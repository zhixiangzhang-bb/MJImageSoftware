


#include "mjis_datainterface.h"
#include "ui_mjis_datainterface.h"


namespace mjis {

    namespace hmi {

        DataInterface::DataInterface(QWidget* parent) :
            QWidget(parent), settings(QCoreApplication::applicationDirPath() + "/Config/ConnectConfig.cfg", QSettings::IniFormat)
            , ui(new Ui::DataInterface), datastring(new std::string)
        {
            ui->setupUi(this);
            ui->datalist->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            // 设置行高模式为自适应内容
            //ui->projectlist->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

            ui->projectlist->setSelectionBehavior(QAbstractItemView::SelectRows);  // 仅选择整行

            connect(ui->save, &QPushButton::clicked, this, &DataInterface::WriteConfig);
            //实例化后初始化配置文件
            InitConnectCofiguration();

            LOG(INFO) << "通讯模块：实例化成功";
        }




        DataInterface::~DataInterface()
        {
            delete ui;
        }



        //添加连接
        void DataInterface::AddTCPConnect(const QString& name, const QString& IP, std::shared_ptr<net::NetConnect> tcp)
        {
            int rowCount = ui->projectlist->rowCount();
            ui->projectlist->insertRow(rowCount);

            ui->projectlist->setCellWidget(rowCount, 2, tcp->ReturnSetButton());
            ui->projectlist->setCellWidget(rowCount, 3, tcp->ReturnConnectButton());
            ui->projectlist->setCellWidget(rowCount, 0, tcp->ReturnBoxButton());
            QTableWidgetItem* ip = new QTableWidgetItem(IP);
            ip->setFlags(ip->flags() ^ Qt::ItemIsEditable); // 设置列只读
            ui->projectlist->setItem(rowCount, 1, ip);

            NetConnectList.append(tcp);
        }



        //增加连接
        void DataInterface::on_add_clicked()
        {
            TcpSet set;
            connect(&set, &TcpSet::ReturnSet, this, &DataInterface::ReturnTCPConfig);
            set.exec();

        }


        //删除连接
        void DataInterface::on_delete_2_clicked()
        {
            QVector<int> selectedRows; // 用于存储选定的行索引
            foreach(const QTableWidgetSelectionRange & range, ui->projectlist->selectedRanges()) {
                int startRow = range.topRow();
                int endRow = range.bottomRow();

                for (int row = startRow; row <= endRow; ++row) {
                    selectedRows.append(row);
                }
            }

            std::sort(selectedRows.begin(), selectedRows.end(), std::greater<int>());

            for (int idex : selectedRows) {
                ConnectMap.remove(NetConnectList[idex]);
                NetConnectList.removeAt(idex);
                ui->projectlist->removeRow(idex);
            }

            this->ConnectConfigChange();
        }



        //创建连接
        void DataInterface::CreateConnect(const QString& name, const QString& sshIP, int sshPort, net::NetConnect::ConnectStyle Style, const QString& localIP, int localPort)
        {
            std::shared_ptr<net::NetConnect> cnct;
            switch (Style)
            {
            case net::NetConnect::TCPCilent:
                cnct = std::make_shared<net::ZTCPCilent>();
                break;
            case net::NetConnect::TCPServer:
                cnct = std::make_shared<net::ZTCPServer>();
                break;
            case net::NetConnect::UDPCilent:
                break;
            case net::NetConnect::UDPServer:
                break;
            case net::NetConnect::ModbusTCPServer:
                break;
            case net::NetConnect::ModbusTCPCilent:
                break;
            default:
                break;
            }
            std::shared_ptr<DataConvertManage> dcm(new DataConvertManage(QCoreApplication::applicationDirPath() + "/Config/Data/" + name + ".cfg"));
            ConnectMap.insert(cnct, dcm);
            connect(cnct.get(), &net::NetConnect::ReadData, dcm.get(), &DataConvertManage::ConverReadData);
            connect(dcm.get(), &DataConvertManage::ReadData, this, &DataInterface::NetWorkData);
            connect(cnct.get(), &net::NetConnect::ConnectError, this, &DataInterface::ConnectError);
            connect(cnct.get(), &net::NetConnect::ConfigChange, this, &DataInterface::ConnectConfigChange);
            cnct->NewConnect(name, sshIP, sshPort, Style, localIP, localPort);
            this->AddTCPConnect(name, sshIP, cnct);
            this->ConnectConfigChange();
            LOG(INFO) << "通讯模块：添加连接成功";
        }



        //新建返回的TCP参数进行设置
        void DataInterface::ReturnTCPConfig(const QString& name, const QString& sshIP, int sshPort, net::NetConnect::ConnectStyle Style, const QString& localIP, int localPort)
        {
            QVector<QString> namelist;
            ConfigControl::ReadIniList(settings, "name", namelist);
            if (namelist.contains(name)) {
                QMessageBox::warning(nullptr, "警告", "存在名称相同的连接！");
                LOG(ERROR) << "通讯模块：创建失败名称重复";
            }
            else {
                CreateConnect(name, sshIP, sshPort, Style, localIP, localPort);
                LOG(INFO) << "通讯模块：创建连接成功";
            }
        }


        //返回连接错误
        void DataInterface::ConnectError(QString error)
        {
            net::NetConnect* netsender = qobject_cast<net::NetConnect*>(sender());
            if (netsender) {
                LOG(ERROR) << "通讯模块：通讯错误:" << netsender->GetName().toStdString() << error.toStdString();
            }
        }



        //读取总的连接配置信息
        void DataInterface::ReadConnectConfig()
        {
            QVector<QString> name;
            ConfigControl::ReadIniList(settings, "name", name);
            QVector<QString> sshIP;
            ConfigControl::ReadIniList(settings, "sshIP", sshIP);
            QVector<int> sshPort;
            ConfigControl::ReadIniList(settings, "sshPort", sshPort);
            QVector<int> style;
            ConfigControl::ReadIniList(settings, "style", style);
            QVector<QString> localIP;
            ConfigControl::ReadIniList(settings, "localIP", localIP);
            QVector<int> localPort;
            ConfigControl::ReadIniList(settings, "localPort", localPort);

            std::vector<int> numbers;
            numbers.push_back(name.size());
            numbers.push_back(sshIP.size());
            numbers.push_back(sshPort.size());
            numbers.push_back(style.size());
            numbers.push_back(localIP.size());
            numbers.push_back(localPort.size());
            if (std::equal(numbers.begin(), numbers.end(), numbers.begin())) {
                for (size_t i = 0; i < name.size(); i++)
                {
                    CreateConnect(name[i], sshIP[i], sshPort[i], static_cast<net::NetConnect::ConnectStyle>(style[i]), localIP[i], localPort[i]);
                }
            }
            LOG(INFO) << "通讯模块：读取配置成功";
        }



        //写入总的连接配置信息
        void DataInterface::WriteConfig()
        {
            QVector<QString> name;
            QVector<QString> sshIP;
            QVector<int> sshPort;
            QVector<int> style;
            QVector<QString> localIP;
            QVector<int> localPort;
            for (const auto& key : NetConnectList) {
                name.append(key->GetName());
                sshIP.append(key->GetSSHIP());
                sshPort.append(key->GetSSHPort());
                style.append(key->GetStyle());
                localIP.append(key->GetLocalIP());
                localPort.append(key->GetLocalPort());
            }

            // 连接名称存配置文件
            ConfigControl::WriteIniList(settings, "name", name);
            // 连接远程IP存配置文件
            ConfigControl::WriteIniList(settings, "sshIP", sshIP);
            // 连接名称存配置文件
            ConfigControl::WriteIniList(settings, "sshPort", sshPort);
            // 连接名称存配置文件
            ConfigControl::WriteIniList(settings, "style", style);
            // 连接名称存配置文件
            ConfigControl::WriteIniList(settings, "localIP", localIP);
            // 连接名称存配置文件
            ConfigControl::WriteIniList(settings, "localPort", localPort);

            LOG(INFO) << "通讯模块：写入配置成功";
        }



        //初始化配置
        void DataInterface::InitConnectCofiguration()
        {
            QString Path = QCoreApplication::applicationDirPath() + "/Config/ConnectConfig.cfg";
            //防止配置文件被删除，同时可以做为配置文件初始化
            QFile file(Path);
            if (file.exists()) {
                ReadConnectConfig();
                LOG(INFO) << "通讯模块：读取配置成功";
            }
            else {
                QVector<QString> name = { "测试用连接" };
                QVector<QString> sshIP = { "192.168.1.201" };
                QVector<int> sshPort = { 2000 };
                QVector<int> style = { 1 };
                QVector<QString> localIP = { "192.168.1.201" };
                QVector<int> localPort = { 2000 };
                // 连接名称存配置文件
                ConfigControl::WriteIniList(settings, "name", name);
                // 连接远程IP存配置文件
                ConfigControl::WriteIniList(settings, "sshIP", sshIP);
                // 连接名称存配置文件
                ConfigControl::WriteIniList(settings, "sshPort", sshPort);
                // 连接名称存配置文件
                ConfigControl::WriteIniList(settings, "style", style);
                // 连接名称存配置文件
                ConfigControl::WriteIniList(settings, "localIP", localIP);
                // 连接名称存配置文件
                ConfigControl::WriteIniList(settings, "localPort", localPort);

                LOG(ERROR) << "通讯模块：连接配置不存在，执行自动创建";

            }
        }




        //数据配置变更
        void DataInterface::ConnectConfigChange()
        {
            //复选列表
            QVector<QCheckBox*> NameList;
            //单位列表
            QVector<QString> UintList;
            QMap<std::shared_ptr<net::NetConnect>, std::shared_ptr<DataConvertManage>>::const_iterator iter;
            for (iter = ConnectMap.constBegin(); iter != ConnectMap.constEnd(); ++iter) {
                // 获取当前迭代器指向的键和值
                std::shared_ptr<DataConvertManage> dataConvertManage = iter.value();
                dataConvertManage->ReadConfigurationFiles();
                NameList.append(dataConvertManage->ReturnNameList());
                UintList.append(dataConvertManage->ReturnUintList());
            }

            int num = ui->datalist->rowCount();
            for (size_t i = 0; i < NameList.size(); i++)
            {
                int row = ui->datalist->rowCount();  // 获取当前行数
                ui->datalist->insertRow(row);
                ui->datalist->setCellWidget(row, 0, NameList[i]);
                QTableWidgetItem* table = ui->datalist->item(i, 1);
                if (table == nullptr) {
                    ui->datalist->setItem(row, 2, new QTableWidgetItem(UintList[i]));
                }
                else {
                    table->setText(UintList[i]);
                }
            }

            for (size_t i = 0; i < num; i++)
            {
                ui->datalist->removeRow(0);
            }

            LOG(INFO) << "通讯模块：配置数据列表成功";
        }



        //网络数据更新
        void DataInterface::NetWorkData()
        {
            //值列表
            QVector<QString> ValueList;
            QMap<std::shared_ptr<net::NetConnect>, std::shared_ptr<DataConvertManage>>::const_iterator iter;
            for (iter = ConnectMap.constBegin(); iter != ConnectMap.constEnd(); ++iter) {
                // 获取当前迭代器指向的键和值
                std::shared_ptr<DataConvertManage> dataConvertManage = iter.value();
                dataConvertManage->ReadConfigurationFiles();
                ValueList.append(dataConvertManage->ReturnVlaueList());
            }

            QString* str = new QString;
            for (size_t i = 0; i < ValueList.size(); i++)
            {
                QTableWidgetItem* table = ui->datalist->item(i, 1);
                if (table == nullptr) {
                    ui->datalist->setItem(i, 1, new QTableWidgetItem(ValueList[i]));
                }
                else {
                    table->setText(ValueList[i]);
                }

                QCheckBox* box = qobject_cast<QCheckBox*>(ui->datalist->cellWidget(i, 0));
                if (box->isChecked()) {
                    QString value;
                    if (ui->datalist->item(i, 1) != nullptr) {
                        value = ui->datalist->item(i, 1)->text();
                    }
                    QString unit;
                    if (ui->datalist->item(i, 2) != nullptr) {
                        unit = ui->datalist->item(i, 2)->text();
                    }
                    str->append(box->text() + ":" + value + " " + unit + "\n");
                }
            }
            *datastring = str->toStdString();
            delete str;
        }



        //返回选择的字符串指针，这里采用共享内存的方式
        std::string* DataInterface::ReturnDataStr()
        {
            //QString* str = new QString;
            //for (size_t i = 0; i < ui->datalist->rowCount(); i++)
            //{
            //    QCheckBox* box = qobject_cast<QCheckBox*>(ui->datalist->cellWidget(i, 0));
            //    if (box->isChecked()) {
            //        QString value;            
            //        if (ui->datalist->item(i, 1) != nullptr) {
            //            value = ui->datalist->item(i, 1)->text();
            //        }
            //        QString unit;
            //        if (ui->datalist->item(i, 2) != nullptr) {
            //            unit = ui->datalist->item(i, 2)->text();
            //        }
            //        str->append(box->text() + ":" + value + " " + unit+"\n");
            //    }
            //}
            //*datastring = str->toStdString();
            //delete str;
            return datastring;
        }


    }
}