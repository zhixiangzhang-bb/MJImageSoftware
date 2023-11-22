#pragma once
#include <QObject>
#include <QHash>
#include "mvcamera.h"





class  CameraManage :
    public QObject
{
    Q_OBJECT

public:
    //构造函数
    CameraManage();

    ~CameraManage();

    //根据需要创建相机
    static ICamera* CreateCamera(uint idex, ICamera::CameraType Type);

    //测试相机连接，0为成功，1为失败
    static bool TryConnectCamera(ICamera* Cmaera);

    //相机开始采集
    static bool StartGrap(ICamera* Camera);

    //相机停止采集
    static bool StopGrap(ICamera* Camera);

    //连接相机
    static bool ConnectCamera(ICamera* Camera);

    //关闭相机连接
    static bool DisConnectCamera(ICamera* Camera);


private:

};

