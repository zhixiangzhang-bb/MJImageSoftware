#ifndef DATAINTERFACE_H
#define DATAINTERFACE_H

#include <QWidget>
#include "TCPConnect.h"
#include "tcpset.h"
#include <QMessageBox>
#include <QDir>
#include <QSettings>
#include "datasetinformation.h"
#include "DataConvert.h"

/*****************************************************************
* 类名称：数据界面类
* 功能描述：显示功能
* 作者：zzx
* 创建日期：2023.7.31
* 最后修改：zzx
* 最后修改日期：
* 备注：
******************************************************************/




namespace Ui {
class DataInterface;
}

class  DataInterface : public QWidget
{
    Q_OBJECT

public:
    explicit DataInterface(QWidget *parent = nullptr);
    ~DataInterface();

    //添加连接
    void AddTCPConnect(const QString& name,const QString& IP, std::shared_ptr<NetConnect> tcp);

    //返回选择的字符串
    std::string* ReturnDataStr();

private:

    //配置文件
    QSettings settings;

    //TCP连接列表
    QVector<std::shared_ptr<NetConnect>> NetConnectList;

    //连接Map
    QMap<std::shared_ptr<NetConnect>, std::shared_ptr<DataConvertManage>> ConnectMap;

    //显示字符串
    std::string* datastring;

    //根据参数创建连接
    void CreateConnect(const QString& name, const QString& sshIP, int sshPort, NetConnect::ConnectStyle Style, const QString& localIP, int localPort);

    //新建返回的TCP参数进行设置
    void ReturnTCPConfig(const QString& name, const QString& sshIP, int sshPort, NetConnect::ConnectStyle Style, const QString& localIP, int localPort);

    //读取总的连接配置信息
    void ReadConnectConfig();

    //写入总的连接配置信息
    void WriteConfig();

    //初始化连接配置信息
    void InitConnectCofiguration();

    //数据配置变更
    void ConnectConfigChange();

    //读取数据
    void NetWorkData();

    Ui::DataInterface *ui;

signals:
    //发出按索引连接信号
    void ConnectIdex(NetConnect* network);

    //发出按索引连接信号
    void SetConnectIdex(NetConnect* network);

    //发出按索引关闭连接信号
    void DisConnectIdex(NetConnect* network);

    //保存配置
    void SaveConfig();

private slots:

    void on_add_clicked();

    void on_delete_2_clicked();

    //返回连接错误
    void ConnectError(QString error);
};

#endif // DATAINTERFACE_H
