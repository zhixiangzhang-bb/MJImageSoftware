#include "TCPConnect.h"




namespace mjis {

	namespace net {


		ZTCPCilent::ZTCPCilent()
			: socket(nullptr)
		{

		}


		ZTCPCilent::~ZTCPCilent()
		{

		}



		//新建客户端
		void ZTCPCilent::NewConnect(const QString& name, const QString& sshIP, int sshPort, NetConnect::ConnectStyle Style, const QString& localIP, int localPort)
		{
			this->name = name;
			this->sshIP = sshIP;
			this->sshPort = sshPort;
			this->localIP = localIP;
			this->localPort = localPort;
			this->Style = Style;
			if (socket == nullptr) {
				socket = std::make_shared<QTcpSocket>(this);
			}
			set = std::make_shared<QPushButton>("设置");
			// 设置按钮样式
			set->setStyleSheet("QPushButton { background-color: transparent; border: none; color: blue; }"
				"QPushButton:hover { text-decoration: underline; }");
			conct = std::make_shared<QPushButton>("已断开连接");
			conct->setCheckable(true);
			conct->setStyleSheet("background-color: red;");
			box = std::make_shared<QCheckBox>(name);
			connect(socket.get(), &QTcpSocket::readyRead, this, &ZTCPCilent::onReadyRead);
			connect(socket.get(), &QTcpSocket::errorOccurred, this, &ZTCPCilent::onSocketError);
			connect(socket.get(), &QTcpSocket::connected, this, &ZTCPCilent::NetWorkConnected);
			connect(socket.get(), &QTcpSocket::disconnected, this, &ZTCPCilent::NetWorkDisconnected);
			connect(conct.get(), &QPushButton::clicked, this, &ZTCPCilent::PushbuttonClicked);
			connect(set.get(), &QPushButton::clicked, this, &ZTCPCilent::SetConnectClicked);
		}



		//按钮设置函数
		void ZTCPCilent::SetConnectClicked()
		{
			/*
			std::shared_ptr<DataSetInformation> Dsi(new DataSetInformation(name));
			connect(Dsi.get(), &DataSetInformation::CompleteConfig, this, &ZTCPCilent::ConfigChange);
			Dsi->exec();
			*/
		}



		//连接按钮点击信号槽
		void ZTCPCilent::PushbuttonClicked()
		{
			if (conct->isChecked()) {
				Connect();
			}
			else {
				DisConnect();
			}
		}



		//设置批量参数
		void ZTCPCilent::SetTCPConnect(const QString& sshIP, int sshPort, NetConnect::ConnectStyle Style, const QString& localIP, int localPort)
		{
			this->sshIP = sshIP;
			this->sshPort = sshPort;
			this->localIP = localIP;
			this->localPort = localPort;
			this->Style = Style;
		}


		//连接到服务器
		bool ZTCPCilent::Connect()
		{
			if (localIP != "" && localPort != -1) {
				// 设置要绑定的网卡地址和端口
				QString targetInterface = localIP;
				qint16 targetPort = localPort;
				// 转换网卡地址为QHostAddress对象
				QHostAddress bindAddress(targetInterface);
				// 绑定到指定网卡和端口
				socket->bind(bindAddress, localPort);
			}
			// 连接到服务器
			socket->connectToHost(QHostAddress(sshIP), sshPort);
			return true;
		}



		//断开连接到服务器
		void ZTCPCilent::DisConnect()
		{
			socket->disconnectFromHost();
		}



		//写入数据
		void ZTCPCilent::WriteData(const QByteArray& writeData)
		{
			if (socket->state() == QAbstractSocket::ConnectedState) {
				socket->write(writeData);
			}
		}




		//读取数据
		void ZTCPCilent::onReadyRead()
		{
			emit ReadData(socket->readAll());
		}



		//连接错误
		void ZTCPCilent::onSocketError(QAbstractSocket::SocketError error)
		{
			emit ConnectError(TCPErrorenumToString(error));
		}



		//已连接状态
		void ZTCPCilent::NetWorkConnected()
		{
			conct->setText("已连接");
			// 设置背景颜色
			conct->setStyleSheet("background-color: green;");
			conct->setChecked(true);
		}


		//已连接状态
		void ZTCPCilent::NetWorkDisconnected()
		{
			conct->setText("已断开连接");
			// 设置背景颜色
			conct->setStyleSheet("background-color: red;");
			conct->setChecked(false);
		}


		/*
		TCP服务器类：
		服务器端使能以侦听为主，所以这里用侦听代替连接请求
		当有连接请求时，建立连接套接字，同时进行收发工作
		一般来讲服务器是无法选择远程ip和端口，也就是说任何客户端都可以在此端口进行数据传输
		*/



		ZTCPServer::ZTCPServer()
			: socket(nullptr)
		{

		}


		ZTCPServer::~ZTCPServer()
		{

		}



		//新建客户端
		void ZTCPServer::NewConnect(const QString& name, const QString& sshIP, int sshPort, NetConnect::ConnectStyle Style, const QString& localIP, int localPort)
		{
			this->name = name;
			this->sshIP = sshIP;
			this->sshPort = sshPort;
			this->localIP = localIP;
			this->localPort = localPort;
			this->Style = Style;
			if (server == nullptr) {
				server = std::make_shared<QTcpServer>(this);
			}
			set = std::make_shared<QPushButton>("设置");
			// 设置按钮样式
			set->setStyleSheet("QPushButton { background-color: transparent; border: none; color: blue; }"
				"QPushButton:hover { text-decoration: underline; }");
			conct = std::make_shared<QPushButton>("未侦听状态");
			conct->setCheckable(true);
			conct->setStyleSheet("background-color: red;");
			box = std::make_shared<QCheckBox>(name);
			connect(server.get(), &QTcpServer::newConnection, this, &ZTCPServer::newConnection);
			connect(conct.get(), &QPushButton::clicked, this, &ZTCPServer::PushbuttonClicked);
			connect(set.get(), &QPushButton::clicked, this, &ZTCPServer::SetConnectClicked);
		}



		//按钮设置函数
		void ZTCPServer::SetConnectClicked()
		{
			/*
			std::shared_ptr<DataSetInformation> Dsi(new DataSetInformation(name));
			connect(Dsi.get(), &DataSetInformation::CompleteConfig, this, &ZTCPCilent::ConfigChange);
			Dsi->exec();
			*/
		}



		//连接按钮点击信号槽
		void ZTCPServer::PushbuttonClicked()
		{
			if (conct->isChecked()) {
				Connect();
			}
			else {
				DisConnect();
			}
		}



		//设置批量参数
		void ZTCPServer::SetTCPConnect(const QString& sshIP, int sshPort, NetConnect::ConnectStyle Style, const QString& localIP, int localPort)
		{
			this->sshIP = sshIP;
			this->sshPort = sshPort;
			this->localIP = localIP;
			this->localPort = localPort;
			this->Style = Style;
		}


		//开始侦听
		bool ZTCPServer::Connect()
		{
			bool a = server->listen(QHostAddress::Any, localPort);
			return true;
		}



		//关闭侦听
		void ZTCPServer::DisConnect()
		{
			server->close();
		}


		//客户端请求连接
		void ZTCPServer::newConnection()
		{
			socket = std::make_shared<QTcpSocket>(server->nextPendingConnection());
			NetWorkConnected();
			// 连接已准备读取信号
			connect(socket.get(), &QTcpSocket::readyRead, this, &ZTCPServer::onReadyRead);
			// 连接断开信号
			connect(socket.get(), &QTcpSocket::disconnected, this, &ZTCPServer::NetWorkDisconnected);

		}

		//写入数据
		void ZTCPServer::WriteData(const QByteArray& writeData)
		{
			if (socket->state() == QAbstractSocket::ConnectedState) {
				socket->write(writeData);
			}
		}



		//读取数据
		void ZTCPServer::onReadyRead()
		{
			emit ReadData(socket->readAll());
		}



		//连接错误
		void ZTCPServer::onSocketError(QAbstractSocket::SocketError error)
		{
			emit ConnectError(TCPErrorenumToString(error));
		}



		//已连接状态
		void ZTCPServer::NetWorkConnected()
		{
			conct->setText("已连接");
			// 设置背景颜色
			conct->setStyleSheet("background-color: green;");
			conct->setChecked(true);
		}


		//已连接状态
		void ZTCPServer::NetWorkDisconnected()
		{
			conct->setText("已断开连接");
			// 设置背景颜色
			conct->setStyleSheet("background-color: red;");
			conct->setChecked(false);
		}


	}
}