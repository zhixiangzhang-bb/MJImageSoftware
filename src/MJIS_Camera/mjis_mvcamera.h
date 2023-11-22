#pragma once


#include "mjis_camera_macro.h"
#include "GigECamera_Types.h"


namespace mjis {

    /*****************************************************************
    * 类名称： 维视相机类
    * 功能描述： 从相机基类继承并重写部分函数，做为维视相机专用类
    * 作者：zzx
    * 创建日期：2023/7/6
    * 最后修改：zzx
    * 最后修改日期：2023/7/19
    * 备注：
    ******************************************************************/



    class Camera_API MVCamera :public ICamera
    {
        Q_OBJECT
    public:
        explicit MVCamera(QObject* parent = nullptr);

        //设置相机ID
        void setidx(uint idx) override;

        //查找可用相机数量
        uint search() override;

        void MVSetDefaultParameters() override;

        int showStreamOnLabel(MV_IMAGE_INFO* pInfo);

        //设置相机FPS
        bool setFPS(uint fps) override;

        //返回连接状态
        bool isConnect() override;

        //返回采集状态
        bool isGrap() override;

        //打开相机属性页
        bool CameraSetSheet();

        //连接相机
        bool open() override;

        //关闭相机
        bool close() override;

        //获取信息
        ICamera::Message gainmessage() override;

        //开始采集
        bool startGrap() override;

        //停止采集
        bool stopGrap() override;

        //获取相机ID
        int GetCameraIdx() override;

        //返回相机ID
        int ReturnFps() override;

    private:
        MVCamInfo* CamInfo;

        HANDLE hCam;

        HANDLE m_hImg;

        HANDLE m_hPropDlg;

        HANDLE m_hProperty;

        cv::Mat img2cvMat(HANDLE hImg);

    };

}

