
#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>

#ifndef GLOG_NO_ABBREVIATED_SEVERITIES
# ifdef ERROR
#  undef ERROR
# endif
const int INFO = GLOG_INFO, WARNING = GLOG_WARNING,
ERROR = GLOG_ERROR, FATAL = GLOG_FATAL;
#endif



#include "CameraImageManage.h"




CameraImageManage::CameraImageManage(QObject* parent)
	:QObject(parent),  savestate(false), snapstate(false), titlecu(false), subtitle(new ImageSubTitle(nullptr,nullptr))
{

}


CameraImageManage::~CameraImageManage()
{

}



//根据返回的ID创建窗口
MyDockWidget* CameraImageManage::CreateCamera(uint idex, ICamera::CameraType Type)
{
    Camera = std::shared_ptr<ICamera>(CameraManage::CreateCamera(idex, Type));
    Camera->setidx(idex);

    bool state=CameraManage::TryConnectCamera(Camera.get());

    if (!state)
    {
        LOG(INFO) << "相机处理模块：相机存在且没被占用，执行配置操作";
        //测试连接成功添加各种变量
        DockWidget = std::make_shared<MyDockWidget>();
        Camera->gainmessage();
        Camera->MVSetDefaultParameters();
        QString title = "已配置相机:" + Camera->Mess.ModelName + " IP地址:" + Camera->Mess.ipAddr;
        DockWidget->setWindowTitle(title);
        connect(Camera.get(), &ICamera::cameraReadQImage, this, &CameraImageManage::ReadQImage);//将读取到的数据送入数据处理线程
        connect(this, &CameraImageManage::ReturnProcessImage, DockWidget.get(), &MyDockWidget::returnCameraQImage);//将处理后的图像写入UI
        return DockWidget.get();
    }
    else {
        LOG(WARNING) << "相机处理模块：相机不存在或相机被占用";
        return nullptr;
    }
}



void CameraImageManage::StartGrap(int idx)
{
    try {
        Camera->startGrap();
        LOG(INFO) << "相机处理模块：相机开始采集";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "相机处理模块：相机触发采集失败";
    }
}



void CameraImageManage::StopGrap(int idx)
{
    try {
        Camera->stopGrap();
        LOG(INFO) << "相机处理模块：相机停止采集";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "相机处理模块：相机触发停止采集失败";
    }
}



void CameraImageManage::ConnectCamera(int idx)
{
    Camera->open();
}



void CameraImageManage::DisConnectCamera(int idx)
{
    Camera->close();
}



//开始保存视频
void CameraImageManage::StartSaveVideo(std::string& Path, ImageSaveVideo::VideoStyle Vdostyle, uint fps, int frame_width, int  frame_height, int idx)
{
    SavetVideo = std::make_shared<ImageSaveVideo>();
    SavetVideo->SetVideoParam(Path, Vdostyle, fps, frame_width, frame_height);
    this->PushImageFile(SavetVideo.get());
    savestate = true;
}


//停止保存视频
void CameraImageManage::StopSaveVideo(int idx)
{
    this->BackImageFile(SavetVideo.get());
    SavetVideo.reset();
    savestate = false;
}



//开始截取图片
void CameraImageManage::StartSnapVideo(std::string& Path, ImageSnapImage::ImageStyle Imgstyle, int frame_width, int  frame_height, int idx)
{
    SavetImage = std::make_shared<ImageSnapImage>();
    SavetImage->SetImageParam(Path, Imgstyle, frame_width, frame_height);
    SavetImage->SetAuto(true);
    this->PushImageFile(SavetImage.get());
    snapstate = true;
}


//停止截取图片
void CameraImageManage::StopSnapVideo(int idx)
{
    this->BackImageFile(SavetImage.get());
    snapstate = false;
}


//开始字幕
void CameraImageManage::StartSubTitle(int idx)
{
    this->titlecu = true;
}



//设置字体格式
void CameraImageManage::SetFontParam( uint offsetx, uint offsety, uint cR, uint cG, uint cB, uint fontheight, int idx)
{
    subtitle->SetFontParam(offsetx, offsety, cR, cG, cB, fontheight);
}


//设置字幕
void CameraImageManage::SetSubTitle(std::string* title, std::string* data, int idx)
{
    subtitle->SetTitle(title, data);
}


//停止字幕显示
void CameraImageManage::StopSubTitle(int idx)
{
    this->titlecu = false;
}



void CameraImageManage::OpenCameraSetSheet(int idx)
{
    Camera->CameraSetSheet();
}



//获取相机ID
int CameraImageManage::GetCameraId(int idx)
{
    return Camera->GetCameraIdx();
}


//判断是否已经添加相机了
bool CameraImageManage::GetCameraIdxState()
{
    if (Camera->GetCameraIdx() >= 0) {
        return true;
    }
    else {
        return false;
    }
}



//判断相机是否还在连接
bool CameraImageManage::GetCameraConnectState()
{
    return Camera->isConnect();
}


//判断相机是否在采集
bool CameraImageManage::GetCameraGrapState()
{
    return Camera->isGrap();
}


//判断是否在录制
bool CameraImageManage::GetSaveState()
{
    return savestate;
}


//判断是否在截图
bool CameraImageManage::GetSnapState()
{
    return snapstate;
}


//判断是否显示字幕
bool CameraImageManage::GetSubTitleState()
{
    return this->TitleCuValue();
}



void CameraImageManage::ReadQImage(cv::Mat& image)
{
    this->ImageProcessExecute(image);
}



void CameraImageManage::ImageProcessExecute(cv::Mat& image)
{
    mutex.lock();
    for (ImageProcess* Process : ProcessQueue)
    {
        image = Process->processImage(image);
    }
    mutex.unlock();
    if (titlecu)
    {
        this->ImageSubTitleExecute(image);
    }
    else
    {
        this->ImageFileExecute(image);
    }
}



void CameraImageManage::ImageSubTitleExecute(cv::Mat& image)
{
    image = subtitle->processImage(image);
    ImageFileExecute(image);
}



void CameraImageManage::ImageFileExecute(cv::Mat& image)
{
    mutex.lock();
    if (!FileQueue.empty()) {
        for (ImageProcess* File : FileQueue)
        {
            image = File->processImage(image);
        }
    }
    mutex.unlock();
    QImage img = MatImageToQt(image);
    emit ReturnProcessImage(img);
}




void CameraImageManage::PushImageProcess(ImageProcess* process)
{
    ProcessQueue.append(process);
}



void CameraImageManage::BackImageProcess(ImageProcess* process)
{
    ProcessQueue.removeAll(process);
}



void CameraImageManage::PushImageFile(ImageProcess* process)
{
    FileQueue.append(process);
}



void CameraImageManage::BackImageFile(ImageProcess* process)
{
    FileQueue.removeAll(process);
}



bool CameraImageManage::TitleCuValue()
{
    return titlecu;
}



QImage CameraImageManage::MatImageToQt(cv::Mat src)
{
    if (src.type() == CV_8UC1)
    {
        QImage qImage(src.cols, src.rows, QImage::Format_Indexed8);
        qImage.setColorCount(256);
        for (int i = 0; i < 256; i++)
        {
            qImage.setColor(i, qRgb(i, i, i));
        }
        uchar* pSrc = src.data;
        for (int row = 0; row < src.rows; row++)
        {
            uchar* pDest = qImage.scanLine(row);
            bool a = memcmp(pDest, pSrc, src.cols);
            pSrc += src.step;
        }
        return qImage;
    }
    else if (src.type() == CV_8UC3)
    {
        const uchar* pSrc = (const uchar*)src.data;
        QImage qImage(pSrc, src.cols, src.rows, src.step, QImage::Format_RGB888);
        return qImage.rgbSwapped();
    }
    else if (src.type() == CV_8UC4)
    {
        const uchar* pSrc = (const uchar*)src.data;
        QImage qImage(pSrc, src.cols, src.rows, src.step, QImage::Format_ARGB32);
        return qImage.copy();
    }
    else
    {
        return QImage();
    }
}

