#include "ImageProcessManage.h"



ImageProcessManage::ImageProcessManage(QObject* parent)
    : titlecu(false), subtitle(new ImageSubTitle(nullptr, nullptr)), QObject{ parent }
{	
    
}


ImageProcessManage::ImageProcessManage(std::string* title, std::string* data)
    : titlecu(false), subtitle(new ImageSubTitle(title, data))
{

}



ImageProcessManage::~ImageProcessManage()
{

}


void ImageProcessManage::ReadQImage(cv::Mat& image)
{
    this->ImageProcessExecute(image);
}




void ImageProcessManage::SetFont(uint offsetx, uint offsety, uint cR, uint cG, uint cB, uint fontheight)
{
    subtitle->SetFontParam(offsetx, offsety, cR, cG, cB, fontheight);
}



void ImageProcessManage::SetTitle(std::string* title,std::string* data)
{
    subtitle->SetTitle(title, data);
}



void ImageProcessManage::ImageProcessExecute(cv::Mat& image)
{
	mutex.lock();
	for (ImageProcess* Process : ProcessQueue) 
	{
		image=Process->processImage(image);
	}
	mutex.unlock();
    if(titlecu)
    {
        this->ImageSubTitleExecute(image);
    }
    else
    {
        this->ImageFileExecute(image);
    }
}



void ImageProcessManage::ImageSubTitleExecute(cv::Mat& image)
{    
    image=subtitle->processImage(image);
    ImageFileExecute(image);
}



void ImageProcessManage::ImageFileExecute(cv::Mat& image)
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




void ImageProcessManage::PushImageProcess(ImageProcess* process)
{
	ProcessQueue.append(process);
}



void ImageProcessManage::BackImageProcess(ImageProcess* process)
{
	ProcessQueue.removeAll(process);
}



void ImageProcessManage::PushImageFile(ImageProcess* process)
{
	FileQueue.append(process);
}



void ImageProcessManage::BackImageFile(ImageProcess* process)
{
	FileQueue.removeAll(process);
}



void ImageProcessManage::SetTitleCuValue(bool cu)
{
    this->titlecu = cu;
}


bool ImageProcessManage::TitleCuValue()
{
    return titlecu;
}



QImage ImageProcessManage::MatImageToQt(cv::Mat src)
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

