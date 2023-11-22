#pragma once

#include <QObject>
#include "mainwindow.h"
#include "tabwidget.h"
#include "networkcamera.h"
#include <QInputDialog>
#include <QColorDialog>
#include <QApplication>
#include <QDir>
#include "localcameraui.h"
#include "CameraImageManage.h"
#include "ImageControl.h"
#include "chartwidget.h"
#include "edgedetection.h"
#include "mlManage.h"




class MainController  : public QObject
{
	Q_OBJECT

public:
	MainController(QObject *parent = nullptr);
	~MainController();


private:
	//主窗口类
	MainWindow* MainWin;

	//初始化图像信号和槽
	void InitSignalsAndSlots();

	//增加TAB页面函数
	Tabwidget* AddTab(QString iconpath, QString name, Tabwidget::VisualItemType Type);

	//初始化日志
	void InitLogging();

	//改变相机界面状态
	void ChangeCameraState(int idx);

	//改变图像界面状态
	void ChangeImageState(int idx);

	//改变数据界面状态
	void ChangeDataState(int idx);

	//悬浮窗口类
	QVector<ads::CDockWidget*> CDockWidgetList;

	//链表，用于保存视频显示界面
	QList<std::shared_ptr<Tabwidget>> TabWidgetList;

	// UI界面哈希表,检索每个TAB界面的项
	QHash<std::shared_ptr<Tabwidget>, std::shared_ptr <CameraImageManage>> TabCameraMap;

	// UI界面哈希表,检索每个TAB界面的项
	QHash<std::shared_ptr<Tabwidget>, std::shared_ptr <ImageControl>> TabImageMap;

	// UI界面哈希表,检索每个TAB界面的项
	QHash<std::shared_ptr<Tabwidget>, std::shared_ptr <ImageControl>> TabMlMap;

	//视频保存路径
	std::string VideoSavePath;

	//图像保存路径
	std::string ImageSavePath;

	//数据通讯管理
	std::shared_ptr<DataCommumication> DatCC;

	//日志消息类
	std::shared_ptr<LogHandler> MessageLogging;

	//图表列表
	QVector<std::shared_ptr<QWidget>> QWidgetList;



private slots:
	//悬浮界面关闭
	void dockWidgetRemoved(ads::CDockWidget* DockWidget);

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
	void on_videotab_tabCloseRequested(int index);

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

	//帮助
	void actHelp_clicked();

	//关于
	void actAboutUs_clicked();

	//应用字体设置
	void AplyFontFormat(std::string fontpath, uint offsetx, uint offsety, uint cR, uint cG, uint cB, uint fontheight);

	//页面改变
	void TabCurrentChanged(int index);
};
