#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCheckBox>
#include "SARibbonMainWindow.h"
#include "SARibbonCategory.h"
#include "SARibbonBar.h"
#include "SARibbonComboBox.h"
#include "SARibbonCheckBox.h"
#include "SARibbonButtonGroupWidget.h"
#include "SARibbonGalleryGroup.h"
#include "SARibbonGallery.h"
#include <QSplitter>
#include <DockManager.h>
#include <QColorDialog>


#include "DockAreaWidget.h"
#include "DockAreaTitleBar.h"
#include "DockAreaTabBar.h"
#include "FloatingDockContainer.h"
#include "DockComponentsFactory.h"


#include <QColorDialog>
#include <QDir>
#include "mjis_core_api.h"
#include "mjis_hmi_api.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public SARibbonMainWindow
{
	Q_OBJECT

public:
	//构造函数
	MainWindow(QWidget* parent = nullptr);

	//析构函数
	~MainWindow();
	
private:
	//布局管理器
	ads::CDockManager* m_DockManager;

	//主页面
	ads::CDockWidget* main;

	//字幕悬浮窗
	ads::CDockWidget* titletoolbar;

	//中心窗口区域,唯一
	ads::CDockAreaWidget* CentralDockArea;

	//左侧停靠区域
	ads::CDockAreaWidget* LeftArea;

	//性能界面,唯一
	ads::CDockWidget* systemwidget;

	//系统消息悬浮窗，唯一
	ads::CDockWidget* systemmessagewid;

	//下方停靠区域
	ads::CDockAreaWidget* DownArea;

	//通讯设置悬浮窗，唯一
	ads::CDockWidget* netsetwid;

	//字幕字符串指针
	std::string* subtitle;

	//代理执行线程
	std::shared_ptr<QThread> AgentThread;

	//主持人实例化
	std::shared_ptr<mjis::Presenter> presenter;

	//图像处理代理
	std::shared_ptr<mjis::ImageAgent> imageagent;

	//下侧插入布局
	void BottomNesting(QWidget* widget, QString name);

	//左侧插入布局
	void LeftNesting(QWidget* widget, QString name);

	//右侧插入布局
	void RightNesting(QWidget* widget, QString name);

	//禁用图像处理业务
	void DisableImage();

	//禁用视觉项目所有业务
	void DisableIVision();

	//菜单栏主按键
	SARibbonBar* ribbon;

	//主页标签页
	SARibbonCategory* categoryMain;

	//成像系统标签页
	SARibbonCategory* categoryVision;

	//图像学
	SARibbonCategory* categoryImage;

	//设备标签页
	SARibbonCategory* categoryDevice;

	//空化标签页
	SARibbonCategory* categoryCavitation;

	//模型预测标签页
	SARibbonCategory* categoryData;

	//帮助标签页
	SARibbonCategory* categoryHelp;

	//新建相机项目
	QAction* actNewvisionproject;

	//打开图片按钮
	QAction* actOpenImage;

	//新建模型按钮
	QAction* actNewModel;

	//打开模型按钮
	QAction* actOpenModel;

	//系统信息
	QAction* actSystemPerformance;

	//系统日志
	QCheckBox* actSystemLog;

	//通讯设置
	QCheckBox* actNetSet;
		;
	//新建本地相机按钮
	QAction* actNewLocalCamera;

	//新建网络相机
	QAction* actNewNetworkCamera;

	//仿真相机
	QAction* actSimulationCamera;

	//设备参数
	QAction* actSetwebcam;

	//录制
	QAction* actRecord;

	//停止录制
	QAction* actStopRecord;

	//快照
	QAction* actSnap;

	//录制
	QAction* actStopSnap;

	//保存路径
	QAction* actImagePath;

	//建立连接
	QAction* actConnect;

	//关闭连接
	QAction* actDisConnect;

	//开始采集
	QAction* actPlay;

	//停止采集
	QAction* actPause;

	//触发设置
	QAction* actTriggerSetting;

	//显示字幕
	QAction* actTitleStart;

	//停止字幕
	QAction* actTitleStop;

	//字幕设置
	QCheckBox* actTitleSet;

	//加载模型
	QAction* actLoadCavModel;

	//图像处理回退
	QAction* actImageRevocation;

	//图像处理重做
	QAction* actImageRework;

	//保存图片
	QAction* actImageSave;

	//滤波按钮组
	SARibbonGallery* galleryFileter;

	//灰度化
	QAction* actGrayImage;

	//二值化
	QAction* actBinaryImage;

	//双边滤波
	QAction* actImageBilateralFilter;

	//均值滤波
	QAction* actImageMeanFilter;

	//高斯模糊
	QAction* actImageGaussianFilter;

	//中值滤波
	QAction* actImageMedianFilter;

	//边缘检测按钮组
	SARibbonGallery* galleryEdgeDetection;

	//Canny算子
	QAction* actCanny;

	//Sobel算子
	QAction* actSobel;

	//Scharr算子
	QAction* actScharr;

	//Laplacian算子
	QAction* actLaplacian;

	//Roberts算子
	QAction* actRoberts;

	//特征提取按钮组
	SARibbonGallery* galleryFeatureExtraction;

	//SIFT
	QAction* actSIFT;

	//SURF
	QAction* actSURF;

	//BRISK
	QAction* actBRISK;

	//AKAZE
	QAction* actAKAZE;

	//亮度调节
	QAction* actBrightness;

	//对比度调整
	QAction* actContrast;

	//饱和度调整
	QAction* actNTSC;

	//色温调整
	QAction* actCCT;

	//色彩平衡调整
	QAction* actHLS;

	//色阶调整
	QAction* actLevels;

	//膨胀
	QAction* actDilation;

	//腐蚀
	QAction* actErosion;

	//图像频谱转换
	QAction* actImageFFT;

	//图像直方图
	QAction* actImageHistogram;

	//训练模型
	QAction* actModelTraining;

	//测试模型
	QAction* actModelTesting;

	//模型保存
	QAction* actModelSave;

	//导入Ok文件夹
	QAction* actLoadOk;

	//导入NO文件夹
	QAction* actLoadNo;

	//随机森林框架
	QAction* actRandomForest;

	//SVM框架
	QAction* actSVM;

	//KNN框架
	QAction* actKNN;

	//深度学习框架
	QAction* actDeepLearning;

	//帮助
	QAction* actHelp;

	//关于
	QAction* actAboutUs;

	//创建菜单栏按钮
	QAction* createAction(const QString& text, const QString& iconurl);

	//向某个标签页插入按钮
	void Setentry(QAction* button, QString name, QString path, QString objectname, SARibbonPannel* tabpage);

	//初始化样式
	void initStyle();

	//初始化主页
	void initMain();

	//初始化视觉
	void initVision();

	//初始化图像学
	void initImage();

	//初始化模型预测
	void initForecast();

	//初始化模型预测
	void initHelp();

	//初始化布局
	void initlayout();

	//初始化图像信号和槽
	void InitSignalsAndSlots();

	//增加TAB页面函数
	std::shared_ptr<mjis::hmi::Tabwidget> AddTab(QString iconpath, QString name, mjis::hmi::Tabwidget::VisualItemType Type);

	//初始化日志
	void InitLogging();

	//改变相机界面状态
	void ChangeCameraState();

	//改变图像界面状态
	void ChangeImageState(int idx);

	//悬浮窗口类
	QVector<ads::CDockWidget*> CDockWidgetList;

	//链表，用于保存视频显示界面
	QVector<std::shared_ptr<mjis::hmi::Tabwidget>> TabWidgetList;

	//视频保存路径
	std::string VideoSavePath;

	//图像保存路径
	std::string ImageSavePath;

	//数据通讯管理
	//std::shared_ptr<DataCommumication> DatCC;

	//日志消息类
	std::shared_ptr<mjis::hmi::LogHandler> MessageLogging;

	//图表列表
	QVector<std::shared_ptr<QWidget>> QWidgetList;

	Ui::MainWindow* ui;


	//自定义槽函数
private slots:
	//字幕设置工具栏按钮
	void actTitleSet_stateChanged(bool state);

	//网络设置显示响应函数
	void actNetSet_stateChanged(bool state);

	//系统日志响应函数
	void actSystemLog_stateChanged(bool state);

	//颜色设置按钮
    void on_fontcolor_clicked();

	//应用字体设置
    void on_ApplyFontset_clicked();

	//标题文本改变
    void on_ExperimentString_textChanged(const QString &arg1);

	//自定义文本改变
    void on_plainTextEdit_textChanged();

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
	void SelcetNetcamId(uint idex, mjis::camera::ICamera::CameraType Type);

	//TAB页面关闭按钮响应
	void TabClose(int index);

	//关闭页面成功
	void CloseSuccess(std::shared_ptr<mjis::hmi::Tabwidget> tab);

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

	//停止录像
	void actStopRecord_clicked();

	//快照
	void actSnap_clicked();

	//停止快照
	void actStopSnap_clicked();

	//字幕显示控制
	void actTitleStart_clicked();

	//字幕显示控制
	void actTitleStop_clicked();

	//相机设置按钮
	void actSetwebcam_clicked();


	void actLoadCavModel_clicked();

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

	//灰度直方图绘制完成
	void DrawChartSuccess(mjis::hmi::ChartWidget* chart, const QString& name);

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

	//页面改变
	void TabCurrentChanged(int index);


signals:
	void Sg_CloseTab(int page);

	//连接相机
	void Sg_Connect(int page);

	//断开连接相机
	void Sg_DisConnect(int page);

	//开始采集
	void Sg_Start(int page);

	//停止采集
	void Sg_Stop(int page);

	//开始保存视频
	void Sg_StartSaveVideo(int page);

	//停止保存视频
	void Sg_StopSaveVideo(int page);

	//开始保存图像
	void Sg_StartSnapImage(int page);

	//停止保存图像
	void Sg_StopSnapImage(int page);

	//显示字幕
	void Sg_StartSub(int page, std::string* text, std::string* data);

	//清除字幕
	void Sg_StopSub(int page);

	//应用字体设置
	void Sg_SetFont(int page, uint offsetx, uint offsety, uint cR, uint cG, uint cB, uint fontheight);

	//打开图片信号
	void Sg_OpenImage(QString path, int page);

	//图像处理
	void Sg_ProcessImage(mjlib::ImageProcess* process, int page);

	//图像处理回退
	void Sg_PopProcess(int page);

	//图像处理取消回退
	void Sg_BackProcess(int page);

	//绘制图表
	void Sg_DrawChart(mjis::hmi::ChartWidget* chart,int page);
	
};
#endif // MAINWINDOW_H
