#include "mjis_networkcamera.h"
#include "ui_mjis_networkcamera.h"
#include <QMessageBox>


namespace mjis {

    namespace hmi {

        networkcamera::networkcamera(QWidget* parent) :
            QDialog(parent),
            ui(new Ui::networkcamera)

        {
            ui->setupUi(this);
            ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
            ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            ui->tableWidget->setSelectionBehavior(QTableWidget::SelectRows);
            this->setWindowTitle("本地相机选择");
        }


        networkcamera::~networkcamera()
        {
            delete ui;
        }



        void networkcamera::on_update_clicked()
        {
            std::shared_ptr<mjis::camera::ICamera> Cam(new mjis::camera::MVCamera);
            int num = Cam->search();
            if (num <= 0) {
                ui->progressBar->setValue(100);
                QMessageBox msgBox;
                msgBox.setText("搜索完成、未发现设备");
                msgBox.exec();
            }
            else {
                for (int var = 0; var < num; ++var) {
                    int rownum = ui->tableWidget->rowCount();
                    Cam->setidx(var);
                    mjis::camera::ICamera::Message ms = Cam->gainmessage();
                    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("设备编号"));
                    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("设备型号"));
                    ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("IP地址"));
                    ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("MC地址"));
                    ui->tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("SN码"));
                    ui->tableWidget->insertRow(rownum);
                    ui->tableWidget->setItem(rownum, 0, new QTableWidgetItem(QString::number(ms.idx)));
                    ui->tableWidget->setItem(rownum, 1, new QTableWidgetItem(ms.ModelName));
                    ui->tableWidget->setItem(rownum, 2, new QTableWidgetItem(ms.ipAddr));
                    ui->tableWidget->setItem(rownum, 3, new QTableWidgetItem(ms.MAC));
                    ui->tableWidget->setItem(rownum, 4, new QTableWidgetItem(ms.SN));
                    ui->progressBar->setValue((var + 1) * 100 / num);
                }
                QMessageBox msgBox;
                msgBox.setText("搜索完成");
                msgBox.exec();
            }
        }



        void networkcamera::on_apply_clicked()
        {
            QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();
            if (!items.empty()) {
                switch (ui->cameraType->currentIndex()) {
                case 0://项0返回MV_EN系列相机
                    emit SelcetNetcamId(ui->tableWidget->row(items.at(0)), mjis::camera::ICamera::MV_Camera);
                    this->close();
                    break;
                case 1:
                    break;
                default:
                    break;
                }
            }
            else
                QMessageBox::warning(this, "警告", "请先选择一行再进行操作");

        }



        void networkcamera::on_close_clicked()
        {
            this->close();
        }



    }
}