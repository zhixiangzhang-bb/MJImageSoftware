#include "mjis_datasetinformation.h"
#include "ui_mjis_datasetinformation.h"
#include "DataConvert.h"
#include <QTableWidgetItem>
#include <QCoreApplication>

namespace mjis {

    namespace hmi {

        DataSetInformation::DataSetInformation(QWidget* parent) :
            QDialog(parent),
            ui(new Ui::DataSetInformation)
        {
            ui->setupUi(this);
            this->setWindowTitle("报文设置");

            // 仅选择整行
            ui->readdatalist->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->writedatalist->setSelectionBehavior(QAbstractItemView::SelectRows);
        }


        //构造函数重载
        DataSetInformation::DataSetInformation(const QString& name) :ui(new Ui::DataSetInformation)
        {
            ui->setupUi(this);
            this->setWindowTitle("报文设置");

            // 仅选择整行
            ui->readdatalist->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->writedatalist->setSelectionBehavior(QAbstractItemView::SelectRows);

            this->name = name;
            //this->dcm = dcm;
            this->ReadConfig();
        }


        //析构函数
        DataSetInformation::~DataSetInformation()
        {
            delete ui;
        }



        //设置名称
        void DataSetInformation::SetName(const QString& name)
        {
            this->name = name;
        }


        //添加读取配置
        void DataSetInformation::on_readadd_clicked()
        {
            int rowCount = ui->readdatalist->rowCount();
            ui->readdatalist->insertRow(rowCount);

            ui->readdatalist->setItem(rowCount, 0, new QTableWidgetItem("缺省名称"));
            ui->readdatalist->setCellWidget(rowCount, 1, CreateDataStyle());
            ui->readdatalist->setCellWidget(rowCount, 2, CreateByteOrder());
            ui->readdatalist->setItem(rowCount, 3, new QTableWidgetItem("缺省单位"));

        }


        //删除读取的配置
        void DataSetInformation::on_readdelete_clicked()
        {
            QVector<int> selectedRows; // 用于存储选定的行索引
            foreach(const QTableWidgetSelectionRange & range, ui->readdatalist->selectedRanges()) {
                int startRow = range.topRow();
                int endRow = range.bottomRow();

                for (int row = startRow; row <= endRow; ++row) {
                    selectedRows.append(row);
                }
            }

            std::sort(selectedRows.begin(), selectedRows.end(), std::greater<int>());

            for (int idex : selectedRows) {
                QWidget* widget1 = ui->readdatalist->cellWidget(idex, 1);
                QWidget* widget2 = ui->readdatalist->cellWidget(idex, 2);
                delete widget1;
                delete widget2;
                ui->readdatalist->removeRow(idex);
            }
        }


        //添加写入配置
        void DataSetInformation::on_writeadd_clicked()
        {
            int rowCount = ui->writedatalist->rowCount();
            ui->writedatalist->insertRow(rowCount);

            ui->writedatalist->setItem(rowCount, 0, new QTableWidgetItem("缺省名称"));
            ui->writedatalist->setCellWidget(rowCount, 1, CreateDataStyle());
            ui->writedatalist->setCellWidget(rowCount, 2, CreateByteOrder());
            ui->writedatalist->setCellWidget(rowCount, 3, CreateDataWriteList());
        }


        //删除写入配置
        void DataSetInformation::on_writedelete_clicked()
        {
            QVector<int> selectedRows; // 用于存储选定的行索引
            foreach(const QTableWidgetSelectionRange & range, ui->writedatalist->selectedRanges()) {
                int startRow = range.topRow();
                int endRow = range.bottomRow();

                for (int row = startRow; row <= endRow; ++row) {
                    selectedRows.append(row);
                }
            }

            for (int idex : selectedRows) {
                QWidget* widget1 = ui->writedatalist->cellWidget(idex, 1);
                QWidget* widget2 = ui->writedatalist->cellWidget(idex, 2);
                delete widget1;
                delete widget2;
                ui->writedatalist->removeRow(idex);
            }
        }


        //保存配置
        void DataSetInformation::on_state_accepted()
        {
            //获取名称称列
            QVector<QString> NameList;
            QVector<int> DataStyleList;
            QVector<int> ByteOrderList;
            QVector<QString> UnitList;

            for (int row = 0; row < ui->readdatalist->rowCount(); row++) {
                QTableWidgetItem* item0 = ui->readdatalist->item(row, 0); // 获取第一列的单元格对象
                QWidget* widget1 = ui->readdatalist->cellWidget(row, 1); // 获取第二列的单元格部件对象
                QWidget* widget2 = ui->readdatalist->cellWidget(row, 2); // 获取第三列的单元格部件对象
                QTableWidgetItem* item3 = ui->readdatalist->item(row, 3); // 获取第四列的单元格对象

                //读取名称
                if (item0 != nullptr) {
                    NameList.append(item0->text());
                }

                //读取表格数据类型
                if (widget1 != nullptr) {
                    QComboBox* DataStyle = qobject_cast<QComboBox*>(widget1);
                    if (DataStyle != nullptr) {
                        DataStyleList.append(DataStyle->currentIndex());
                    }
                }

                //读取字节顺序
                if (widget2 != nullptr) {
                    QComboBox* ByteOrder = qobject_cast<QComboBox*>(widget2);
                    if (ByteOrder != nullptr) {
                        ByteOrderList.append(ByteOrder->currentIndex());
                    }
                }

                //读取单位
                if (item3 != nullptr) {
                    UnitList.append(item3->text());
                }
            }
            QString path = QCoreApplication::applicationDirPath() + "/Config/Data/" + name + ".cfg";
            QSettings settings(path, QSettings::IniFormat);
            ConfigControl::WriteIniList(settings, "name", NameList);
            ConfigControl::WriteIniList(settings, "datastyle", DataStyleList);
            ConfigControl::WriteIniList(settings, "byteorder", ByteOrderList);
            ConfigControl::WriteIniList(settings, "unit", UnitList);
            this->close();
            emit CompleteConfig();
        }



        //创建数据类型枚举
        QComboBox* DataSetInformation::CreateDataStyle(int idex)
        {
            QComboBox* Qcb = new QComboBox(this);
            Qcb->addItem("Float", 0);
            Qcb->addItem("Int", 1);
            Qcb->addItem("Bool", 2);
            Qcb->setCurrentIndex(idex);
            return Qcb;
        }


        //创建字节顺序枚举
        QComboBox* DataSetInformation::CreateByteOrder(int idex)
        {
            QComboBox* Qcb = new QComboBox(this);
            Qcb->addItem("小端排序", 0);
            Qcb->addItem("大端排序", 1);
            Qcb->setCurrentIndex(idex);
            return Qcb;
        }


        //创建写入数据列表
        QComboBox* DataSetInformation::CreateDataWriteList(int idex)
        {
            QComboBox* Qcb = new QComboBox(this);
            Qcb->setCurrentIndex(idex);
            return Qcb;
        }



        //读取配置
        void DataSetInformation::ReadConfig()
        {
            //获取名称称列
            QVector<QString> NameList;
            QVector<int> DataStyleList;
            QVector<int> ByteOrderList;
            QVector<QString> UnitList;

            QSettings settings(QCoreApplication::applicationDirPath() + "/Config/Data/" + name + ".cfg", QSettings::IniFormat);
            ConfigControl::ReadIniList(settings, "name", NameList);
            ConfigControl::ReadIniList(settings, "datastyle", DataStyleList);
            ConfigControl::ReadIniList(settings, "byteorder", ByteOrderList);
            ConfigControl::ReadIniList(settings, "unit", UnitList);

            //配置写入
            for (size_t i = 0; i < NameList.size(); i++)
            {
                ui->readdatalist->insertRow(i);
                ui->readdatalist->setItem(i, 0, new QTableWidgetItem(NameList[i]));
                ui->readdatalist->setCellWidget(i, 1, CreateDataStyle(DataStyleList[i]));
                ui->readdatalist->setCellWidget(i, 2, CreateByteOrder(ByteOrderList[i]));
                ui->readdatalist->setItem(i, 3, new QTableWidgetItem(UnitList[i]));
            }
        }


        //取消按钮
        void DataSetInformation::on_state_rejected()
        {
            this->close();
        }


    }
}