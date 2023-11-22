
#include "mjis_camera.h"
#include "MVGigE.h"
#include "MVImageC.h"
#include "MVCamProptySheet.h"


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


    /*****************************************************************
    * 类名称： 维视相机类
    * 功能描述： 从相机基类继承并重写部分函数，做为维视相机专用类
    * 作者：zzx
    * 创建日期：2023/7/6
    * 最后修改：zzx
    * 最后修改日期：2023/7/19
    * 备注：
    ******************************************************************/


    int __stdcall StreamCB(MV_IMAGE_INFO* pInfo, ULONG_PTR nUserVal)//回调函数，由相机触发
    {
        MVCamera* pWd = (MVCamera*)nUserVal;
        return (pWd->showStreamOnLabel(pInfo));
    }



    MVCamera::MVCamera(QObject* parent)
        : ICamera{ parent }
        , hCam(nullptr)
        , m_hImg(nullptr)
        , m_hPropDlg(nullptr)
        , m_hProperty(nullptr)
    {
        connectstate = false;
        grapstate = false;
    }



    void MVCamera::setidx(uint idx)
    {
        this->idx = idx;
    }



    uint MVCamera::search()
    {
        MVInitLib();
        int nCams = 0;
        bool state = MVEnumerateAllDevices(&nCams);
        if (state == MVST_SUCCESS) {
            return nCams;
        }
        else {
            return 0;
        }
    }


    bool MVCamera::open()
    {
        MVInitLib();
        if (hCam == NULL)
        {
            MVSTATUS_CODES state = MVOpenCamByIndex(idx, &hCam);
            connectstate = !state;
            MVCamProptySheetInit(&m_hProperty, hCam, 0, LPCTSTR("Propty"));
            return state;
        }
        else
        {
            return true;
        }

    }



    bool MVCamera::close()
    {
        bool state = MVCloseCam(hCam);
        if (state == MVST_SUCCESS)
        {
            hCam = NULL;
        }
        connectstate = false;
        return state;
    }


    ICamera::Message MVCamera::gainmessage()
    {
        CamInfo = new MVCamInfo;
        bool state = MVGetDevInfo(idx, CamInfo);
        if (state == MVST_SUCCESS) {
            Mess.ipAddr = QString::number(CamInfo->mIpAddr[0]) + '.' +
                QString::number(CamInfo->mIpAddr[1]) + '.' +
                QString::number(CamInfo->mIpAddr[2]) + '.' +
                QString::number(CamInfo->mIpAddr[3]);
            Mess.ModelName = CamInfo->mModelName;
            for (int var = 0; var < 6; ++var) {
                Mess.MAC.append(':' + QString::number(uint(CamInfo->m_IfMAC[var]), 16));
            }
            Mess.SN = CamInfo->mSerialNumber;
            //MVCloseCam(hCam);
            return Mess;
        }
        else {
            return Mess;
        }
    }


    bool MVCamera::startGrap()
    {
        if (connectstate) {
            bool state = MVStartGrab(hCam, StreamCB, (ULONG_PTR)this);
            if (!(state == MVST_SUCCESS))
            {
                if (m_hPropDlg != NULL)
                {
                    MVCamProptySheetCameraRun(m_hPropDlg, MVCameraRun_ON);
                }
            }
            grapstate = !state;
            return state;
        }
        else {
            return true;
        }
    }


    bool MVCamera::stopGrap()
    {
        grapstate = false;
        return MVStopGrab(hCam);
    }

    bool MVCamera::setFPS(uint fps)
    {
        return 0;
    }


    bool MVCamera::isConnect()
    {
        return connectstate;
    }



    bool MVCamera::isGrap()
    {
        return grapstate;
    }


    bool MVCamera::CameraSetSheet()
    {
        return MVCamProptySheetShow(m_hProperty);
    }


    void MVCamera::MVSetDefaultParameters()//初始化相机设置
    {
        this->open();
        MVSTATUS_CODES state = MVSetPacketSize(hCam, 1316);//设置网络包格式，初始化以最小写入保证接收图片
        TriggerModeEnums enumMode;
        MVGetTriggerMode(hCam, &enumMode);
        if (enumMode != TriggerMode_Off)
        {
            //设置为连续非触发模式
            MVSetTriggerMode(hCam, TriggerMode_Off);
        }
        int w, h;
        MV_PixelFormatEnums PixelFormat;
        MVGetWidth(hCam, &w);
        MVGetHeight(hCam, &h);
        MVGetPixelFormat(hCam, &PixelFormat);
        //根据相机的宽、高、像素格式创建图像
        if (PixelFormat == PixelFormat_Mono8)
        {
            this->m_hImg = MVImageCreate(w, h, 8);
        }
        else
        {
            this->m_hImg = MVImageCreate(w, h, 24);
        }
        //设置相机属性页
        if (m_hPropDlg == NULL)
        {
            //创建及初始化属性页对话框
            const char t_Title[] = "Camera Properties";
            LPCTSTR strCaption = (LPCTSTR)t_Title;
            MVCamProptySheetCreateEx(&m_hPropDlg, hCam, 0, strCaption, 0xffff);
            if (m_hPropDlg == NULL)
            {
                return;
            }
        }
        this->close();
    }



    //将读到的图像数据转成MAT
    cv::Mat MVCamera::img2cvMat(HANDLE hImg)
    {
        int width = MVImageGetWidth(hImg);
        int height = MVImageGetHeight(hImg);
        int bpp = MVImageGetBPP(hImg);
        int pitch = MVImageGetPitch(hImg);
        unsigned char* pImgData = (unsigned char*)MVImageGetBits(hImg);
        if (bpp == 8)
        {
            cv::Mat matImage(height, width, CV_8UC1);
            memcpy(&matImage.data, pImgData, width * height);
            return matImage;
        }
        else if (bpp == 24)
        {
            cv::Mat matImage(height, width, CV_8UC3);
            memcpy(matImage.data, pImgData, width * height * 3);
            return matImage;
        }
        else
        {
            return cv::Mat();
        }
    }



    int MVCamera::showStreamOnLabel(MV_IMAGE_INFO* pInfo)
    {
        MVInfo2Image(hCam, pInfo, (MVImage*)m_hImg);
        cv::Mat cvImage = img2cvMat(m_hImg);
        emit cameraReadQImage(cvImage);
        return 0;
    }



    //获取相机ID
    int MVCamera::GetCameraIdx()
    {
        return idx;
    }



    //返回相机ID
    int MVCamera::ReturnFps()
    {
        return fps;
    }
}