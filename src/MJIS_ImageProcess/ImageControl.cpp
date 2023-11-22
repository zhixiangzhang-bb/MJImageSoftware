
#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>

#ifndef GLOG_NO_ABBREVIATED_SEVERITIES
# ifdef ERROR
#  undef ERROR
# endif
const int INFO = GLOG_INFO, WARNING = GLOG_WARNING,
ERROR = GLOG_ERROR, FATAL = GLOG_FATAL;
#endif



#include "ImageControl.h"


ImageControl::ImageControl():pcif(new ProcessingInterface), dock(new MyDockWidget)
{
    dock->setWindowTitle("图像处理");
}


ImageControl::ImageControl(std::shared_ptr<MyDockWidget> dock) :pcif(new ProcessingInterface), dock(dock)
{
    dock->setWindowTitle("图像处理");
}


ImageControl::~ImageControl()
{
    ProcessAdvanceStack.clear();
    if(!ProcessAdvanceStack.empty()){
        ProcessAdvanceStack.pop();
    }
    ProcessBackStack.clear();
    if (!ProcessBackStack.empty()) {
        ProcessBackStack.pop();
    }
}


//打开图片
MyDockWidget* ImageControl::OpenImage(std::string& path)
{
    try {
        std::shared_ptr<OpenImageFile> imagefile(new OpenImageFile);
        cv::Mat image = imagefile->OpenImage(path);
        ProcessAdvanceStack.push(image);
        QImage img = MatImageToQt(image);
        dock->returnCameraQImage(img);
        LOG(INFO) << "图像处理模块：打开图片成功";
    }
    catch(const std::exception& e){
        LOG(ERROR) << "图像处理模块：打开图片失败"<<e.what();
    }
	return dock.get();
}



//打开图片
MyDockWidget* ImageControl::ReturnDock()
{
    return dock.get();
}


void ImageControl::ImageProcessResult(ImageProcess* process)
{
    try {
        auto startTime = std::chrono::high_resolution_clock::now();
        cv::Mat processiamge = process->processImage(ProcessAdvanceStack.top());
        QImage img = MatImageToQt(processiamge);
        ProcessAdvanceStack.push(processiamge);
        dock->returnCameraQImage(img);
        LOG(INFO) << "图像处理模块：处理成功";
        // 获取当前时间点
        auto endTime = std::chrono::high_resolution_clock::now();
        // 计算函数执行时间（以毫秒为单位）
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

        pcif->AddStep(QString::fromStdString(process->ReturnName()), QString::fromStdString(process->ReturnName()), duration.count());

    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：处理失败 异常：："<< e.what();
    }
}



//直方图显示
QVector<QVector<double>> ImageControl::StatisticsImage(ImageStatistics* statistics)
{
    std::vector<std::vector<double>> vec = statistics->Statistics(ProcessAdvanceStack.top());
    QVector<QVector<double>> result;
    if (!vec.empty()) {
        result.append(QVector<double>(vec[0].begin(), vec[0].end()));
        result.append(QVector<double>(vec[1].begin(), vec[1].end()));
        LOG(INFO) << "图像处理模块：直方图数据转换成功";
        return result;
    }
    else {
        LOG(ERROR) << "图像处理模块：直方图数据转换失败";
        return result;
    }

}



void ImageControl::PopProcess()
{    
    if (ProcessAdvanceStack.size()>1)
    {
        ProcessAdvanceStack.pop();
    }
    QImage img = MatImageToQt(ProcessAdvanceStack.top());
    dock->returnCameraQImage(img);
    pcif->DeleteStep();
}



void ImageControl::PushProcess()
{

}



//根据地址保存图片
void ImageControl::SaveImage(std::string path)
{
    cv::Mat img = ProcessAdvanceStack.top();
    ImageSnapImage snap;
    snap.SetImageParam(path, ImageSnapImage::PNG, img.size().width, img.size().height);
    snap.processImage(img);
}



    
QImage ImageControl::MatImageToQt(cv::Mat src)
{
    if (src.type() == CV_8UC1)
    {
        QImage image = QImage(src.data, src.cols, src.rows, static_cast<int>(src.step), QImage::Format_Grayscale8);
        return image;
    }
    else if (src.type() == CV_8UC3)
    {
        QImage image = QImage(src.data, src.cols, src.rows, static_cast<int>(src.step), QImage::Format_RGB888);
        return image;
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



/// <summary>
/// 返回界面指针，这里指针交给自己来释放，外部不对界面资源做控制，仅作为使用
/// </summary>
/// <returns></returns>界面指针
ProcessingInterface* ImageControl::ReturnInterface()
{
    return pcif.get();
}


