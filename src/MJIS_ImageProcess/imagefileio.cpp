#include "imagefileio.h"

ImageSaveVideo::ImageSaveVideo(ImageProcess* parent)
{

}

ImageSaveVideo::~ImageSaveVideo()
{
    StopSaveVideo();
}



//根据配置打开视频文件
void ImageSaveVideo::SetVideoParam(const std::string& Path,VideoStyle Vdostyle,uint fps, int frame_width, int  frame_height)
{   
    this->frame_width = frame_width;
    this->frame_height = frame_height;
    switch (Vdostyle)
    {
    case ImageSaveVideo::MJPG:
        SaveVideoState = VideoIO.open(Path + ".avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, cv::Size(frame_width, frame_height));
        break;
    case ImageSaveVideo::MP4V:
        SaveVideoState = VideoIO.open(Path + ".mp4", cv::VideoWriter::fourcc('M', 'P', '4', 'V'), fps, cv::Size(frame_width, frame_height));
        break;
    case ImageSaveVideo::XVID:
        SaveVideoState = VideoIO.open(Path + ".avi", cv::VideoWriter::fourcc('X', 'V', 'I', 'D'), fps, cv::Size(frame_width, frame_height));
        break;
    case ImageSaveVideo::H264:
        SaveVideoState = VideoIO.open(Path + ".mp4", cv::VideoWriter::fourcc('H', '2', '6', '5'), fps, cv::Size(frame_width, frame_height));
        break;
    default:
        break;
    }
}


//执行一次写入一次
cv::Mat ImageSaveVideo::processImage(const cv::Mat& image)
{
    if (SaveVideoState) {
        cv::Mat proimage;
        cv::resize(image, proimage, cv::Size(frame_width, frame_height));
        VideoIO.write(proimage);
    }
    return image;
}


//停止录制后释放资源
void ImageSaveVideo::StopSaveVideo()
{
    VideoIO.release();
}


//播放视频文件
void ImageSaveVideo::LoadVideo(std::string path)
{
    cv::VideoCapture video(path);
    if (!video.isOpened()) {
        LoadVideoState=false;
        return;
    }else{
        LoadVideoState=true;
        double fps = video.get(cv::CAP_PROP_FPS);
        cv::Mat frame;
        while (true) {
            // 逐帧读取视频
            if (!video.read(frame)) {
                video.release();
                break;
            }
            //QImage img=ImageProcess::MatImageToQt(frame);
            //emit ReturnLoadVideo(img);

            cv::waitKey(1000/fps);
        }
    }
}




//返回处理名称
std::string ImageSaveVideo::ReturnName()
{
    return "保存视频";
}



/*

图片采集逻辑

*/





ImageSnapImage::ImageSnapImage(ImageProcess* parent):num(0), autocu(false)
{

}



//根据配置设置图片保存类型
void ImageSnapImage::SetImageParam(const std::string& Path, ImageStyle Imgstyle, int frame_width, int  frame_height)
{
    this->path = Path;
    this->frame_width = frame_width;
    this->frame_height = frame_height;
    switch (Imgstyle) {
    case JPEG:
        format = ".jpeg";
        break;
    case PNG:
        format = ".png";
        break;
    case BMP:
        format = ".bmp";
        break;
    case TIFF:
        format = ".tiff";
        break;
    default:
        break;
    }
}



//设置保存路径
void ImageSnapImage::SetImagePath(std::string& Path)
{
    this->path = Path;
}



//设置自动化采集
void ImageSnapImage::SetAuto(bool autocu)
{
    this->autocu = autocu;
    num = 0;
}



//执行一次写入一次
cv::Mat ImageSnapImage::processImage(const cv::Mat& image)
{
    cv::Mat proimage;
    std::string pathstr;
    if (autocu) {
        pathstr = path +std::to_string(num)+format;
        num++;
    }
    cv::resize(image, proimage, cv::Size(frame_width, frame_height));
    cv::imwrite(pathstr, image);
    return image;
}


//返回处理名称
std::string ImageSnapImage::ReturnName()
{
    return "采集图片";
}




/*
打开图片逻辑分隔
*/





OpenImageFile::OpenImageFile(ImageProcess* parent)
{
    
}



cv::Mat OpenImageFile::OpenImage(std::string& Path)
{
    cv::Mat image = cv::imread(cv::String(Path.begin(), Path.end()));
    if (!image.empty()) {
        cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
        return image;
    }
    else {
        return cv::Mat();
    }
}


