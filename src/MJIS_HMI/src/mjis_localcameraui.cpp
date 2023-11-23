#include "mjis_localcameraui.h"
#include "ui_mjis_localcameraui.h"
#include <QMessageBox>


namespace mjis {

    namespace hmi {

        LocalCameraUI::LocalCameraUI(QWidget* parent) :
            QDialog(parent),
            ui(new Ui::LocalCameraUI)
        {
            ui->setupUi(this);
            ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
            ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            ui->tableWidget->setSelectionBehavior(QTableWidget::SelectRows);
            this->setWindowTitle("本地相机选择");
            ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("本地ID"));
            ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("相机宽度"));
            ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("相机高度"));
            ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("FPS"));
        }



        LocalCameraUI::~LocalCameraUI()
        {
            delete ui;
        }



        void LocalCameraUI::on_select_clicked()
        {
            mjis::camera::LocalCamera loccam;
            int numCameras = 0;
            uint num = ui->number->value();
            for (int i = 0; i < 20; i++) {  // 假设最多有100个相机设备
                int rownum = ui->tableWidget->rowCount();
                loccam.setidx(i);
                bool state = loccam.open();
                if (!state) {
                    mjis::camera::ICamera::Message ms = loccam.gainmessage();
                    ui->tableWidget->insertRow(rownum);
                    ui->tableWidget->setItem(rownum, 0, new QTableWidgetItem(QString::number(ms.idx)));
                    ui->tableWidget->setItem(rownum, 1, new QTableWidgetItem(ms.ModelName));
                    ui->tableWidget->setItem(rownum, 2, new QTableWidgetItem(ms.ipAddr));
                    ui->tableWidget->setItem(rownum, 3, new QTableWidgetItem(ms.MAC));
                }
                ui->progressBar->setValue((i + 1) * 100 / 20);
            }
            QMessageBox msgBox;
            msgBox.setText("搜索完成");
            msgBox.exec();
        }



        void LocalCameraUI::on_appy_clicked()
        {
            QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();
            if (!items.empty()) {
                emit SelcetNetcamId(ui->tableWidget->row(items.at(0)), mjis::camera::ICamera::Local_Camera);
                this->close();
            }
            else {
                QMessageBox::warning(this, "警告", "请先选择一行再进行操作");
            }
        }



        void LocalCameraUI::on_close_clicked()
        {
            this->close();
        }


        void LocalCameraUI::on_number_valueChanged(int arg1)
        {

        }

    }
}