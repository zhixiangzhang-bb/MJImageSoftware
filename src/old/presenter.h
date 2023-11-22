#pragma once

#include <QObject>
#include "ImageLibConnect.h"
#include <QApplication>
#include "tabwidget.h"


class Presenter  : public QObject
{
	Q_OBJECT

public:
	Presenter(QObject *parent);

	~Presenter();


	//新建相机项目按钮点击响应函数
	void NewVisionProject();

	//新建机器学习项目
	void actNewModel_clicked();

	//打开图片响应函数
	void actOpenImage_clicked();

	//添加网络相机响应函数
	void actNewNetworkCamera_clicked();

	//添加本地按钮响应函数
	void actNewLocalCamera_clicked();

	//根据相机选择的类型和ID执行
	void SelcetNetcamId(uint idex, CameraType Type);

	//TAB页面关闭按钮响应
	void TabClose(int index);

	//连接相机按钮
	void actConnect_clicked();

	//关闭相机连接
	void actDisConnect_clicked();

	//开始采集
	void actPlay_clicked();

	//停止采集
	void actPause_clicked();

	//开始录像
	void actRecord_clicked();

	//快照
	void actSnap_clicked();

	//字幕显示控制
	void actTitleStart_clicked();

	//字幕显示控制
	void actTitleStop_clicked();

	//相机设置按钮
	void actSetwebcam_clicked();

	//图像保存路径
	void actImagePath_clicked();

	//撤销图像操作
	void actImageRevocation_clicked();

	//恢复图像操作
	void actImageRework_clicked();

	//保存处理后的图像
	void actImageSaveclicked();

	//图像灰度化按钮
	void actGrayImage_clicked();

	//图像二值化按钮
	void actBinaryImage_clicked();

	//均值滤波
	void actImageMeanFilter_clicked();

	//高斯滤波
	void actImageGaussianFilter_clicked();

	//中值滤波
	void actImageMedianFilter_clicked();

	//双边滤波
	void actImageBilateralFilter_clicked();

	//Canny算子
	void actCanny_clicked();

	//Sobel算子
	void actSobel_clicked();

	//Scharr算子
	void actScharr_clicked();

	//Laplacian算子
	void actLaplacian_clicked();

	//Roberts算子
	void actRoberts_clicked();

	//SIFT
	void actSIFT_clicked();

	//SURF
	void actSURF_clicked();

	//BRISK
	void actBRISK_clicked();

	//AKAZE
	void actAKAZE_clicked();

	//亮度调节
	void actBrightness_clicked();

	//对比度调节
	void actContrast_clicked();

	//饱和度调节
	void actNTSC_clicked();

	//色温调节
	void actCCT_clicked();

	//色彩平衡调节
	void actHLS_clicked();

	//色阶调节
	void actLevels_clicked();

	//膨胀
	void actDilation_clicked();

	//腐蚀
	void actErosion_clicked();

	//频谱转换
	void actImageFFT_clicked();

	//灰度直方图
	void actImageHistogram_clicked();

	//测试连接
	void actTryRemotConnect_clicked();

	//模型训练
	void actModelTraining_clicked();

	//模型测试
	void actModelTesting_clicked();

	//模型保存
	void actModelSave_clicked();

	//导入OK文件夹
	void actLoadOk_clicked();

	//导入NO文件夹
	void actLoadNo_clicked();

	//随机森林框架
	void actRandomForest_clicked();

	//SVM框架
	void actSVM_clicked();

	//KNN框架
	void actKNN_clicked();

	//帮助
	void actHelp_clicked();

	//关于
	void actAboutUs_clicked();
};
