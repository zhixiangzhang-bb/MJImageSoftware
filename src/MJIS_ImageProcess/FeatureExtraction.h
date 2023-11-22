#pragma once
#include "imageprocess.h"



/*****************************************************************
* 类名称：SIFT（尺度不变特征变换）
* 功能描述：SIFT是一种用于检测和描述图像中的稳定特征点的算法。它对图像的尺度、旋转和亮度变化具有很强的不变性。
* 作者：zzx
* 创建日期：2023.7.25
* 最后修改：zzx
* 最后修改日期：
* 备注：
******************************************************************/




class _declspec(dllexport) SIFT :
    public ImageProcess
{
public:
	//构造函数
	explicit SIFT();

	//SIFT
	cv::Mat processImage(const cv::Mat& image) override;

	//返回处理名称
	std::string ReturnName() override;

private:



};




/*****************************************************************
* 类名称：SURF（加速稳健特征）
* 功能描述：SURF是一种类似于SIFT的特征提取器，它使用快速算法来加速特征提取过程。SURF对尺度、旋转和亮度变化具有较好的不变性。
* 作者：zzx
* 创建日期：2023.7.25
* 最后修改：zzx
* 最后修改日期：
* 备注：
******************************************************************/




class _declspec(dllexport) SURF :
	public ImageProcess
{
public:
	//构造函数
	explicit SURF();

	//SIFT
	cv::Mat processImage(const cv::Mat& image) override;

	//返回处理名称
	std::string ReturnName() override;

private:



};




/*****************************************************************
* 类名称：BRISK（Binary Robust Invariant Scalable Keypoints）
* 功能描述：BRISK是一种基于二进制描述符的特征提取器，它结合了尺度不变特征和旋转不变特征。BRISK在保持较高性能的同时，具有较快的速度。
* 作者：zzx
* 创建日期：2023.7.25
* 最后修改：zzx
* 最后修改日期：
* 备注：
******************************************************************/




class _declspec(dllexport) BRISK :
	public ImageProcess
{
public:
	//构造函数
	explicit BRISK();

	//SIFT
	cv::Mat processImage(const cv::Mat& image) override;

	//返回处理名称
	std::string ReturnName() override;

private:



};





/*****************************************************************
* 类名称：AKAZE（Accelerated-KAZE）
* 功能描述：AKAZE是一种快速的特征提取器，它基于KAZE算法，并结合了加速算法来提高速度。AKAZE对于尺度、旋转和仿射变换具有较好的不变性。
* 作者：zzx
* 创建日期：2023.7.25
* 最后修改：zzx
* 最后修改日期：
* 备注：
******************************************************************/





class _declspec(dllexport) AKAZE :
	public ImageProcess
{
public:
	//构造函数
	explicit AKAZE();

	//SIFT
	cv::Mat processImage(const cv::Mat& image) override;

	//返回处理名称
	std::string ReturnName() override;


private:



};

