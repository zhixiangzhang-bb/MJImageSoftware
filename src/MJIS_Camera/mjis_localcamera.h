#pragma once



#include "mjis_camera_macro.h"
#include <qtimer.h>



namespace mjis {

    /*****************************************************************
    * 类名称：本地相机类
    * 功能描述：根据ID控制相机，比较简单，主要做测试
    * 作者：zzx
    * 创建日期：2023.6.10
    * 最后修改：zzx
    * 最后修改日期：
    * 备注：
    ******************************************************************/


    class Camera_API LocalCamera : public ICamera
    {
        Q_OBJECT
    public:
        explicit LocalCamera(QObject* parent = nullptr);

        //设置相机ID
        void setidx(uint idx) override;

        uint search() override;

        void MVSetDefaultParameters() override;

        //返回连接状态
        bool isConnect() override;

        //返回采集状态
        bool isGrap() override;

        //相机属性页面
        bool CameraSetSheet() override;

        //返回相机ID
        int GetCameraIdx() override;

        //返回相机ID
        int ReturnFps() override;

    public slots:
        //打开相机
        bool open() override;

        //关闭相机
        bool close() override;

        //开始采集
        bool startGrap() override;

        //停止采集
        bool stopGrap() override;

        //设置相机FPS
        bool setFPS(uint fps) override;

        //本地相机没有IP等信息，这里用曝光时间等代替
        ICamera::Message gainmessage() override;


    private:
        cv::VideoCapture cap;

        std::shared_ptr<QTimer> time;

        void ReadIamge();

    };

}

