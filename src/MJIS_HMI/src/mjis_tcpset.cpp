#include "mjis_tcpset.h"
#include "ui_mjis_tcpset.h"


namespace mjis {

    namespace hmi {

        TcpSet::TcpSet(QWidget* parent) :
            QDialog(parent),
            ui(new Ui::TcpSet)
        {
            ui->setupUi(this);
            this->setWindowTitle("TCP设置");
        }

        TcpSet::~TcpSet()
        {
            delete ui;
        }


        void TcpSet::on_buttonBox_rejected()
        {
            reject();
        }



        void TcpSet::on_buttonBox_accepted()
        {
            emit ReturnSet(ui->name->text(), ui->sship->text(), ui->sshport->value(), static_cast<net::NetConnect::ConnectStyle>(ui->style->currentIndex()), ui->localip->text(), ui->localport->value());
            accept();
        }


    }
}
