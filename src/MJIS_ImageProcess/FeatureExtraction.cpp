#include "FeatureExtraction.h"
#include <opencv2/xfeatures2d.hpp>


SIFT::SIFT()
{

}


cv::Mat SIFT::processImage(const cv::Mat& image)
{
    // 创建SIFT对象
    cv::Ptr<cv::SIFT> sift = cv::SIFT::create();

    // 检测关键点并计算描述符
    std::vector<cv::KeyPoint> keypoints;
    cv::Mat descriptors;
    sift->detectAndCompute(image, cv::noArray(), keypoints, descriptors);

    // 在图像上绘制关键点
    cv::Mat outputImage;
    cv::drawKeypoints(image, keypoints, outputImage);

	return outputImage;
}


//返回处理名称
std::string SIFT::ReturnName()
{
    return "SIFT特征查找";
}





/*






*/




SURF::SURF()
{

}


cv::Mat SURF::processImage(const cv::Mat& image)
{
    // 创建SURF对象
    cv::Ptr<cv::Feature2D> surf = cv::xfeatures2d::SURF::create();

    // 检测关键点和计算描述符
    std::vector<cv::KeyPoint> keypoints;
    cv::Mat descriptors;
    surf->detectAndCompute(image, cv::noArray(), keypoints, descriptors);

    // 在图像上绘制关键点
    cv::Mat image_with_keypoints;
    cv::drawKeypoints(image, keypoints, image_with_keypoints);

    return image_with_keypoints;
}

//返回处理名称
std::string SURF::ReturnName()
{
    return "SURF特征查找";
}


/*






*/



BRISK::BRISK()
{

}


cv::Mat BRISK::processImage(const cv::Mat& image)
{
    // 创建SURF对象
    cv::Ptr<cv::Feature2D> surf = cv::xfeatures2d::SURF::create();

    // 检测关键点和计算描述符
    std::vector<cv::KeyPoint> keypoints;
    cv::Mat descriptors;
    surf->detectAndCompute(image, cv::noArray(), keypoints, descriptors);

    // 在图像上绘制关键点
    cv::Mat image_with_keypoints;
    cv::drawKeypoints(image, keypoints, image_with_keypoints);

    return image_with_keypoints;
}


//返回处理名称
std::string BRISK::ReturnName()
{
    return "BRISK特征查找";
}




/*






*/



AKAZE::AKAZE()
{

}


cv::Mat AKAZE::processImage(const cv::Mat& image)
{
    // 创建AKAZE特征提取器对象
    cv::Ptr<cv::AKAZE> akaze = cv::AKAZE::create();

    // 检测和描述图像中的特征点
    std::vector<cv::KeyPoint> keypoints;
    cv::Mat descriptors;
    akaze->detectAndCompute(image, cv::noArray(), keypoints, descriptors);

    // 在图像上绘制特征点
    cv::Mat image_with_keypoints;
    cv::drawKeypoints(image, keypoints, image_with_keypoints, cv::Scalar(0, 0, 255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    return image_with_keypoints;
}


//返回处理名称
std::string AKAZE::ReturnName()
{
    return "AKAZE特征查找";
}

