#pragma once

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMetaEnum>
#include <QPushButton>
#include <QCheckBox>



/*****************************************************************
* 类名称：网络通讯基类
* 功能描述：提供接口的类
* 作者：zzx
* 创建日期：2023.8.2
* 最后修改：zzx
* 最后修改日期：
* 备注：
******************************************************************/




class NetConnect : public QObject
{
	Q_OBJECT
public:

	//连接类型枚举
	enum ConnectStyle {
		TCPCilent,
		TCPServer,
		UDPCilent,
		UDPServer,
		ModbusTCPServer,
		ModbusTCPCilent
	};


	NetConnect():sshPort(-1), localPort(-1), Style(TCPCilent){};


	//TCP连接错误枚举转字符串
	static QString TCPErrorenumToString(QAbstractSocket::SocketError Error)
	{
		const QMetaObject* metaObject = &QTcpSocket::staticMetaObject;
		int index = metaObject->indexOfEnumerator("SocketError");
		QMetaEnum metaEnum = metaObject->enumerator(index);
		return QString::fromUtf8(metaEnum.valueToKey(Error));
	}

	virtual void SetTCPConnect(const QString& sshIP, int sshPort, NetConnect::ConnectStyle Style, const QString& localIP, int localPort)=0;

	virtual void NewConnect(const QString& name, const QString& sshIP, int sshPort, NetConnect::ConnectStyle Style, const QString& localIP, int localPort)=0;

	virtual bool Connect()=0;

	virtual void DisConnect()=0;

	virtual void WriteData(const QByteArray& writeData)=0;


	//返回设置按钮
	QPushButton* ReturnSetButton() {
		return set.get();
	}

	//返回连接按钮
	QPushButton* ReturnConnectButton() {
		return conct.get();
	}

	//返回连接名称选择按钮
	QCheckBox* ReturnBoxButton() {
		return box.get();
	}

	//返回连接名称
	QString GetName() {
		return name;
	}

	//返回本地IP
	QString GetLocalIP() {
		return localIP;
	}

	//返回本地端口说明
	int GetLocalPort() {
		return localPort;
	}

	//返回远程IP说明
	QString GetSSHIP() {
		return sshIP;
	}

	//返回远程端口说明
	int GetSSHPort() {
		return sshPort;
	}

	//返回类型说明
	ConnectStyle GetStyle() {
		return Style;
	}




protected:
	//连接类型
	ConnectStyle Style;

	//连接名称
	QString name;

	//远程IP地址
	QString sshIP;

	//远程端口
	int sshPort;

	//本地IP地址
	QString localIP;

	//本地端口
	int localPort;

	//设置按钮
	std::shared_ptr<QPushButton> set;

	//连接按钮
	std::shared_ptr<QPushButton> conct;

	//复选按钮
	std::shared_ptr<QCheckBox> box;



signals:
	void ReadData(QByteArray readData);

	void onConnected();

	void onDisconnected();

	void Connected();

	void DisConnected();

	void ConnectError(QString error);

	void ConfigChange();

};



/*****************************************************************
* 类名称：TCP客户端连接
* 功能描述：可选择做为TCP客户端
* 作者：zzx
* 创建日期：2023.8.2
* 最后修改：zzx
* 最后修改日期：
* 备注：
******************************************************************/




class  ZTCPCilent : public NetConnect
{

public:
	ZTCPCilent();

	~ZTCPCilent();

	//设置批量参数:远程IP，远程端口，类型，本地IP，本地端口
	void SetTCPConnect(const QString& sshIP, int sshPort, NetConnect::ConnectStyle Style,const QString& localIP="", int localPort=-1) override;

	//新建客户端:远程IP，远程端口，类型，本地IP(为空则按索引），本地端口(为空则自行分配）
	void NewConnect(const QString& name, const QString& sshIP, int sshPort, NetConnect::ConnectStyle Style, const QString& localIP="", int localPort=-1) override;

	//连接到服务器:成功返回0，失败返回1
	bool Connect() override;

	//断开连接到服务器
	void DisConnect() override;

	//写入数据
	void WriteData(const QByteArray& writeData) override;


private:
	//客户端套接字
	std::shared_ptr<QTcpSocket> socket;

	//读取完毕
	void onReadyRead();

	//读取错误
	void onSocketError(QAbstractSocket::SocketError error);

	//已连接状态
	void NetWorkConnected();

	//已断开连接状态
	void NetWorkDisconnected();

	//按钮设置函数
	void SetConnectClicked();

	//连接按钮点击信号槽
	void PushbuttonClicked();


signals:


};



/*****************************************************************
* 类名称：TCP服务器
* 功能描述：提供TCP服务器连接，采用侦听方式
* 作者：zzx
* 创建日期：2023.8.9
* 最后修改：zzx
* 最后修改日期：
* 备注：
******************************************************************/


class  ZTCPServer : public NetConnect
{

public:
	ZTCPServer();

	~ZTCPServer();

	//设置批量参数:远程IP，远程端口，类型，本地IP，本地端口
	void SetTCPConnect(const QString& sshIP, int sshPort, NetConnect::ConnectStyle Style, const QString& localIP = "", int localPort = -1) override;

	//新建客户端:远程IP，远程端口，类型，本地IP(为空则按索引），本地端口(为空则自行分配）
	void NewConnect(const QString& name, const QString& sshIP, int sshPort, NetConnect::ConnectStyle Style, const QString& localIP = "", int localPort = -1) override;

	//连接到服务器:成功返回0，失败返回1
	bool Connect() override;

	//断开连接到服务器
	void DisConnect() override;

	//写入数据
	void WriteData(const QByteArray& writeData) override;


private:
	//客户端套接字
	std::shared_ptr<QTcpSocket> socket;

	//客户端套接字
	std::shared_ptr<QTcpServer> server;

	//客户端请求连接
	void newConnection();

	//读取完毕
	void onReadyRead();

	//读取错误
	void onSocketError(QAbstractSocket::SocketError error);

	//已连接状态
	void NetWorkConnected();

	//已断开连接状态
	void NetWorkDisconnected();

	//按钮设置函数
	void SetConnectClicked();

	//连接按钮点击信号槽
	void PushbuttonClicked();

};

