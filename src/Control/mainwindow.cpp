
#include "loghead.h"

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "SAFramelessHelper.h"
#include "videopathset.h"
#include <filesystem>
#include <QFormLayout>
#include <QSpinBox>
#include <QDialogButtonBox>
#include "mjis_ImageLibConnect.h"
#include <QLabel>
#include "configinterface.h"

using namespace ads;


MainWindow::MainWindow(QWidget *parent)
    : subtitle(new std::string),SARibbonMainWindow(parent)
    , AgentThread(new QThread())
    , presenter(new Presenter())
    , imageagent(nullptr)
    , LeftArea(nullptr), DownArea(nullptr)
    ,ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //将代理移动到工作线程
    presenter->moveToThread(AgentThread.get());
    AgentThread->start();

    this->InitLogging();
    this->showMaximized();
    this->initlayout();//初始化布局
    this->initStyle();//初始化工具栏
    this->initVision();//初始化样式函数
    this->initMain();//初始化样式函数
    this->initImage();//初始化图像学样式
    this->initForecast();
    this->initHelp();//在初始化帮助列表
    this->InitSignalsAndSlots();

    ui->statusBar->showMessage("软件版本:初步设计版本V1.0 ");

}



MainWindow::~MainWindow()
{
    if (AgentThread->isRunning())
    {
        AgentThread->quit();
    }
    delete ui;
}


//初始化样式
void MainWindow::initStyle()
{
    SAFramelessHelper* helper = framelessHelper();
    helper->setRubberBandOnResize(false);
    this->ribbon = ribbonBar();
    this->ribbon->setContentsMargins(5, 0, 5, 0);
    this->ribbon->setFixedWidth(20);
    this->ribbon->setMinimumWidth(600);
    //设置applicationButton
    this->ribbon->applicationButton()->setText(("菜单"));
    //添加标签页 - 通过addCategoryPage工厂函数添加
    this->categoryMain = this->ribbon->addCategoryPage(tr("主页"));
    this->categoryImage= this->ribbon->addCategoryPage(tr("图像学"));
    this->categoryCavitation = this->ribbon->addCategoryPage(tr("模型预测"));
    this->categoryHelp = this->ribbon->addCategoryPage(tr("帮助"));
    setWindowTitle(("成像及处理软件"));
    setWindowIcon(QIcon("./icon/照相机.svg"));

    ui->ExperimentDate->setDateTime(QDateTime::currentDateTime());

}



//初始化日志记录器
void MainWindow::InitLogging()
{
    // 初始化日志记录器
    google::InitGoogleLogging("CavitationAPP");
    FLAGS_alsologtostderr = true;//是否将日志输出到文件和stderr
    FLAGS_colorlogtostderr = true;//是否启用不同颜色显示
    google::SetLogDestination(google::GLOG_INFO, "E:/ZImageSoft/CavitationAPP/Log/Log_");//INFO级别的日志都存放到logs目录下且前缀为INFO_
    google::SetLogDestination(google::GLOG_WARNING, "E:/ZImageSoft/CavitationAPP/Log/Log_");//WARNING级别的日志都存放到logs目录下且前缀为WARNING_
    google::SetLogDestination(google::GLOG_ERROR, "E:/ZImageSoft/CavitationAPP/Log/Log_");	//ERROR级别的日志都存放到logs目录下且前缀为ERROR_
    google::SetLogDestination(google::GLOG_FATAL, "E:/ZImageSoft/CavitationAPP/Log/Log_");
}




void MainWindow::initMain()//初始化主页
{

    const QString currentPath = QCoreApplication::applicationDirPath();
    SARibbonPannel* Main_pannel1;//主页标签页分项名
    SARibbonPannel* Main_pannel2;//主页标签页分项名
    SARibbonPannel* Main_pannel3;//主页标签页分项名
    SARibbonPannel* Main_pannel4;//主页标签页分项名
    SARibbonPannel* Main_pannel5;//主页标签页分项名
    SARibbonPannel* Main_pannel6;//主页标签页分项名
    SARibbonPannel* Main_pannel7;//主页标签页分项名
    SARibbonPannel* Main_pannel8;//主页标签页分项名
    Main_pannel1 =this->categoryMain->addPannel(("图像学"));
    Main_pannel2 =this->categoryMain->addPannel(("添加设置"));
    Main_pannel3 =this->categoryMain->addPannel(("控制"));
    Main_pannel4 = this->categoryMain->addPannel(("录制"));
    Main_pannel5 = this->categoryMain->addPannel(("设备"));
    Main_pannel6 = this->categoryMain->addPannel(("字幕"));
    Main_pannel7 = this->categoryMain->addPannel(("空化预测"));
    Main_pannel8 = this->categoryMain->addPannel(("视图"));
    this->actNewvisionproject = new QAction(this);//新建文件按钮
    this->Setentry(actNewvisionproject,"新建相机", currentPath+"/icon/新建窗口.svg","actNewvisionproject",Main_pannel1);
    this->actOpenImage = new QAction(this);//打开图片按钮
    this->Setentry(actOpenImage,"打开图片","./icon/打开图片.svg","actOpenImage",Main_pannel1);


    this->actNewLocalCamera = new QAction(this);
    this->Setentry(actNewLocalCamera, "本地设备", currentPath+"/icon/添加设备.svg", "actNewvision", Main_pannel2);
    this->actNewNetworkCamera = new QAction(this);
    this->Setentry(actNewNetworkCamera, "网络设备", currentPath+"/icon/添加设备.svg", "actNewNetworkCamera", Main_pannel2);
    this->actSimulationCamera = new QAction(this);
    this->Setentry(actSimulationCamera, "仿真相机", "./icon/仿真相机.svg", "actSimulationCamera", Main_pannel2);


    this->actConnect = new QAction(this);
    this->Setentry(actConnect, "连接相机", "./icon/连接.svg", "actConnect", Main_pannel3);
    this->actDisConnect = new QAction(this);
    this->Setentry(actDisConnect, "断开连接", "./icon/取消连接.svg", "actDisConnect", Main_pannel3);
    this->actPlay = new QAction(this);
    this->Setentry(actPlay, "开始采集", "./icon/播放.svg", "actPlay", Main_pannel3);
    this->actPause = new QAction(this);
    this->Setentry(actPause, "停止采集", "./icon/暂停.svg", "actPause", Main_pannel3);


    this->actRecord = new QAction(this);
    this->Setentry(actRecord, "录 制", "./icon/开始录制视频.svg", "actRecord", Main_pannel4);
    this->actStopRecord = new QAction(this);
    this->Setentry(actStopRecord, "停止录制", "./icon/停止录制视频.svg", "actStopRecord", Main_pannel4);
    this->actSnap = new QAction(this);
    this->Setentry(actSnap, "快 照", "./icon/连续采集.svg", "actSnap", Main_pannel4);
    this->actStopSnap = new QAction(this);
    this->Setentry(actStopSnap, "停止快照", "./icon/停止连续采集.svg", "actStopSnap", Main_pannel4);
    this->actImagePath = new QAction(this);
    this->Setentry(actImagePath, "路径设置", "./icon/路径设置.svg", "actImagePath", Main_pannel4);


    this->actSetwebcam = new QAction(this);
    this->Setentry(actSetwebcam, "设备参数", "./icon/设备管理.svg", "actSetwebcam", Main_pannel5);
    this->actTriggerSetting = new QAction(this);
    this->Setentry(actTriggerSetting, "触发设置", "./icon/触发设置.svg", "actTriggerSetting", Main_pannel5);


    this->actTitleStart = new QAction(this);
    this->Setentry(actTitleStart, "打开字幕", "./icon/智能字幕.svg", "actTitleControl", Main_pannel6);
    this->actTitleStop = new QAction(this);
    this->Setentry(actTitleStop, "关闭字幕", "./icon/视频去字幕.svg", "actTitleControl", Main_pannel6);


    this->actLoadCavModel = new QAction(this);//新建设备参数
    this->Setentry(actLoadCavModel, "载入模型", "./icon/导入配置.svg", "actLoadCavModel", Main_pannel7);

    //模型板块
    //this->actNewModel = new QAction(this);//打开图片按钮
    //this->Setentry(actNewModel, "新建模型", "./icon/新建模型.svg", "actNewModel", Main_pannel8);
    //this->actOpenModel = new QAction(this);//打开图片按钮
    //this->Setentry(actOpenModel, "打开模型", "./icon/打开模型.svg", "actOpenModel", Main_pannel8);

    //视图板块
    this->actSystemPerformance = new QAction(this);
    //this->Setentry(actSystemPerformance, "系统性能", "./icon/性能统计.svg", "actSystemPerformance", Main_pannel8);


    this->actSystemLog = new QCheckBox(this);
    actSystemLog->setText("系统日志");
    //actSystemLog->setIcon(QIcon("./icon/日志.svg"));
    actSystemLog->setObjectName("actSystemLog");
    Main_pannel8->addSmallWidget(actSystemLog);
    //this->Setentry(actSystemLog, "系统日志", "./icon/日志.svg", "actSystemLog", Main_pannel8);


    this->actNetSet = new QCheckBox(this);
    actNetSet->setText("通讯设置");
    //actNetSet->setIcon(QIcon("./icon/通讯设置.svg"));
    actNetSet->setObjectName("actNetSet");
    Main_pannel8->addSmallWidget(actNetSet);
    //this->Setentry(actNetSet, "通讯设置", "./icon/通讯设置.svg", "actSystemLog", Main_pannel8);


    this->actTitleSet = new QCheckBox(this);
    actTitleSet->setText("字幕设置");
    //actNetSet->setIcon(QIcon("./icon/通讯设置.svg"));
    actTitleSet->setObjectName("actTitleSet");
    Main_pannel8->addSmallWidget(actTitleSet);
    //this->Setentry(actNetSet, "通讯设置", "./icon/通讯设置.svg", "actSystemLog", Main_pannel8);



    //连接性能按钮信号槽
    connect(this->actSystemLog, &QCheckBox::stateChanged, this, &MainWindow::actSystemLog_stateChanged, Qt::QueuedConnection);
    //连接
    connect(this->actNetSet, &QCheckBox::stateChanged, this, &MainWindow::actNetSet_stateChanged, Qt::DirectConnection);
    //连接
    connect(this->actTitleSet, &QCheckBox::stateChanged, this, &MainWindow::actTitleSet_stateChanged, Qt::DirectConnection);

    //软件初始化后禁用按钮直到事件达到后解锁
    this->DisableIVision();

    //this->actNetSet->setChecked(true);
    //this->actTitleSet->setChecked(true);
}


void MainWindow::initVision()//初始化视觉菜单
{
    /*
    SARibbonPannel* Vision_pannel1;//视觉标签页分项名
    SARibbonPannel* Vision_pannel2;//视觉标签页分项名
    SARibbonPannel* Vision_pannel3;//视觉标签页分项名
    SARibbonPannel* Vision_pannel4;//视觉标签页分项名
    SARibbonPannel* Vision_pannel5;//视觉标签页分项名
    SARibbonPannel* Vision_pannel6;//视觉标签页分项名

    Vision_pannel1 =this->categoryVision->addPannel(("添加设备"));
    Vision_pannel2 =this->categoryVision->addPannel(("控制"));
    Vision_pannel3 =this->categoryVision->addPannel(("录制"));
    Vision_pannel4 =this->categoryVision->addPannel(("设置"));
    Vision_pannel5 =this->categoryVision->addPannel(("字幕"));
    Vision_pannel6 =this->categoryVision->addPannel(("预测模型"));

    /*
    this->actNewLocalCamera = new QAction(this);
    this->Setentry(actNewLocalCamera,"本地设备","./icon/添加设备.svg","actNewvision",Vision_pannel1);
    this->actNewNetworkCamera = new QAction(this);
    this->Setentry(actNewNetworkCamera,"网络设备","./icon/添加设备.svg","actNewNetworkCamera",Vision_pannel1);
    this->actSimulationCamera = new QAction(this);
    this->Setentry(actSimulationCamera, "仿真相机", "./icon/仿真相机.svg", "actSimulationCamera", Vision_pannel1);

    this->actConnect = new QAction(this);
    this->Setentry(actConnect,"连接相机","./icon/连接.svg","actConnect",Vision_pannel2);
    this->actDisConnect = new QAction(this);
    this->Setentry(actDisConnect,"断开连接","./icon/取消连接.svg","actDisConnect",Vision_pannel2);
    this->actPlay = new QAction(this);
    this->Setentry(actPlay,"开始采集","./icon/播放.svg","actPlay",Vision_pannel2);
    this->actPause = new QAction(this);
    this->Setentry(actPause,"停止采集","./icon/暂停.svg","actPause",Vision_pannel2);

    this->actRecord = new QAction(this);
    this->Setentry(actRecord,"录 制","./icon/开始录制视频.svg","actRecord",Vision_pannel3);
    this->actStopRecord = new QAction(this);
    this->Setentry(actStopRecord, "停止录制", "./icon/停止录制视频.svg", "actStopRecord", Vision_pannel3);
    this->actSnap = new QAction(this);
    this->Setentry(actSnap,"快 照","./icon/连续采集.svg","actSnap",Vision_pannel3);
    this->actStopSnap = new QAction(this);
    this->Setentry(actStopSnap, "停止快照", "./icon/停止连续采集.svg", "actStopSnap", Vision_pannel3);
    this->actImagePath = new QAction(this);
    this->Setentry(actImagePath,"路径设置","./icon/路径设置.svg","actImagePath",Vision_pannel3);
    this->actSetwebcam = new QAction(this);

    this->Setentry(actSetwebcam,"设备参数","./icon/设备管理.svg","actSetwebcam",Vision_pannel4);
    this->actTriggerSetting = new QAction(this);
    this->Setentry(actTriggerSetting,"触发设置","./icon/触发设置.svg","actTriggerSetting",Vision_pannel4);

    this->actTitleStart = new QAction(this);
    this->Setentry(actTitleStart,"打开字幕","./icon/智能字幕.svg","actTitleControl",Vision_pannel5);
    this->actTitleStop = new QAction(this);
    this->Setentry(actTitleStop, "关闭字幕", "./icon/视频去字幕.svg", "actTitleControl", Vision_pannel5);
    this->actTitleSet = new QAction(this);
    this->Setentry(actTitleSet,"字幕设置","./icon/字幕设置.svg","actTitleSet",Vision_pannel5);

    this->actLoadCavModel = new QAction(this);//新建设备参数
    this->Setentry(actLoadCavModel,"载入模型","./icon/导入配置.svg","actLoadCavModel",Vision_pannel6);

    //软件初始化后禁用按钮直到事件达到后解锁
    //this->DisableIVision();

    //this->actLoadCavModel->setEnabled(true);

    //connect(this->actTitleSet, &QAction::triggered, this, &MainWindow::actTitleSet_clicked, Qt::QueuedConnection);
    */
}




//禁用所有相机业务
void MainWindow::DisableIVision()
{
    actNewLocalCamera->setEnabled(false);
    actNewNetworkCamera->setEnabled(false);
    actSimulationCamera->setEnabled(false);
    actConnect->setEnabled(false);
    actDisConnect->setEnabled(false);
    actPlay->setEnabled(false);
    actPause->setEnabled(false);
    actRecord->setEnabled(false);
    actStopRecord->setEnabled(false);
    actSnap->setEnabled(false);
    actStopSnap->setEnabled(false);
    actSetwebcam->setEnabled(false);
    actTriggerSetting->setEnabled(false);
    actTitleStart->setEnabled(false);
    actTitleStop->setEnabled(false);
    //actLoadCavModel->setEnabled(false);
}






//初始化图像学
void MainWindow::initImage()
{
    SARibbonPannel* Image_pannel1;//视觉标签页分项名
    SARibbonPannel* Image_pannel2;//视觉标签页分项名
    SARibbonPannel* Image_pannel3;//视觉标签页分项名
    SARibbonPannel* Image_pannel4;//视觉标签页分项名
    SARibbonPannel* Image_pannel5;//视觉标签页分项名
    SARibbonPannel* Image_pannel6;//视觉标签页分项名
    SARibbonPannel* Image_pannel7;//视觉标签页分项名
    SARibbonPannel* Image_pannel8;//视觉标签页分项名
    SARibbonPannel* Image_pannel9;//视觉标签页分项名

    Image_pannel1 = this->categoryImage->addPannel(("编辑"));
    Image_pannel2 = this->categoryImage->addPannel(("滤镜"));
    Image_pannel3 = this->categoryImage->addPannel(("边缘检测"));
    Image_pannel4 = this->categoryImage->addPannel(("特征值"));
    Image_pannel5 = this->categoryImage->addPannel(("色彩校正"));
    Image_pannel6 = this->categoryImage->addPannel(("形态学"));
    Image_pannel7 = this->categoryImage->addPannel(("图像分析"));

    //工具栏
    this->actImageRevocation = new QAction(this);//新建后退按钮
    this->Setentry(actImageRevocation, "撤 销", "./icon/撤销.svg", "actImageRevocation", Image_pannel1);
    this->actImageRework = new QAction(this);//新建后退按钮
    this->Setentry(actImageRework, "重 做", "./icon/重做.svg", "actImageRework", Image_pannel1);
    this->actImageSave = new QAction(this);//新建后退按钮
    this->Setentry(actImageSave, "保 存", "./icon/保存.svg", "actImageSave", Image_pannel1);



    //滤波按钮组
    this->actGrayImage = createAction("灰度化", "./icon/灰度化.svg");//新建灰度化按钮
    this->actBinaryImage = createAction("二值化", "./icon/图像的二值化.svg");//新建二值化按钮
    this->actImageBilateralFilter = createAction("双边滤波", "./icon/图像滤波.svg");//新建滤波按钮
    this->actImageMeanFilter = createAction("均值模糊", "./icon/均值滤波.svg");//新建滤波按钮
    this->actImageGaussianFilter = createAction("高斯模糊", "./icon/高斯滤波.svg");//新建滤波按钮
    this->actImageMedianFilter = createAction("中值模糊", "./icon/中值滤波.svg");//新建滤波按钮
    galleryFileter = Image_pannel2->addGallery();
    QList<QAction*> galleryFileterActions;
    galleryFileterActions.append(actGrayImage);
    galleryFileterActions.append(actBinaryImage);
    galleryFileterActions.append(actImageMeanFilter);
    galleryFileterActions.append(actImageGaussianFilter);
    galleryFileterActions.append(actImageMedianFilter);
    galleryFileterActions.append(actImageBilateralFilter);
    SARibbonGalleryGroup* group1 = galleryFileter->addCategoryActions("卷积方法", galleryFileterActions);
    group1->setGalleryGroupStyle(SARibbonGalleryGroup::IconWithWordWrapText);
    group1->setGridMinimumWidth(80);
    group1->setGridMaximumWidth(335);
    galleryFileter->setCurrentViewGroup(group1);

    //图像识别
    this->actCanny = createAction("Canny算子", "./icon/边缘检测.svg");
    this->actSobel = createAction("Sobel算子", "./icon/边缘检测.svg");
    this->actScharr = createAction("Scharr算子", "./icon/边缘检测.svg");
    this->actLaplacian = createAction("Laplacian算子", "./icon/边缘检测.svg");
    this->actRoberts = createAction("Roberts算子", "./icon/边缘检测.svg");

    galleryEdgeDetection = Image_pannel3->addGallery();
    QList<QAction*> galleryEdgeDetectionActions;
    galleryEdgeDetectionActions.append(actCanny);
    galleryEdgeDetectionActions.append(actSobel);
    galleryEdgeDetectionActions.append(actScharr);
    galleryEdgeDetectionActions.append(actLaplacian);
    galleryEdgeDetectionActions.append(actRoberts);
    SARibbonGalleryGroup* group2 = galleryEdgeDetection->addCategoryActions("识别", galleryEdgeDetectionActions);
    group2->setGalleryGroupStyle(SARibbonGalleryGroup::IconWithWordWrapText);
    group2->setGridMinimumWidth(80);
    group2->setGridMaximumWidth(335);
    galleryEdgeDetection->setCurrentViewGroup(group2);


    //特诊提取
    this->actSIFT = createAction("SIFT", "./icon/特征提取.svg");
    this->actSURF = createAction("SURF", "./icon/特征提取.svg");
    this->actBRISK = createAction("BRISK", "./icon/特征提取.svg");
    this->actAKAZE = createAction("AKAZE", "./icon/特征提取.svg");


    galleryFeatureExtraction = Image_pannel4->addGallery();
    QList<QAction*> galleryFeatureExtractionActions;
    galleryFeatureExtractionActions.append(actSIFT);
    galleryFeatureExtractionActions.append(actSURF);
    galleryFeatureExtractionActions.append(actBRISK);
    galleryFeatureExtractionActions.append(actAKAZE);
    SARibbonGalleryGroup* group3 = galleryFeatureExtraction->addCategoryActions("特征提取", galleryFeatureExtractionActions);
    group3->setGalleryGroupStyle(SARibbonGalleryGroup::IconWithWordWrapText);
    group3->setGridMinimumWidth(80);
    group3->setGridMaximumWidth(335);
    galleryFeatureExtraction->setCurrentViewGroup(group3);


    //色彩校正
    this->actBrightness = new QAction(this);
    this->Setentry(actBrightness, "亮 度", "./icon/亮度.svg", "actBrightness", Image_pannel5);
    this->actContrast = new QAction(this);
    this->Setentry(actContrast, "对比度", "./icon/对比度.svg", "actContrast", Image_pannel5);
    this->actNTSC = new QAction(this);
    this->Setentry(actNTSC, "饱和度", "./icon/饱和度.svg", "actNTSC", Image_pannel5);
    this->actCCT = new QAction(this);
    this->Setentry(actCCT, "色 温", "./icon/色温.svg", "actCCT", Image_pannel5);
    this->actHLS = new QAction(this);
    this->Setentry(actHLS, "色彩平衡", "./icon/色彩平衡.svg", "actHLS", Image_pannel5);
    this->actLevels = new QAction(this);
    this->Setentry(actLevels, "色 阶", "./icon/色阶.svg", "actLevels", Image_pannel5);

    //形态学
    this->actDilation = new QAction(this);
    this->Setentry(actDilation, "膨 胀", "./icon/膨胀.svg", "actDilation", Image_pannel6);
    this->actErosion = new QAction(this);
    this->Setentry(actErosion, "腐 蚀", "./icon/腐蚀.svg", "actErosion", Image_pannel6);



    //图像分析
    this->actImageFFT = new QAction(this);
    this->Setentry(actImageFFT, "频谱转换", "./icon/频谱分析.svg", "actImageFFT", Image_pannel7);
    this->actImageHistogram = new QAction(this);
    this->Setentry(actImageHistogram, "直方图", "./icon/直方图.svg", "actImageHistogram", Image_pannel7);



    //软件初始化后禁用按钮直到事件达到后解锁
    this->DisableImage();
}



//禁用所有视觉项目
void MainWindow::DisableImage()
{
    actImageRevocation->setEnabled(false);
    actImageRework->setEnabled(false);
    actImageSave->setEnabled(false);
    actGrayImage->setEnabled(false);
    actBinaryImage->setEnabled(false);
    actImageBilateralFilter->setEnabled(false);
    actImageFFT->setEnabled(false);
    actImageHistogram->setEnabled(false);

    actBrightness->setEnabled(false);
    actContrast->setEnabled(false);
    actNTSC->setEnabled(false);
    actCCT->setEnabled(false);
    actHLS->setEnabled(false);
    actLevels->setEnabled(false);
    actDilation->setEnabled(false);
    actErosion->setEnabled(false);

    galleryFileter->setEnabled(false);
    galleryEdgeDetection->setEnabled(false);
    galleryFeatureExtraction->setEnabled(false);
}





//初始化模型预测
void MainWindow::initForecast()
{
    SARibbonPannel* Forecast_pannel1;//视觉标签页分项名
    SARibbonPannel* Forecast_pannel2;//视觉标签页分项名
    SARibbonPannel* Forecast_pannel3;//视觉标签页分项名
    SARibbonPannel* Forecast_pannel4;//视觉标签页分项名

    Forecast_pannel1 = this->categoryCavitation->addPannel(("工具"));
    Forecast_pannel2 = this->categoryCavitation->addPannel(("导入"));
    Forecast_pannel3 = this->categoryCavitation->addPannel(("框架"));

    this->actModelTraining = new QAction(this);//新建数据测试连接
    this->Setentry(actModelTraining, "模型训练", "./icon/模型训练.svg", "actModelTraining", Forecast_pannel1);
    this->actModelTesting = new QAction(this);//新建数据测试连接
    this->Setentry(actModelTesting, "模型测试", "./icon/模型测试.svg", "actModelTesting", Forecast_pannel1);
    this->actModelSave = new QAction(this);//新建后退按钮
    this->Setentry(actModelSave, "保 存", "./icon/保存.svg", "actModelSave", Forecast_pannel1);

    this->actLoadOk = new QAction(this);//新建后退按钮
    this->Setentry(actLoadOk, "OK文件夹", "./icon/ok.svg", "actLoadOk", Forecast_pannel2);
    this->actLoadNo = new QAction(this);//新建后退按钮
    this->Setentry(actLoadNo, "NO文件夹", "./icon/NO.svg", "actLoadNo", Forecast_pannel2);

    this->actRandomForest = new QAction(this);//新建后退按钮
    this->Setentry(actRandomForest, "随机森林", "./icon/随机森林.svg", "actRandomForest", Forecast_pannel3);
    this->actSVM = new QAction(this);//新建后退按钮
    this->Setentry(actSVM, "SVM", "./icon/svm.svg", "actSVM", Forecast_pannel3);
    this->actKNN = new QAction(this);//新建后退按钮
    this->Setentry(actKNN, "KNN", "./icon/KNN.svg", "actKNN", Forecast_pannel3);
    this->actDeepLearning = new QAction(this);//新建后退按钮
    this->Setentry(actDeepLearning, "深度学习", "./icon/深度学习.svg", "actDeepLearning", Forecast_pannel3);
}





//初始化帮助界面
void MainWindow::initHelp()
{
    SARibbonPannel* Help_pannel1;//视觉标签页分项名
    SARibbonPannel* Help_pannel2;//视觉标签页分项名
    SARibbonPannel* Help_pannel3;//视觉标签页分项名

    Help_pannel1 = this->categoryHelp->addPannel(("帮助"));
    Help_pannel2 = this->categoryHelp->addPannel(("关于"));


    this->actHelp = new QAction(this);//新建数据测试连接
    this->Setentry(actHelp, "帮 助", "./icon/帮助.svg", "actHelp", Help_pannel1);

    this->actAboutUs = new QAction(this);//新建后退按钮
    this->Setentry(actAboutUs, "关于作者", "./icon/关于作者.svg", "actAboutUs", Help_pannel2);

}




//添加标签页按钮，只限按钮
void MainWindow::Setentry(QAction* button,QString name,QString path,QString objectname,SARibbonPannel* tabpage)
{
    button->setText(name);
    button->setIcon(QIcon(path));
    button->setObjectName(objectname);
    tabpage->addLargeAction(button);
}




//初始化布局
void MainWindow::initlayout()
{
    /*
    //设置布局参数
    ads::CDockManager::setConfigFlag(ads::CDockManager::FocusHighlighting, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::AllTabsHaveCloseButton, true);   
    ads::CDockManager::setConfigFlag(CDockManager::DockAreaHasCloseButton, false);
    ads::CDockManager::setConfigFlag(CDockManager::DockAreaHasUndockButton, false);
    ads::CDockManager::setConfigFlag(CDockManager::DragPreviewIsDynamic, true);
    ads::CDockManager::setConfigFlag(CDockManager::DragPreviewShowsContentPixmap, false);
    ads::CDockManager::setConfigFlag(CDockManager::DragPreviewHasWindowFrame, false);

    //创建布局管理器
    //m_DockManager = new ads::CDockManager(this);

    //设置中心窗口
    main = new ads::CDockWidget("主窗口");
    main->setWidget(ui->widget);
    CentralDockArea = m_DockManager->setCentralWidget(main);
    CentralDockArea->setAllowedAreas(DockWidgetArea::OuterDockAreas);
    ui->videotab->setTabsClosable(true);


    //创建通讯管理器
    DatCC = std::make_shared<DataCommumication>(this);
    netsetwid = new ads::CDockWidget("通讯设置");
    netsetwid->setWidget(DatCC->ReturnUI());
    LeftArea = m_DockManager->addDockWidget(ads::LeftDockWidgetArea, netsetwid, CentralDockArea);
    LeftArea=m_DockManager->addDockWidgetTab(ads::LeftDockWidgetArea, netsetwid);
    //auto netarea=m_DockManager->addDockWidget(ads::BottomDockWidgetArea, netsetwid, sysDockArea);


    //添加字幕设置工具栏
    titletoolbar = new ads::CDockWidget("字幕设置");
    titletoolbar->setWidget(ui->titletoolbar);
    auto area = m_DockManager->addDockWidget(ads::InvalidDockWidgetArea, titletoolbar, LeftArea);
    m_DockManager->addDockWidgetTabToArea(titletoolbar, LeftArea);
    //sysDockArea = m_DockManager->addDockWidget(ads::LeftDockWidgetArea, titletoolbar);
    //sysDockArea->close();
    //area->close();
    LeftArea->close();
    netsetwid->close();
    titletoolbar->close();

    //默认添加系统日志界面,所有界面管理器都有一个出口统一释放内存
    SystemMessage* systemmessage = new SystemMessage;
    systemmessagewid = new ads::CDockWidget("系统日志");
    systemmessagewid->setWidget(systemmessage);
    systemmessagewid->setFeature(CDockWidget::DockWidgetClosable,true);
    //把这个窗口默认插入到下边
    DownArea =m_DockManager->addDockWidget(ads::BottomDockWidgetArea, systemmessagewid, CentralDockArea);
    //messagearea->close();



    //默认添加系统性能界面,所有界面管理器都有一个出口统一释放内存
    //SystemResources* systemresources = new SystemResources();
    //systemwidget = new ads::CDockWidget("系统性能");
    //systemwidget->setWidget(systemresources);
    //设置关闭后自动删除窗口
    //systemwidget->setFeature(ads::CDockWidget::DockWidgetDeleteOnClose, true);
    //把这个窗口默认插入到右边
    //m_DockManager->addDockWidget(ads::BottomDockWidgetArea, systemwidget, processDockArea);

    ui->statusBar->showMessage("软件版本:初步设计版本V1.0");
    */
}



//初始化信号和槽
void MainWindow::InitSignalsAndSlots()
{
    /*
    //相机参数
    connect(actNewvisionproject, &QAction::triggered, this, &MainWindow::NewVisionProject,Qt::DirectConnection);
    connect(this, &MainWindow::Sg_CloseTab, presenter.get(), &Presenter::CloseTab, Qt::QueuedConnection);

    //打开图片信号槽
    connect(actOpenImage, &QAction::triggered, this, &MainWindow::actOpenImage_clicked, Qt::QueuedConnection);
    connect(this, &MainWindow::Sg_Connect, presenter.get(), &Presenter::Connect, Qt::QueuedConnection);
    connect(this, &MainWindow::Sg_DisConnect, presenter.get(), &Presenter::DisConnect, Qt::QueuedConnection);
    connect(this, &MainWindow::Sg_Start, presenter.get(), &Presenter::Start, Qt::QueuedConnection);
    connect(this, &MainWindow::Sg_Stop, presenter.get(), &Presenter::Stop, Qt::QueuedConnection);
    connect(this, &MainWindow::Sg_StartSaveVideo, presenter.get(), &Presenter::StartSaveVideo, Qt::QueuedConnection);
    connect(this, &MainWindow::Sg_StopSaveVideo, presenter.get(), &Presenter::StopSaveVideo, Qt::QueuedConnection);
    connect(this, &MainWindow::Sg_StartSnapImage, presenter.get(), &Presenter::StartSnapImage, Qt::QueuedConnection);
    connect(this, &MainWindow::Sg_StopSnapImage, presenter.get(), &Presenter::StopSnapImage, Qt::QueuedConnection);
    connect(this, &MainWindow::Sg_StartSub, presenter.get(), &Presenter::StartSub, Qt::QueuedConnection);
    connect(this, &MainWindow::Sg_StopSub, presenter.get(), &Presenter::StopSub, Qt::QueuedConnection);
    connect(this, &MainWindow::Sg_SetFont, presenter.get(), &Presenter::SetFont, Qt::QueuedConnection);
    connect(presenter.get(), &Presenter::ChangeToolState, this, &MainWindow::ChangeCameraState, Qt::QueuedConnection);
    connect(this, &MainWindow::Sg_OpenImage, presenter.get(), &Presenter::OpenImage, Qt::QueuedConnection);
    connect(this, &MainWindow::Sg_ProcessImage, presenter.get(), &Presenter::ProcessImage, Qt::QueuedConnection);
    connect(this, &MainWindow::Sg_PopProcess, presenter.get(), &Presenter::PopProcess, Qt::QueuedConnection);
    connect(this, &MainWindow::Sg_BackProcess, presenter.get(), &Presenter::BackProcess, Qt::QueuedConnection);
    connect(this, &MainWindow::Sg_DrawChart, presenter.get(), &Presenter::DrawChart, Qt::QueuedConnection);
    connect(presenter.get(), &Presenter::DrawChartSuccess, this, &MainWindow::DrawChartSuccess, Qt::QueuedConnection);


    //connect(actNewModel, &QAction::triggered, this, &MainWindow::actNewModel_clicked, Qt::DirectConnection);
    connect(actNewNetworkCamera, &QAction::triggered, this, &MainWindow::actNewNetworkCamera_clicked);
    connect(actNewLocalCamera, &QAction::triggered, this, &MainWindow::actNewLocalCamera_clicked, Qt::QueuedConnection);
    connect(actConnect, &QAction::triggered, this, &MainWindow::actConnect_clicked, Qt::QueuedConnection);
    connect(actDisConnect, &QAction::triggered, this, &MainWindow::actDisConnect_clicked, Qt::QueuedConnection);
    connect(actPlay, &QAction::triggered, this, &MainWindow::actPlay_clicked, Qt::QueuedConnection);
    connect(actPause, &QAction::triggered, this, &MainWindow::actPause_clicked, Qt::QueuedConnection);
    connect(actRecord, &QAction::triggered, this, &MainWindow::actRecord_clicked, Qt::DirectConnection);
    connect(actStopRecord, &QAction::triggered, this, &MainWindow::actStopRecord_clicked, Qt::DirectConnection);
    connect(actSnap, &QAction::triggered, this, &MainWindow::actSnap_clicked, Qt::DirectConnection);
    connect(actStopSnap, &QAction::triggered, this, &MainWindow::actStopSnap_clicked, Qt::DirectConnection);
    connect(actImagePath, &QAction::triggered, this, &MainWindow::actImagePath_clicked, Qt::QueuedConnection);
    connect(actTitleStart, &QAction::triggered, this, &MainWindow::actTitleStart_clicked, Qt::QueuedConnection);
    connect(actTitleStop, &QAction::triggered, this, &MainWindow::actTitleStop_clicked, Qt::QueuedConnection);
    connect(actSetwebcam, &QAction::triggered, this, &MainWindow::actSetwebcam_clicked, Qt::QueuedConnection);
    connect(actLoadCavModel, &QAction::triggered, this, &MainWindow::actLoadCavModel_clicked, Qt::QueuedConnection);
    connect(actImageRevocation, &QAction::triggered, this, &MainWindow::actImageRevocation_clicked, Qt::QueuedConnection);
    connect(actImageRework, &QAction::triggered, this, &MainWindow::actImageRework_clicked, Qt::QueuedConnection);
    connect(actImageSave, &QAction::triggered, this, &MainWindow::actImageSaveclicked, Qt::QueuedConnection);
    connect(ui->videotab, &QTabWidget::tabCloseRequested, this, &MainWindow::TabClose);

    //滤镜信号槽
    connect(actGrayImage, &QAction::triggered, this, &MainWindow::actGrayImage_clicked, Qt::QueuedConnection);
    connect(actBinaryImage, &QAction::triggered, this, &MainWindow::actBinaryImage_clicked, Qt::QueuedConnection);
    connect(actImageMeanFilter, &QAction::triggered, this, &MainWindow::actImageMeanFilter_clicked, Qt::QueuedConnection);
    connect(actImageGaussianFilter, &QAction::triggered, this, &MainWindow::actImageGaussianFilter_clicked, Qt::QueuedConnection);
    connect(actImageMedianFilter, &QAction::triggered, this, &MainWindow::actImageMedianFilter_clicked, Qt::QueuedConnection);
    connect(actImageBilateralFilter, &QAction::triggered, this, &MainWindow::actImageBilateralFilter_clicked, Qt::QueuedConnection);

    //边缘检测信号槽
    connect(actCanny, &QAction::triggered, this, &MainWindow::actCanny_clicked, Qt::QueuedConnection);
    connect(actSobel, &QAction::triggered, this, &MainWindow::actSobel_clicked, Qt::QueuedConnection);
    connect(actScharr, &QAction::triggered, this, &MainWindow::actScharr_clicked, Qt::QueuedConnection);
    connect(actLaplacian, &QAction::triggered, this, &MainWindow::actLaplacian_clicked, Qt::QueuedConnection);
    connect(actRoberts, &QAction::triggered, this, &MainWindow::actRoberts_clicked, Qt::QueuedConnection);

    //特征提取
    connect(actSIFT, &QAction::triggered, this, &MainWindow::actSIFT_clicked, Qt::QueuedConnection);
    connect(actSURF, &QAction::triggered, this, &MainWindow::actSURF_clicked, Qt::QueuedConnection);
    connect(actBRISK, &QAction::triggered, this, &MainWindow::actBRISK_clicked, Qt::QueuedConnection);
    connect(actAKAZE, &QAction::triggered, this, &MainWindow::actAKAZE_clicked, Qt::QueuedConnection);


    //色彩校正信号槽      
    connect(actBrightness, &QAction::triggered, this, &MainWindow::actBrightness_clicked, Qt::QueuedConnection);
    connect(actContrast, &QAction::triggered, this, &MainWindow::actContrast_clicked, Qt::QueuedConnection);
    connect(actNTSC, &QAction::triggered, this, &MainWindow::actNTSC_clicked, Qt::QueuedConnection);
    connect(actCCT, &QAction::triggered, this, &MainWindow::actCCT_clicked, Qt::QueuedConnection);
    connect(actHLS, &QAction::triggered, this, &MainWindow::actHLS_clicked, Qt::QueuedConnection);
    connect(actLevels, &QAction::triggered, this, &MainWindow::actLevels_clicked, Qt::QueuedConnection);
    connect(actDilation, &QAction::triggered, this, &MainWindow::actDilation_clicked, Qt::QueuedConnection);
    connect(actErosion, &QAction::triggered, this, &MainWindow::actErosion_clicked, Qt::QueuedConnection);
    connect(actImageFFT, &QAction::triggered, this, &MainWindow::actImageFFT_clicked, Qt::QueuedConnection);
    connect(actImageHistogram, &QAction::triggered, this, &MainWindow::actImageHistogram_clicked, Qt::QueuedConnection);

    //模型预测信号槽
    connect(actModelTraining, &QAction::triggered, this, &MainWindow::actModelTraining_clicked, Qt::QueuedConnection);
    connect(actModelTesting, &QAction::triggered, this, &MainWindow::actModelTesting_clicked, Qt::QueuedConnection);
    connect(actModelSave, &QAction::triggered, this, &MainWindow::actModelSave_clicked, Qt::QueuedConnection);
    connect(actLoadOk, &QAction::triggered, this, &MainWindow::actLoadOk_clicked, Qt::QueuedConnection);
    connect(actLoadNo, &QAction::triggered, this, &MainWindow::actLoadNo_clicked, Qt::QueuedConnection);
    connect(actRandomForest, &QAction::triggered, this, &MainWindow::actRandomForest_clicked, Qt::QueuedConnection);
    connect(actSVM, &QAction::triggered, this, &MainWindow::actSVM_clicked, Qt::QueuedConnection);
    connect(actKNN, &QAction::triggered, this, &MainWindow::actKNN_clicked, Qt::QueuedConnection);

    connect(m_DockManager, &ads::CDockManager::dockWidgetRemoved, this, &MainWindow::dockWidgetRemoved, Qt::DirectConnection);

    connect(ui->videotab, &QTabWidget::currentChanged, this, &MainWindow::TabCurrentChanged, Qt::DirectConnection);
    */
    //帮助页面
    connect(actHelp, &QAction::triggered, this, &MainWindow::actHelp_clicked, Qt::QueuedConnection);
    connect(actAboutUs, &QAction::triggered, this, &MainWindow::actAboutUs_clicked, Qt::QueuedConnection);
        
    LOG(INFO) << "系统信息：事件循环配置完成";
}




//创建工具栏按钮函数
QAction* MainWindow::createAction(const QString& text, const QString& iconurl)//创建工具栏按钮函数
{
    QAction* act = new QAction(this);
    act->setText(text);
    act->setIcon(QIcon(iconurl));
    act->setObjectName(text);
    return act;
}




//项目名称值改变响应
void MainWindow::on_ExperimentString_textChanged(const QString& arg1)
{
    QString str;
    str.append(arg1 + "\n");
    str.append(ui->plainTextEdit->toPlainText());
    *subtitle = str.toStdString();
}



//下方添加窗口
void MainWindow::BottomNesting(QWidget* widget,QString name)
{    
    ads::CDockWidget* dockwidget = new ads::CDockWidget(name);
    dockwidget->setWidget(widget);
    //设置关闭后自动删除窗口
    dockwidget->setFeature(ads::CDockWidget::DockWidgetDeleteOnClose, true);
    //m_DockManager->addDockWidget(ads::CenterDockWidgetArea, dockwidget, messagearea);
}



//左侧添加窗口
void MainWindow::LeftNesting(QWidget* widget, QString name)
{
    ads::CDockWidget* dockwidget = new ads::CDockWidget(name);
    dockwidget->setWidget(widget);
    //设置关闭后自动删除窗口
    dockwidget->setFeature(ads::CDockWidget::DockWidgetDeleteOnClose, true);
    m_DockManager->addDockWidgetTab(ads::LeftDockWidgetArea, dockwidget);
}



//右侧添加窗口
void MainWindow::RightNesting(QWidget* widget, QString name)
{
    ads::CDockWidget* dockwidget = new ads::CDockWidget(name,widget);

    //设置关闭后自动删除窗口
    dockwidget->setFeature(ads::CDockWidget::DockWidgetDeleteOnClose, true);

    //绑定窗口依赖
    dockwidget->setWidget(widget);

    m_DockManager->addDockWidgetTab(ads::RightDockWidgetArea, dockwidget);

    dockwidget = nullptr;
}


//关闭后删除页面释放资源
void MainWindow::dockWidgetRemoved(ads::CDockWidget* DockWidget)
{
    delete DockWidget->takeWidget();
}



//增加TAB页面函数
std::shared_ptr<Tabwidget> MainWindow::AddTab(QString iconpath, QString name, Tabwidget::VisualItemType Type)
{
    std::shared_ptr<Tabwidget> widget(new Tabwidget);
    TabWidgetList.append(widget);
    widget->SetItemStyle(Type);
    widget->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动删除
    int cur = ui->videotab->addTab(widget.get(), QIcon("./icon/摄像头.svg"), name);
    ui->videotab->setCurrentIndex(cur);
    ui->videotab->setVisible(true);
    ui->videotab->setTabIcon(cur, QIcon(iconpath));
    return widget;
}



//新建相机项目按钮点击响应函数
void MainWindow::NewVisionProject()
{
    bool bOk = false;
    QString sName = QInputDialog::getText(this, "项目名称设置", "请输入项目名称", QLineEdit::Normal, "高压侧观测", &bOk);
    if (bOk)
    {
        presenter->CreateImageAgent(this->AddTab("./icon/摄像头.svg", sName, Tabwidget::CameraItem).get());
        LOG(INFO) << "添加相机项目";
    }
    else {
        LOG(INFO) << "取消添加相机";
    }
}



/*
图形等线程在这里面执行，业务逻辑放到下层执行

*/



//打开图片响应函数
void MainWindow::actOpenImage_clicked()
{
    // 打开文件对话框
    QString path = QFileDialog::getOpenFileName(this, "选择文件", "", "JPEG Files (*.jpg *.jpeg);;PNG Files (*.png);;BMP Files (*.bmp)");
    if (!path.isEmpty())
    {
        presenter->CreateImageAgent(this->AddTab("./icon/图像处理.svg", path, Tabwidget::ImageItem).get());
        emit Sg_OpenImage(path, ui->videotab->currentIndex());
        LOG(INFO) << "打开图片路径：" + path.toStdString() + "成功";
    }
}




//新建机器学习项目
void MainWindow::actNewModel_clicked()
{
    bool bOk = false;
    QString sName = QInputDialog::getText(this, "项目名称设置", "请输入模型名称", QLineEdit::Normal, "新建的模型", &bOk);
    if (bOk)
    {
        this->AddTab("./icon/打开模型.svg", sName, Tabwidget::CameraItem)->layout()->addWidget(new zzxml::ConfigInterface());
        LOG(INFO) << "添加模型训练项目";
    }
    else {
        LOG(INFO) << "取消模型训练项目";
    }
}



//系统日志显示控制函数
void MainWindow::actSystemLog_stateChanged(bool state)
{
    if (state) {
        if (DownArea == nullptr) {
            DownArea = m_DockManager->addDockWidget(ads::BottomDockWidgetArea, systemmessagewid, CentralDockArea);
        }
        else {
            DownArea->show();
            systemmessagewid->show();
        }
    }
    else {
        systemmessagewid->close();
        DownArea->close();
    }

}



//网络设置显示响应函数
void MainWindow::actNetSet_stateChanged(bool state)
{
    auto area = netsetwid->dockAreaWidget();
    if (state) {
        netsetwid->show();
    }
    else {
        netsetwid->close();
    }

}



//字幕设置工具栏按钮响应函数
void MainWindow::actTitleSet_stateChanged(bool state)
{
    if (state) {
        titletoolbar->show();
    }
    else {
        titletoolbar->close();
    }
}



//添加新的网络相机
void MainWindow::actNewNetworkCamera_clicked()
{
    std::shared_ptr<networkcamera> netcam(new networkcamera);
    connect(netcam.get(), &networkcamera::SelcetNetcamId, this, &MainWindow::SelcetNetcamId);//返回选择的相机
    netcam->exec();
}



//添加本地相机或者USB相机
void MainWindow::actNewLocalCamera_clicked()
{
    std::shared_ptr <LocalCameraUI> loccam(new LocalCameraUI);
    connect(loccam.get(), &LocalCameraUI::SelcetNetcamId, this, &MainWindow::SelcetNetcamId);//返回选择的相机
    loccam->exec();
}



//返回选择的相机信息，并且初始化相机
void MainWindow::SelcetNetcamId(uint idex, mjis::ICamera::CameraType Type)
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    int num = ui->videotab->currentIndex();
    if (num == -1) {
        QMessageBox::warning(this, "警告", "没有创建项目，请确认后在添加");
    }
    else {
        QString str;
        str.append(ui->ExperimentString->text() + "\n");
        str.append(ui->plainTextEdit->toPlainText());
        *subtitle = str.toStdString();
        presenter->CreateCamera(idex, Type,ui->videotab->currentIndex());
        this->actConnect->setEnabled(true);
        this->actSetwebcam->setEnabled(true);
        this->actTriggerSetting->setEnabled(true);
        this->actNewLocalCamera->setEnabled(false);
        this->actNewNetworkCamera->setEnabled(false);
        this->actSimulationCamera->setEnabled(false);
        LOG(INFO) << "已在页面" + std::to_string(num) + "添加相机";
    }
    QApplication::restoreOverrideCursor();
}



//关闭嵌入式多窗口响应函数
void MainWindow::TabClose(int index)
{
    int ret = QMessageBox::question(this, "提示", "是否关闭本窗口", QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes)
    {
        int idex = ui->videotab->currentIndex();
        emit Sg_CloseTab(ui->videotab->currentIndex());
        ui->videotab->removeTab(idex);
        TabWidgetList.removeAt(idex);
    }
}


//关闭页面成功
void MainWindow::CloseSuccess(std::shared_ptr<Tabwidget> tab)
{
    int idx=TabWidgetList.indexOf(tab);
    TabWidgetList.removeAt(idx);   
    ui->videotab->removeTab(idx);
    LOG(INFO) << "已关闭页面" << std::to_string(idx);
}
 

//相机连接
void MainWindow::actConnect_clicked()
{
    emit Sg_Connect(ui->videotab->currentIndex());
}


//断开相机连接
void MainWindow::actDisConnect_clicked()
{
    emit Sg_DisConnect(ui->videotab->currentIndex());
}



//采集按钮点击事件函数
void MainWindow::actPlay_clicked()
{
    emit Sg_Start(ui->videotab->currentIndex());
}



//停止采集按钮点击事件
void MainWindow::actPause_clicked()
{
    emit Sg_Stop(ui->videotab->currentIndex());
}



//录制按钮点击事件函数
void MainWindow::actRecord_clicked()
{
    emit Sg_StartSaveVideo(ui->videotab->currentIndex());
}



//录制按钮点击事件函数
void MainWindow::actStopRecord_clicked()
{
    emit Sg_StopSaveVideo(ui->videotab->currentIndex());
}



//快照按钮点击事件函数
void MainWindow::actSnap_clicked()
{
    emit Sg_StartSnapImage(ui->videotab->currentIndex());
}


//快照按钮点击事件函数
void MainWindow::actStopSnap_clicked()
{
    emit Sg_StopSnapImage(ui->videotab->currentIndex());
}



//字幕显示按钮
void MainWindow::actTitleStart_clicked()
{
    emit Sg_StartSub(ui->videotab->currentIndex(), subtitle, DatCC->ReturnDataSting());
    this->actTitleStart->setEnabled(false);
    this->actTitleStop->setEnabled(true);
}


//字幕停止按钮
void MainWindow::actTitleStop_clicked()
{
    emit Sg_StopSub(ui->videotab->currentIndex());
    this->actTitleStart->setEnabled(true);
    this->actTitleStop->setEnabled(false);
}



//字体颜色设置按钮
void MainWindow::on_fontcolor_clicked()
{

    // 设置颜色选择对话框的初始颜色为上次选择的颜色
    //colorDialog.setCurrentColor(colorDialog.selectedColor());

    // 显示颜色选择对话框，并获取所选颜色
    //QColor color = colorDialog.getColor();
    QColor color = QColorDialog::getColor(Qt::white, this, "Select color");
    ui->red->setValue(color.red());
    ui->green->setValue(color.green());
    ui->blue->setValue(color.blue());
}



//应用字体设置
void MainWindow::on_ApplyFontset_clicked()
{
    if (ui->videotab->currentIndex() >= 0)
    {
        emit Sg_SetFont(ui->videotab->currentIndex(), ui->OffSetX->value(), ui->OffSetY->value(), ui->red->value(), ui->green->value(), ui->blue->value(), ui->FontSize->value());
    }
}




//自定义文本值改变响应
void MainWindow::on_plainTextEdit_textChanged()
{
    QString str;
    str.append(ui->ExperimentString->text() + "\n");
    str.append(ui->plainTextEdit->toPlainText());
    *subtitle = str.toStdString();
}



//路径设置按钮点击事件函数
void MainWindow::actImagePath_clicked()
{
    VideoPathSet videoset;
    videoset.setWindowTitle(QStringLiteral("图像文件设置"));
    videoset.setWindowIcon(this->windowIcon());
    videoset.exec();
}



//相机属性页面
void MainWindow::actSetwebcam_clicked()
{

}



void MainWindow::actLoadCavModel_clicked()
{
    presenter->LoadModel();
}



//图像处理回退
void MainWindow::actImageRevocation_clicked()
{
    emit Sg_PopProcess(ui->videotab->currentIndex());
}



//图像重做函数
void MainWindow::actImageRework_clicked()
{
    emit Sg_BackProcess(ui->videotab->currentIndex());
}



//保存处理后的图片
void MainWindow::actImageSaveclicked()
{
    QString path = QFileDialog::getSaveFileName(nullptr, "选择文件", "", "JPEG Files (*.jpg *.jpeg);;PNG Files (*.png);;BMP Files (*.bmp)");
    if (!path.isEmpty()) {
        std::string str = path.toLocal8Bit().data();
        //TabImageMap.value(TabWidgetList[ui->videotab->currentIndex()])->SaveImage(str);
    }
}



//灰度化函数实现
void MainWindow::actGrayImage_clicked()
{
    mjlib::ImageGray* gray = new mjlib::ImageGray;
    if (gray != nullptr) {
        emit Sg_ProcessImage(gray, ui->videotab->currentIndex());
    }
}



//二值化函数实现
void MainWindow::actBinaryImage_clicked()
{
    mjlib::ImageBinaryzation* process = ImageLibConnect::CreateBinary(true);
    if (process != nullptr) {
        emit Sg_ProcessImage(process, ui->videotab->currentIndex());
        LOG(INFO) << "图像处理模块：二值化完成";
    }
}




//均值滤波
void MainWindow::actImageMeanFilter_clicked()
{
    mjlib::ImageMeanFilter* process = ImageLibConnect::CreateMean(true);
    if (process != nullptr) {
        emit Sg_ProcessImage(process, ui->videotab->currentIndex());
    }

}


//高斯滤波
void MainWindow::actImageGaussianFilter_clicked()
{
    mjlib::ImageGaussianFilter* process = ImageLibConnect::CreateGaussian(true);
    if (process != nullptr) {
        emit Sg_ProcessImage(process, ui->videotab->currentIndex());
    }
}



//中值滤波
void MainWindow::actImageMedianFilter_clicked()
{
    mjlib::ImageMedianFilter* process = ImageLibConnect::CreateMedian(true);
    if (process != nullptr) {
        emit Sg_ProcessImage(process, ui->videotab->currentIndex());
        LOG(INFO) << "图像处理模块：中值滤波完成";
    }
}




//双边滤波
void MainWindow::actImageBilateralFilter_clicked()
{
    mjlib::ImageBilateralFilter* process = ImageLibConnect::CreateBilateral(true);
    if (process != nullptr) {
        emit Sg_ProcessImage(process, ui->videotab->currentIndex());
        LOG(INFO) << "图像处理模块：双边滤波完成";
    }

}


//Canny算子
void MainWindow::actCanny_clicked()
{
    try {
        LOG(INFO) << "图像处理模块：Canny算子检测完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：Canny算子检测失败 异常：" << e.what();
    }
}


//Sobel算子
void MainWindow::actSobel_clicked()
{
    try {
        std::shared_ptr<mjlib::Sobel> sob(new mjlib::Sobel);
        //TabImageMap.value(TabWidgetList[ui->videotab->currentIndex()])->ImageProcessResult(sob.get());
        LOG(INFO) << "图像处理模块：Sobel算子检测完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：Sobel算子检测失败 异常：" << e.what();
    }
}



//Scharr算子
void MainWindow::actScharr_clicked()
{
    try {
        mjlib::Scharr Scharr;
        //TabImageMap.value(TabWidgetList[ui->videotab->currentIndex()])->ImageProcessResult(&Scharr);
        LOG(INFO) << "图像处理模块：Scharr算子检测完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：Scharr算子检测失败 异常：" << e.what();
    }
}



//Laplacian算子
void MainWindow::actLaplacian_clicked()
{
    try {
        mjlib::Laplacian filt;
        //TabImageMap.value(TabWidgetList[ui->videotab->currentIndex()])->ImageProcessResult(&filt);
        LOG(INFO) << "图像处理模块：Laplacian算子检测完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：Laplacian算子检测失败 异常：" << e.what();
    }
}



//Roberts算子
void MainWindow::actRoberts_clicked()
{
    try {
        mjlib::Roberts filt;
        LOG(INFO) << "图像处理模块：Roberts算子检测完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：Roberts算子检测失败 异常：" << e.what();
    }
}




//SIFT
void MainWindow::actSIFT_clicked()
{
    try {
        mjlib::SIFT filt;
        LOG(INFO) << "图像处理模块：SIFT特征提取完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：SIFT特征提取失败 异常：" << e.what();
    }
}



//SURF
void MainWindow::actSURF_clicked()
{
    try {
        mjlib::SURF filt;
        LOG(INFO) << "图像处理模块：SURF特征提取完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：SURF特征提取失败 异常：" << e.what();
    }
}



//BRISK
void MainWindow::actBRISK_clicked()
{
    try {
        mjlib::BRISK filt;
        LOG(INFO) << "图像处理模块：BRISK特征提取完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：BRISK特征提取失败 异常：" << e.what();
    }
}


//AKAZE
void MainWindow::actAKAZE_clicked()
{
    try {
        mjlib:: AKAZE filt;
        LOG(INFO) << "图像处理模块：AKAZE特征提取完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：AKAZE特征提取失败 异常：" << e.what();
    }
}



//亮度调节
void MainWindow::actBrightness_clicked()
{
    try {
        mjlib::Bright bri;
        LOG(INFO) << "图像处理模块：亮度调节完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：亮度调节失败 异常：" << e.what();
    }
}


//对比度调节
void MainWindow::actContrast_clicked()
{
    try {
        mjlib::Contrast cts;
        //TabImageMap.value(TabWidgetList[ui->videotab->currentIndex()])->ImageProcessResult(&cts);
        LOG(INFO) << "图像处理模块：对比度调节完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：对比度调节失败 异常：" << e.what();
    }
}


//饱和度调节
void MainWindow::actNTSC_clicked()
{
    try {
        mjlib::NTSC ntsc;
        //TabImageMap.value(TabWidgetList[ui->videotab->currentIndex()])->ImageProcessResult(&ntsc);
        LOG(INFO) << "图像处理模块：饱和度调节完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：饱和度调节失败 异常：" << e.what();
    }
}

//色温调节
void MainWindow::actCCT_clicked()
{
    try {
        mjlib::CCT cct;
        //TabImageMap.value(TabWidgetList[ui->videotab->currentIndex()])->ImageProcessResult(&cct);
        LOG(INFO) << "图像处理模块：色温调节完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：色温调节失败 异常：" << e.what();
    }
}


//色彩平衡调节
void MainWindow::actHLS_clicked()
{
    try {
        mjlib::AKAZE filt;
        //TabImageMap.value(TabWidgetList[ui->videotab->currentIndex()])->ImageProcessResult(&filt);
        LOG(INFO) << "图像处理模块：双边滤波完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：双边滤波失败 异常：" << e.what();
    }
}

//色阶调节
void MainWindow::actLevels_clicked()
{
    try {
        mjlib::Levels lv;
        //TabImageMap.value(TabWidgetList[ui->videotab->currentIndex()])->ImageProcessResult(&lv);
        LOG(INFO) << "图像处理模块：色阶调节完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：色阶调节失败 异常：" << e.what();
    }
}



//膨胀
void MainWindow::actDilation_clicked()
{
    try {
        mjlib::Expand epd;
        //TabImageMap.value(TabWidgetList[ui->videotab->currentIndex()])->ImageProcessResult(&epd);
        LOG(INFO) << "图像处理模块：膨胀处理完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：膨胀处理失败 异常：" << e.what();
    }
}


//腐蚀
void MainWindow::actErosion_clicked()
{
    try {
        mjlib::Corrosion crs;
        //TabImageMap.value(TabWidgetList[ui->videotab->currentIndex()])->ImageProcessResult(&crs);
        LOG(INFO) << "图像处理模块：腐蚀处理完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：腐蚀处理失败 异常：" << e.what();
    }
}




//频谱图函数实现
void MainWindow::actImageFFT_clicked()
{
    mjlib::AKAZE fft;
    //TabImageMap.value(TabWidgetList[ui->videotab->currentIndex()])->ImageProcessResult(&fft);
}



//灰度直方图函数实现
void MainWindow::actImageHistogram_clicked()
{
    mjis::hmi::ChartWidget* chart = new mjis::hmi::ChartWidget();

    // 设置坐标轴
    chart->SetXYName("灰度级", "像素数");

    emit Sg_DrawChart(chart,ui->videotab->currentIndex());
}



//灰度直方图绘制完成
void MainWindow::DrawChartSuccess(mjis::hmi::ChartWidget* chart,const QString& name)
{
    this->BottomNesting(chart, name);
    chart->RescaleAxes();
}



//测试连接
void MainWindow::actTryRemotConnect_clicked()
{
    if (DataCommumication::Ping("192.168.1.2")) {
        LOG(INFO) << "数据连接模块：连接失败";
    }
    else {
        LOG(INFO) << "数据连接模块：连接成功";
    }
}


//模型训练
void MainWindow::actModelTraining_clicked()
{

}



//模型测试
void MainWindow::actModelTesting_clicked()
{

}


//模型保存
void MainWindow::actModelSave_clicked()
{

}


//导入OK文件夹
void MainWindow::actLoadOk_clicked()
{   
    // 创建一个文件选择对话框
    QFileDialog dialog;

    // 设置对话框选项
    dialog.setFileMode(QFileDialog::Directory);  // 可选择任意文件
    dialog.setViewMode(QFileDialog::Detail);   // 显示详细信息

    // 弹出文件选择对话框
    if (dialog.exec())
    {
        // 获取选择的文件路径
        std::string okpath = dialog.selectedFiles().at(0).toLocal8Bit().toStdString();

        zzxml::ConfigInterface* cfif = TabWidgetList[ui->videotab->currentIndex()]->findChild<zzxml::ConfigInterface*>();

        cfif->ReadOkPreData();

    }
}


//导入NO文件夹
void MainWindow::actLoadNo_clicked()
{

}

//随机森林框架
void MainWindow::actRandomForest_clicked()
{

}

//SVM框架
void MainWindow::actSVM_clicked()
{

}


//KNN框架
void MainWindow::actKNN_clicked()
{

}


//帮助页面
void MainWindow::actHelp_clicked()
{
    DatCC->ReturnDataSting();
}



//关于页面
void MainWindow::actAboutUs_clicked()
{
    mjis::hmi::AboutMe am;
    am.exec();
}



//TAB页面改变伴随状态改变,观察者的一种变种
void MainWindow::TabCurrentChanged(int index)
{
    if (index >= 0) {
        switch (TabWidgetList[index]->GetItemStyle())
        {
        case Tabwidget::CameraItem:
            ChangeCameraState();
            break;
        case Tabwidget::ImageItem:
            ChangeImageState(index);
            break;
        case Tabwidget::VideoItem:
            break;
        default:
            break;
        }
    }
    //项目全关后禁用这些操作
    else {
        this->DisableImage();
        this->DisableIVision();
    }
}



//改变相机界面状态,这个方法说实话有点麻烦，应该有更好的办法，先这样有空在想
void MainWindow::ChangeCameraState()
{
    int idex = ui->videotab->currentIndex();

    if (presenter->ReturnCameraPoint(idex) == nullptr) {
        //判断相机加载状态
        this->actNewLocalCamera->setEnabled(true);
        this->actNewNetworkCamera->setEnabled(true);
    }
    else {
        //获取连接状态
        auto cont = presenter->ReturnCameraConnect(idex);
        this->actConnect->setEnabled(!cont);
        this->actDisConnect->setEnabled(cont);
        if (cont) {
            //获取采集状态
            auto bpst = presenter->ReturnCameraGrap(idex);
            this->actPlay->setEnabled(!bpst);
            this->actPause->setEnabled(bpst);

            //如果是正常采集状态则激活录像和快照
            if (bpst) {
                auto svst = presenter->ReturnSaveState(idex);
                this->actRecord->setEnabled(!svst);
                this->actStopRecord->setEnabled(svst);

                //获取快照状态     
                auto snst = presenter->ReturnSnapState(idex);
                this->actSnap->setEnabled(!snst);
                this->actStopSnap->setEnabled(snst);

                auto stst= presenter->ReturnSnapState(idex);
                this->actTitleStart->setEnabled(stst);
                this->actTitleStop->setEnabled(!stst);
                this->actLoadCavModel->setEnabled(true);
            }
            else {
                this->actRecord->setEnabled(false);
                this->actStopRecord->setEnabled(false);
                this->actSnap->setEnabled(false);
                this->actStopSnap->setEnabled(false);
                //this->actLoadCavModel->setEnabled(false);
            }
        }
        else {
            this->actPlay->setEnabled(false);
            this->actPause->setEnabled(false);
            this->actRecord->setEnabled(false);
            this->actStopRecord->setEnabled(false);
            this->actSnap->setEnabled(false);
            this->actStopSnap->setEnabled(false);
            this->actTitleStart->setEnabled(false);
            this->actTitleStop->setEnabled(false);
            //this->actLoadCavModel->setEnabled(false);
        }
    }

}



//改变图像界面状态,这个方法说实话有点麻烦，应该有更好的办法，先这样有空在想
void MainWindow::ChangeImageState(int idx)
{
    this->actImageRevocation->setEnabled(true);
    this->actImageRework->setEnabled(true);
    this->actImageSave->setEnabled(true);
    this->actGrayImage->setEnabled(true);
    this->actBinaryImage->setEnabled(true);
    this->actImageBilateralFilter->setEnabled(true);
    this->actImageFFT->setEnabled(true);
    this->actImageHistogram->setEnabled(true);

    this->galleryFileter->setEnabled(true);
    this->galleryEdgeDetection->setEnabled(true);
    this->galleryFeatureExtraction->setEnabled(true);

    this->actBrightness->setEnabled(true);
    this->actContrast->setEnabled(true);
    this->actNTSC->setEnabled(true);
    this->actCCT->setEnabled(true);
    this->actHLS->setEnabled(true);
    this->actLevels->setEnabled(true);
    this->actDilation->setEnabled(true);
    this->actErosion->setEnabled(true);

    this->DisableIVision();
}


