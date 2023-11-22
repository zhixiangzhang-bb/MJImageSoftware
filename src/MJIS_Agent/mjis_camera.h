#pragma once


#include "GigECamera_Types.h"
#include "mjis_agent_macro.h"
#include <qtimer.h>



namespace mjis {

        class  MJIS_Agent_API ICamera : public QObject {

            Q_OBJECT
        public:

            //相机状态枚举
            enum  CameraState {
                SUCCESS,//成功
                FAULT,//错误
                ERR_RESOURCE_IN_USE,//资源被占用 
                ACCESS_DENIED,//无法访问
                INVALID_ID,//ID错误
                FILE_IO//I/O错误
            };


            //相机信息结构体
            struct  Message {
                uint idx = -1;
                QString ModelName;
                QString ipAddr;
                QString MAC;
                QString SN;
            };


            //相机类型枚举
            enum  CameraType {
                No,
                Local_Camera,
                MV_Camera,
            };



            ICamera(QObject* parent = nullptr)
                : QObject(parent), idx(-1), fps(30) {}


            Message Mess;

            virtual void setidx(uint idx) = 0;

            virtual uint search() = 0;

            virtual void MVSetDefaultParameters() = 0;

            virtual bool isConnect() = 0;

            virtual bool isGrap() = 0;

            virtual bool CameraSetSheet() = 0;

            virtual bool open() = 0;

            virtual bool close() = 0;

            virtual Message gainmessage() = 0;

            virtual bool startGrap() = 0;

            virtual bool stopGrap() = 0;

            virtual bool setFPS(uint fps) = 0;

            virtual int GetCameraIdx() = 0;

            virtual int ReturnFps() = 0;


        protected:
            //相机ID
            uint idx;

            //相机类型
            CameraType Type;

            //相机连接状态
            bool connectstate;

            //相机采集状态
            bool grapstate;

            //相机fps
            int fps;


            //考虑多种使用方式，这里加入信号
        signals:
            void cameraReadQImage(cv::Mat image);

        };





    /*****************************************************************
    * 类名称：本地相机类
    * 功能描述：根据ID控制相机，比较简单，主要做测试
    * 作者：zzx
    * 创建日期：2023.6.10
    * 最后修改：zzx
    * 最后修改日期：
    * 备注：
    ******************************************************************/


    class MJIS_Agent_API LocalCamera : public ICamera
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


    /*****************************************************************
    * 类名称： 维视相机类
    * 功能描述： 从相机基类继承并重写部分函数，做为维视相机专用类
    * 作者：zzx
    * 创建日期：2023/7/6
    * 最后修改：zzx
    * 最后修改日期：2023/7/19
    * 备注：
    ******************************************************************/


    class MJIS_Agent_API MVCamera :public ICamera
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

