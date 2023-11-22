#include "ImageMainContoller.h"
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>



ImageMainContoller::ImageMainContoller(QObject *parent)
	: QObject(parent)
{
    
}



ImageMainContoller::~ImageMainContoller()
{

}


ICamera* ImageMainContoller::createCamera(const CameraType cameraType)
{
    switch (cameraType) {
    case Local_Camera:
        return new LocalCamera();
        break;
    case MV_Camera:
        return new MVCamera();
        break;
    default:
        return nullptr;
        break;
    }
}



MyDockWidget* ImageMainContoller::CreateStructure(uint idex, CameraType Type)
{
    ImageGroup* ImageG = new ImageGroup;
    ImageG->Camera = createCamera(Type);
    ImageG->Camera->setidx(idex);
    bool state = TryConnectCamera(ImageG->Camera);
    if (!state)
    {        
        ImageG->ImageProcess = new ImageProcessManage;
        MyDockWidget* Video = new MyDockWidget;
        ImageG->CameraThread = new QThread;
        if (!ImageG->CameraThread->isRunning()) {
            ImageG->CameraThread->start();
        }
        ImageG->Camera->setidx(idex);
        ImageG->Camera->gainmessage();
        ImageG->Camera->moveToThread(ImageG->CameraThread);
        ImageG->ImageProcess->moveToThread(ImageG->CameraThread);
        ImageG->Camera->MVSetDefaultParameters();
        VideoMap.insert(Video, ImageG);
        QString title = "已配置相机:" + ImageG->Camera->Mess.ModelName + " IP地址:" + ImageG->Camera->Mess.ipAddr;
        Video->setWindowTitle(title);
        connect(ImageG->Camera, &ICamera::cameraReadQImage, ImageG->ImageProcess, &ImageProcessManage::ReadQImage);//将读取到的数据送入数据处理线程
        connect(ImageG->ImageProcess, &ImageProcessManage::ReturnProcessImage, Video, &MyDockWidget::returnCameraQImage);//将处理后的图像写入UI
        return Video;
    }
    else
    {
        delete ImageG->Camera;
        delete ImageG;
        return nullptr;
    }
}



MyDockWidget* ImageMainContoller::OpenImage(std::string stdFilePath)
{
    ImageGroup* ImageG = new ImageGroup;
    ImageG->ImageProcess = new ImageProcessManage;
    MyDockWidget* Video = new MyDockWidget;
    VideoMap.insert(Video, ImageG);
    connect(ImageG->ImageProcess, &ImageProcessManage::ReturnProcessImage, Video, &MyDockWidget::returnCameraQImage);//将处理后的图像写入UI
    cv::Mat image = cv::imread(stdFilePath);
    ImageG->ImageProcess->ReadQImage(image);
    return  Video;
}




void ImageMainContoller::ReleaseResource(MyDockWidget* Video)
{
    if (VideoMap.value(Video) != nullptr) {
        VideoMap.value(Video)->CameraThread->quit();
        delete VideoMap.value(Video)->Camera;
        delete VideoMap.value(Video)->ImageProcess;
        delete VideoMap.value(Video)->CameraThread;
        VideoMap.remove(Video);
        VideoList.removeAll(Video);
    }
}



bool ImageMainContoller::TryConnectCamera(ICamera* Cmaera)
{
    if (!Cmaera->open())
    {
        Cmaera->close();
        return false;
    }
    else
    {
        return true;
    }
}


void ImageMainContoller::ConnectCamera(MyDockWidget* Video)
{
    VideoMap.value(Video)->Camera->open();
}


void ImageMainContoller::DisConnectCamera(MyDockWidget* Video)
{
    VideoMap.value(Video)->Camera->close();
}


void ImageMainContoller::StartGrap(MyDockWidget* Video)
{
    VideoMap.value(Video)->Camera->startGrap();
}


void ImageMainContoller::StopGrap(MyDockWidget* Video)
{
    VideoMap.value(Video)->Camera->stopGrap();
}



bool ImageMainContoller::CameraisRunning(MyDockWidget* Video)
{
    return 0;
}



void ImageMainContoller::StartSaveVideo(MyDockWidget* Video, std::string Path, VideoStyle Vdostyle, uint fps, int frame_width, int  frame_height)
{
    savevideo = new ImageSaveVideo();
    savevideo->SetVideoParam(Path, Vdostyle, fps, frame_width, frame_height);
    VideoMap.value(Video)->ImageProcess->PushImageProcess(savevideo);
}



void ImageMainContoller::StopSaveVideo(MyDockWidget* Video)
{
    VideoMap.value(Video)->ImageProcess->BackImageProcess(savevideo);   
    delete savevideo;
}


void ImageMainContoller::StartSnapVideo(MyDockWidget* Video,std::string Path, ImageStyle Imgstyle, int frame_width, int  frame_height)
{
    sanpimage = new ImageSnapImage;
    sanpimage->SetImageParam(Path, Imgstyle, frame_width, frame_height);
    //VideoMap.value(Video)->ImageProcess->PushImageFile(sanpimage);
}


void ImageMainContoller::StopSnapVideo(MyDockWidget* Video)
{
    //VideoMap.value(Video)->ImageProcess->BackImageFile(sanpimage);
    delete sanpimage;
}



void ImageMainContoller::StartSubTitle(MyDockWidget* Video)
{
    //ideoMap.value(Video)->ImageProcess->subtitle = new ImageSubTitle(offsetx, offsety, clor.red(), clor.green(), clor.blue(), 18);
    //VideoMap.value(Video)->ImageProcess->subtitle->SetTitle("空化观测试验");
    VideoMap.value(Video)->ImageProcess->titlecu = true;//这里先按这个模式设置字幕
    //VideoMap.value(Video)->ImageProcess->PushImageProcess(subtitle);
}



void ImageMainContoller::SetFontParam(MyDockWidget* Video, uint offsetx, uint offsety, uint cR, uint cG, uint cB, uint fontheight)//设置字体格式
{
    VideoMap.value(Video)->ImageProcess->SetFont(offsetx, offsety, cR, cG, cB, fontheight);
}



void ImageMainContoller::SetSubTitle(MyDockWidget* Video,std::string title)
{
    VideoMap.value(Video)->ImageProcess->SetTitle(title);
}



void ImageMainContoller::StopSubTitle(MyDockWidget* Video)
{
    VideoMap.value(Video)->ImageProcess->titlecu = false;//这里先按这个模式设置字幕
}
