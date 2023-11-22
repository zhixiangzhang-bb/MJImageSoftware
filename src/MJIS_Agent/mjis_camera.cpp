
#include "mjis_localcamera.h"


namespace mjis {

    LocalCamera::LocalCamera(QObject* parent)
        : ICamera{ parent }, time(new QTimer)
    {
        connectstate = false;
        grapstate = false;
    }


    void LocalCamera::setidx(uint idx)
    {
        this->idx = idx;
    }



    bool LocalCamera::open()
    {
        cap.open(idx);
        if (cap.isOpened()) {
            connectstate = true;
            return 0;
        }
        else {
            return 1;
        }
    }


    bool LocalCamera::close()
    {
        connectstate = false;

        //如果在采集先结束采集任务
        if (grapstate = true) {
            grapstate = false;
            time = nullptr;
        }

        if (!cap.isOpened())
        {
            cap.release();
            return false;
        }
        else
        {
            return true;
        }
    }


    //开始采集
    bool LocalCamera::startGrap()
    {
        double fps = cap.get(cv::CAP_PROP_FPS);
        connect(time.get(), &QTimer::timeout, this, &LocalCamera::ReadIamge);
        time->start(1000 / fps);
        grapstate = true;
        return grapstate;
    }


    //停止采集
    bool LocalCamera::stopGrap()
    {
        time->stop();
        time = nullptr;
        grapstate = false;
        if (time = nullptr) {
            return false;
        }
        else {
            return true;
        }
    }

    //正在连接状态
    bool LocalCamera::isConnect()
    {
        return connectstate;
    }


    //正在采集状态
    bool LocalCamera::isGrap()
    {
        return grapstate;
    }



    ICamera::Message LocalCamera::gainmessage()
    {
        cap.open(idx);
        if (cap.isOpened()) {
            Mess.idx = idx;
            Mess.ModelName = "本地相机" + QString::number(idx);//型号用图片宽度代替
            Mess.ipAddr = QString::number(cap.get(cv::CAP_PROP_FRAME_WIDTH));//型号用图片宽度代替
            Mess.MAC = QString::number(cap.get(cv::CAP_PROP_FRAME_HEIGHT));//IP地址用图片高度代替
            Mess.SN = QString::number(cap.get(cv::CAP_PROP_FPS));//MAC地址用分辨率代替
            cap.release();
        }
        return Mess;
    }



    uint LocalCamera::search()
    {
        return 0;
    }


    void LocalCamera::MVSetDefaultParameters()
    {

    }



    void LocalCamera::ReadIamge()
    {
        cv::Mat image;
        cap.read(image);
        //cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
        //cv::imshow("11", image);
        emit cameraReadQImage(image);
    }




    bool LocalCamera::setFPS(uint fps)
    {
        if (!cap.isOpened()) {
            open();
        }
        cap.set(cv::CAP_PROP_FPS, fps);
        double fpst = cap.get(cv::CAP_PROP_FPS);
        cap.release();
        if (fpst == fps) {
            return 0;
        }
        else {
            return 1;
        }
    }


    bool LocalCamera::CameraSetSheet()
    {
        return 0;
    }


    //获取相机ID
    int LocalCamera::GetCameraIdx()
    {
        return idx;
    }


    //返回相机ID
    int LocalCamera::ReturnFps()
    {
        return fps;
    }

}