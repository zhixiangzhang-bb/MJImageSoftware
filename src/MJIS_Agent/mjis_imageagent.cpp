#include "mjis_imageagent.h"
#include <QDateTime>
#include <QDir>




ImageAgent::ImageAgent(QObject *parent)
	: QObject(parent), tab(nullptr), Camera(nullptr), save(nullptr), subtitle(nullptr), titlestate(false)
{

}




ImageAgent::ImageAgent(Tabwidget* tab):tab(tab), Camera(nullptr), save(nullptr), subtitle(nullptr), titlestate(false)
{

}



/**
 * @brief 析构函数
*/
ImageAgent::~ImageAgent()
{

}




//根据返回的ID创建窗口
void ImageAgent::CreateCamera(uint idex, mjis::ICamera::CameraType Type)
{
    if (Camera == nullptr) {
        switch (Type)
        {
        case mjis::ICamera::No:
            return;
        case mjis::ICamera::Local_Camera:
            Camera = std::shared_ptr<mjis::ICamera>(new mjis::LocalCamera());
            break;
        case mjis::ICamera::MV_Camera:
            Camera = std::shared_ptr<mjis::ICamera>(new mjis::MVCamera());
            break;
        default:
            return;
        }
    }
    else {
        return;
    }
    if (tab != nullptr) {
        Camera->setidx(idex);
        Camera->gainmessage();
        tab->SetState("已配置相机:" + Camera->Mess.ModelName + " 信息:" + Camera->Mess.SN);
        connect(Camera.get(), &mjis::ICamera::cameraReadQImage, this, &ImageAgent::ReadQImage);//将读取到的数据送入数据处理线程
        connect(this, &ImageAgent::UpdateImage, tab, &Tabwidget::ShowCameraQImage);//将处理后的图像写入UI
    }
}


//返回相机指针
mjis::ICamera* ImageAgent::ReturnCamera()
{
    return Camera.get();
}



//读取相机的图片
void ImageAgent::ReadQImage(cv::Mat image)
{    
    //设置字幕
    if (titlestate) {
        subtitle->processImage(image);
    }
    
    //图像处理其他操作
    if (ProcessList.size() > 0) {
        for (std::shared_ptr<mjlib::ImageProcess> var : ProcessList)
        {
            var->processImage(image);
        }
    }
    QImage qimage = MatImageToQt(image);
    emit UpdateImage(qimage);
}


//连接相机
void ImageAgent::ConnectCamera()
{
    Camera->open();
    if (Camera->isConnect()) {
        tab->SetNameStr("相机已连接，未启动采集工作");
    }
}


//断开相机连接
void ImageAgent::DisConnectCamera()
{
    Camera->close();
    if (!Camera->isConnect()) {
        tab->SetNameStr("相机已断开");
    }
}

//返回相机连接状态
bool ImageAgent::ReturnCameraConnect()
{
    return Camera->isConnect();
}


//连接相机
void ImageAgent::StartGrap()
{
    Camera->startGrap();
    if (Camera->isGrap()) {
        tab->SetNameStr("相机正在采集");
    }
}



void ImageAgent::StopGrap()
{
    try {
        Camera->stopGrap();
        if (Camera->isGrap()) {
            tab->SetNameStr("相机已连接，未启动采集工作");
        }
    }
    catch (const std::exception& e) {
    }
}


//返回相机采集状态
bool ImageAgent::ReturnCameraGrap()
{
    return Camera->isGrap();
}




//开始保存视频
void ImageAgent::StartSaveVideo(const std::string& Path, mjlib::ImageSaveVideo::VideoStyle Vdostyle, int frame_width, int  frame_height)
{
    try {
        save=std::make_shared<mjlib::ImageSaveVideo>();
        save->SetVideoParam(Path,  Vdostyle, Camera->ReturnFps(), frame_width, frame_height);
        ProcessList.append(save);
    }
    catch (const std::exception& e) {
    }
}


//停止保存视频
void ImageAgent::StopSaveVideo()
{
    ProcessList.removeAll(save);
    save=nullptr;
}


//返回保存视频状态
bool ImageAgent::ReturnSaveState()
{
    if (save == nullptr) {
        return false;
    }
    else {
        return true;
    }
}


//开始保存图像
void ImageAgent::StartSnapVideo(const QString& Path, mjlib::ImageSnapImage::ImageStyle Imgstyle, int frame_width, int  frame_height)
{
    try {
        // 获取当前日期和时间
        QDateTime currentDateTime = QDateTime::currentDateTime();

        // 将日期和时间格式化为字符串
        QString dateTimeString = currentDateTime.toString("yyyy_MM_dd hh_mm_ss");

        QString folderPath = Path+ dateTimeString;
        QDir dir;
        if (dir.mkdir(folderPath))
        {
            std::string str = (folderPath + "/试验数据").toLocal8Bit().toStdString();
            snap = std::make_shared<mjlib::ImageSnapImage>();
            snap->SetImageParam(str, Imgstyle, frame_width, frame_height);
            snap->SetAuto(true);
            ProcessList.append(snap);
        }
    }
    catch (const std::exception& e) {
    }
}


//停止保存图像
void ImageAgent::StopSnapVideo()
{
    ProcessList.removeAll(snap);
    snap = nullptr;
}


//返回保存图片状态
bool ImageAgent::ReturnSnapState()
{
    if (snap == nullptr) {
        return false;
    }
    else {
        return true;
    }
}


//开始显示字幕
void ImageAgent::StartSubtitle(std::string* title, std::string* data)
{
    subtitle = std::make_shared<mjlib::ImageSubTitle>(title, data);
    titlestate = true;
}



//停止显示字幕
void ImageAgent::StopSubtitle()
{
    titlestate = false;
    subtitle = nullptr;
}



//返回字幕显示状态
bool ImageAgent::ReturnSubState()
{
    return titlestate;
}

//应用字体设置
void ImageAgent::SetFont(uint offsetx, uint offsety, uint cR, uint cG, uint cB, uint fontheight)
{
    if (subtitle != nullptr)
    {
        subtitle->SetFontParam(offsetx, offsety, cR, cG, cB, fontheight);
    }
}


//打开图片
void ImageAgent::OpenImage(const QString& path)
{
    std::string str = path.toLocal8Bit().data();
    std::shared_ptr<mjlib::OpenImageFile> imagefile(new mjlib::OpenImageFile);
    cv::Mat image = imagefile->OpenImage(str);
    cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
    ProcessAdvanceStack.push(image);
    connect(this, &ImageAgent::UpdateImage, tab, &Tabwidget::ShowCameraQImage);
    emit UpdateImage(MatImageToQt(image));
}



//图像处理
void ImageAgent::ProcessImage(mjlib::ImageProcess* process)
{
    cv::Mat image = process->processImage(ProcessAdvanceStack.top());
    ProcessAdvanceStack.push(image);
    ProcessBackStack.clear();
    emit UpdateImage(MatImageToQt(image));
}



//图像处理回退
void ImageAgent::PopProcess()
{
    if (ProcessAdvanceStack.size() > 1)
    {
        ProcessBackStack.push(ProcessAdvanceStack.top());
        ProcessAdvanceStack.pop();
    }
    emit UpdateImage(MatImageToQt(ProcessAdvanceStack.top()));
}


//图像处理取消回退
void ImageAgent::BackProcess()
{
    if (ProcessBackStack.size() > 1)
    {
        ProcessAdvanceStack.push(ProcessBackStack.top());
        ProcessBackStack.pop();
    }
    emit UpdateImage(MatImageToQt(ProcessAdvanceStack.top()));
}



//绘制灰度直方图
std::tuple<std::vector<double>, std::vector<double>> ImageAgent::DrawHistogram()
{
    //::Histogram hist;
    //return hist.Statistics(ProcessAdvanceStack.top());  
    std::tuple<std::vector<double>, std::vector<double>> result;
    return result;
}



/**
 * @brief MAT转QIMAGE图片
 * @param src MAT图片
 * @return 返回QIMAGE图片
*/
QImage ImageAgent::MatImageToQt(cv::Mat& src)
{
    if (src.type() == CV_8UC1)
    {
        // 创建 QImage
        QImage dest((uchar*)src.data,src.cols, src.rows,static_cast<int>(src.step),QImage::Format_Grayscale8);
        return dest;
    }
    else if (src.type() == CV_8UC3)
    {
        const uchar* pSrc = (const uchar*)src.data;
        QImage qImage(src.data, src.cols, src.rows, src.step, QImage::Format_RGB888);
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

