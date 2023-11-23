#pragma once


#include <QDialog>
#include "TCPConnect.h"






namespace Ui {
class TcpSet;
}

namespace mjis {

    namespace hmi {


        /*****************************************************************
        * 类名称：TCP参数设置界面
        * 功能描述：用于配置TCP参数
        * 作者：zzx
        * 创建日期：2023.8.2
        * 最后修改：zzx
        * 最后修改日期：
        * 备注：
        ******************************************************************/

        class  TcpSet : public QDialog
        {
            Q_OBJECT

        public:

            explicit TcpSet(QWidget* parent = nullptr);

            ~TcpSet();


        private slots:
            void on_buttonBox_accepted();

            void on_buttonBox_rejected();

        private:
            Ui::TcpSet* ui;


        signals:
            void ReturnSet(const QString& name, const QString& sshIP, int sshPort, net::NetConnect::ConnectStyle Style, const QString& localIP, int localPort);
        };

    }
}


