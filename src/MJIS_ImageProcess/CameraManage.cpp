#include "CameraManage.h"

CameraManage::CameraManage()
{

}

CameraManage::~CameraManage()
{

}


ICamera* CameraManage::CreateCamera(uint idex, ICamera::CameraType Type)
{
    switch (Type) {
    case ICamera::Local_Camera:
        return new LocalCamera();
        break;
    case ICamera::MV_Camera:
        return new MVCamera();
        break;
    default:
        return nullptr;
        break;
    }
}


//这里测试连接用了双条件嵌套，应该还有更好的方式，此处备注做为优化
bool CameraManage::TryConnectCamera(ICamera* Cmaera)
{
    if (!Cmaera->isConnect())
    {
        if (!Cmaera->open())
        {
            Cmaera->close();
            return false;
        }
        else {
            return true;
        }
    }
    else
    {
        return true;
    }
}


bool CameraManage::StartGrap(ICamera* Camera)
{
    return Camera->startGrap();
}


bool CameraManage::StopGrap(ICamera* Camera)
{
   return Camera->stopGrap();
}


bool CameraManage::ConnectCamera(ICamera* Camera)
{
    return  Camera->open();
}



bool CameraManage::DisConnectCamera(ICamera* Camera)
{
    return Camera->close();
}


