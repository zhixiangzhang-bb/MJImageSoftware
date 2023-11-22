#pragma once

#include <QImage>
#include <QObject>
#include <opencv2/opencv.hpp>


#if defined(MJIS_Camera)
#  define Camera_API Q_DECL_EXPORT
#else
#  define Camera_API Q_DECL_IMPORT
#endif


/*****************************************************************
* 类名称：相机基类
* 功能描述：
* 作者：zzx
* 创建日期：
* 最后修改：zzx
* 最后修改日期：
* 备注：
******************************************************************/

namespace mjis {

    class  Camera_API ICamera : public QObject {

        Q_OBJECT
    public:

        //相机状态枚举
        enum  CameraState {
            SUCCESS,//成功
            ERROR,//错误
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

}