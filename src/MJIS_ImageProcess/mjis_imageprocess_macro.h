#pragma once



#include <QDockWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QWheelEvent>
#include "mjlib_vision_api.h"


#if defined(MJIS_ImageProcess)
#  define MJIS_ImageProcess_API Q_DECL_EXPORT
#else
#  define MJIS_ImageProcess_API Q_DECL_IMPORT
#endif




/// <summary>
/// 
/// </summary> MAT转成QT图片，采用内联形式加速
/// <param name="src"></param>
/// <returns></returns>返回QImage
inline QImage MatImage2Qt(cv::Mat& src)
{
    if (src.type() == CV_8UC1)
    {
        // 创建 QImage
        QImage dest((uchar*)src.data, src.cols, src.rows, static_cast<int>(src.step), QImage::Format_Grayscale8);
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


