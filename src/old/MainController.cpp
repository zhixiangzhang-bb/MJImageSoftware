#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>

#ifndef GLOG_NO_ABBREVIATED_SEVERITIES
# ifdef ERROR
#  undef ERROR
# endif
const int INFO = GLOG_INFO, WARNING = GLOG_WARNING,
ERROR = GLOG_ERROR, FATAL = GLOG_FATAL;
#endif



#include "MainController.h"
#include "videopathset.h"
#include <filesystem>
#include "aboutme.h"
#include <QFormLayout>
#include <QSpinBox>
#include <QDialogButtonBox>
#include "ImageLibConnect.h"





//构造函数
MainController::MainController(QObject *parent)
	: QObject(parent)
{
    this->InitLogging();

    MainWin=new MainWindow;

    //创建通讯管理器
    DatCC = std::make_shared<DataCommumication>(this);
    MainWin->AddNetWorkWidget(DatCC->ReturnUI());
	MainWin->show();

    this->InitSignalsAndSlots();


    LOG(INFO) << "系统事件：应用程序初始化成功";


}




//析构函数
MainController::~MainController()
{
    // 关闭日志记录器
    google::ShutdownGoogleLogging();
    LOG(INFO) << "系统消息：应用程序退出";
}




//初始化日志记录器
void MainController::InitLogging()
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





//初始化信号和槽
void MainController::InitSignalsAndSlots()
{
    //主页信号槽
    connect(MainWin->actNewvisionproject, &QAction::triggered, this, &MainController::NewVisionProject);
    connect(MainWin->actOpenImage, &QAction::triggered, this, &MainController::actOpenImage_clicked, Qt::DirectConnection);
    connect(MainWin->actNewModel, &QAction::triggered, this, &MainController::actNewModel_clicked, Qt::DirectConnection);
    connect(MainWin->actNewNetworkCamera, &QAction::triggered, this, &MainController::actNewNetworkCamera_clicked);
    connect(MainWin->actNewLocalCamera, &QAction::triggered, this, &MainController::actNewLocalCamera_clicked, Qt::QueuedConnection);
    connect(MainWin->TabWidget, &QTabWidget::tabCloseRequested, this, &MainController::on_videotab_tabCloseRequested);
    connect(MainWin->actConnect, &QAction::triggered, this, &MainController::actConnect_clicked, Qt::QueuedConnection);
    connect(MainWin->actDisConnect, &QAction::triggered, this, &MainController::actDisConnect_clicked, Qt::QueuedConnection);
    connect(MainWin->actPlay, &QAction::triggered, this, &MainController::actPlay_clicked, Qt::QueuedConnection);
    connect(MainWin->actPause, &QAction::triggered, this, &MainController::actPause_clicked, Qt::QueuedConnection);
    connect(MainWin->actRecord, &QAction::triggered, this, &MainController::actRecord_clicked, Qt::DirectConnection);
    connect(MainWin->actSnap, &QAction::triggered, this, &MainController::actSnap_clicked, Qt::DirectConnection);
    //connect(MainWin, &MainWindow::AplyFontFormat, this, &MainController::AplyFontFormat, Qt::DirectConnection);
    connect(MainWin->actImagePath, &QAction::triggered, this, &MainController::actImagePath_clicked, Qt::QueuedConnection);
    connect(MainWin->actTitleStart, &QAction::triggered, this, &MainController::actTitleStart_clicked, Qt::QueuedConnection);
    connect(MainWin->actTitleStop, &QAction::triggered, this, &MainController::actTitleStop_clicked, Qt::QueuedConnection);
    connect(MainWin->actSetwebcam, &QAction::triggered, this, &MainController::actSetwebcam_clicked, Qt::QueuedConnection);
    connect(MainWin->actImageRevocation, &QAction::triggered, this, &MainController::actImageRevocation_clicked, Qt::QueuedConnection);
    connect(MainWin->actImageRework, &QAction::triggered, this, &MainController::actImageRework_clicked, Qt::QueuedConnection);
    connect(MainWin->actImageSave, &QAction::triggered, this, &MainController::actImageSaveclicked, Qt::QueuedConnection);

    //滤镜信号槽
    connect(MainWin->actGrayImage, &QAction::triggered, this, &MainController::actGrayImage_clicked, Qt::QueuedConnection);
    connect(MainWin->actBinaryImage, &QAction::triggered, this, &MainController::actBinaryImage_clicked, Qt::QueuedConnection);
    connect(MainWin->actImageMeanFilter, &QAction::triggered, this, &MainController::actImageMeanFilter_clicked, Qt::QueuedConnection);
    connect(MainWin->actImageGaussianFilter, &QAction::triggered, this, &MainController::actImageGaussianFilter_clicked, Qt::QueuedConnection);
    connect(MainWin->actImageMedianFilter, &QAction::triggered, this, &MainController::actImageMedianFilter_clicked, Qt::QueuedConnection);
    connect(MainWin->actImageBilateralFilter, &QAction::triggered, this, &MainController::actImageBilateralFilter_clicked, Qt::QueuedConnection);

    //边缘检测信号槽
    connect(MainWin->actCanny, &QAction::triggered, this, &MainController::actCanny_clicked, Qt::QueuedConnection);
    connect(MainWin->actSobel, &QAction::triggered, this, &MainController::actSobel_clicked, Qt::QueuedConnection);
    connect(MainWin->actScharr, &QAction::triggered, this, &MainController::actScharr_clicked, Qt::QueuedConnection);
    connect(MainWin->actLaplacian, &QAction::triggered, this, &MainController::actLaplacian_clicked, Qt::QueuedConnection);
    connect(MainWin->actRoberts, &QAction::triggered, this, &MainController::actRoberts_clicked, Qt::QueuedConnection);

    //特征提取
    connect(MainWin->actSIFT, &QAction::triggered, this, &MainController::actSIFT_clicked, Qt::QueuedConnection);
    connect(MainWin->actSURF, &QAction::triggered, this, &MainController::actSURF_clicked, Qt::QueuedConnection);
    connect(MainWin->actBRISK, &QAction::triggered, this, &MainController::actBRISK_clicked, Qt::QueuedConnection);
    connect(MainWin->actAKAZE, &QAction::triggered, this, &MainController::actAKAZE_clicked, Qt::QueuedConnection);


    //色彩校正信号槽      
    connect(MainWin->actBrightness, &QAction::triggered, this, &MainController::actBrightness_clicked, Qt::QueuedConnection);
    connect(MainWin->actContrast, &QAction::triggered, this, &MainController::actContrast_clicked, Qt::QueuedConnection);
    connect(MainWin->actNTSC, &QAction::triggered, this, &MainController::actNTSC_clicked, Qt::QueuedConnection);
    connect(MainWin->actCCT, &QAction::triggered, this, &MainController::actCCT_clicked, Qt::QueuedConnection);
    connect(MainWin->actHLS, &QAction::triggered, this, &MainController::actHLS_clicked, Qt::QueuedConnection);
    connect(MainWin->actLevels, &QAction::triggered, this, &MainController::actLevels_clicked, Qt::QueuedConnection);
    connect(MainWin->actDilation, &QAction::triggered, this, &MainController::actDilation_clicked, Qt::QueuedConnection);
    connect(MainWin->actErosion, &QAction::triggered, this, &MainController::actErosion_clicked, Qt::QueuedConnection);
    connect(MainWin->actImageFFT, &QAction::triggered, this, &MainController::actImageFFT_clicked, Qt::QueuedConnection);
    connect(MainWin->actImageHistogram, &QAction::triggered, this, &MainController::actImageHistogram_clicked, Qt::QueuedConnection);

    //模型预测信号槽
    connect(MainWin->actModelTraining, &QAction::triggered, this, &MainController::actModelTraining_clicked, Qt::QueuedConnection);
    connect(MainWin->actModelTesting, &QAction::triggered, this, &MainController::actModelTesting_clicked, Qt::QueuedConnection);
    connect(MainWin->actModelSave, &QAction::triggered, this, &MainController::actModelSave_clicked, Qt::QueuedConnection);

    connect(MainWin->m_DockManager, &ads::CDockManager::dockWidgetRemoved, this, &MainController::dockWidgetRemoved, Qt::DirectConnection);

    connect(MainWin->GetTabPoint(), &QTabWidget::currentChanged, this, &MainController::TabCurrentChanged, Qt::DirectConnection);

    //帮助页面
    connect(MainWin->actHelp, &QAction::triggered, this, &MainController::actHelp_clicked, Qt::QueuedConnection);
    connect(MainWin->actAboutUs, &QAction::triggered, this, &MainController::actAboutUs_clicked, Qt::QueuedConnection);

    LOG(INFO) << "系统事件: 事件循环配置完毕";
}



//关闭后删除页面释放资源
void MainController::dockWidgetRemoved(ads::CDockWidget* DockWidget)
{
    delete DockWidget->takeWidget();
}



//增加TAB页面函数
Tabwidget* MainController::AddTab(QString iconpath,QString name, Tabwidget::VisualItemType Type)
{
    std::shared_ptr<Tabwidget> widget(new Tabwidget);
    TabWidgetList.append(widget);
    widget->SetItemStyle(Type);
    widget->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动删除
    int cur = MainWin->TabWidget->addTab(widget.get(), QIcon("./icon/摄像头.svg"), name);
    MainWin->TabWidget->setCurrentIndex(cur);
    MainWin->TabWidget->setVisible(true);
    MainWin->TabWidget->setTabIcon(cur, QIcon(iconpath));
    return widget.get();
}



//新建相机项目按钮点击响应函数
void MainController::NewVisionProject()
{
    bool bOk = false;
    QString sName = QInputDialog::getText(MainWin, "项目名称设置", "请输入项目名称", QLineEdit::Normal, "高压侧观测", &bOk);
    if (bOk)
    {
        this->AddTab("./icon/摄像头.svg", sName, Tabwidget::CameraItem);
        LOG(INFO) << "添加相机项目";
    }
    else {
        LOG(INFO) << "取消添加相机";
    }
}




//打开图片响应函数
void MainController::actOpenImage_clicked()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    // 打开文件对话框
    QString path = QFileDialog::getOpenFileName(nullptr, "选择文件", "", "JPEG Files (*.jpg *.jpeg);;PNG Files (*.png);;BMP Files (*.bmp)");     
    if (!path.isEmpty())
    {
        std::shared_ptr<Tabwidget> widget(this->AddTab("./icon/图像处理.svg", path, Tabwidget::ImageItem));
        std::shared_ptr <ImageControl> image(new ImageControl);
        TabImageMap.insert(widget, image);
        std::string str = path.toLocal8Bit().data();
        widget->layout()->addWidget(image->OpenImage(str));

        LOG(INFO) << "打开图片路径："+ path.toStdString()+"成功";
    }
    QApplication::restoreOverrideCursor();
}


//新建机器学习项目
void MainController::actNewModel_clicked()
{
    bool bOk = false;
    QString sName = QInputDialog::getText(MainWin, "项目名称设置", "请输入模型名称", QLineEdit::Normal, "新建的模型", &bOk);
    if (bOk)
    {
        this->AddTab("./icon/打开模型.svg", sName, Tabwidget::MachineItem)->layout()->addWidget(mlManage::CreateConfigItf());
        LOG(INFO) << "添加模型训练项目";
    }
    else {
        LOG(INFO) << "取消模型训练项目";
    }

}

//添加新的网络相机
void MainController::actNewNetworkCamera_clicked()
{
    std::shared_ptr<networkcamera> netcam(new networkcamera);
    connect(netcam.get(), &networkcamera::SelcetNetcamId, this, &MainController::SelcetNetcamId);//返回选择的相机
    netcam->exec();
}



//添加本地相机或者USB相机
void MainController::actNewLocalCamera_clicked()
{
    std::shared_ptr <LocalCameraUI> loccam(new LocalCameraUI);
    connect(loccam.get(), &LocalCameraUI::SelcetNetcamId, this, &MainController::SelcetNetcamId);//返回选择的相机
    loccam->exec();
}



//返回选择的相机信息，并且初始化相机
void MainController::SelcetNetcamId(uint idex, CameraType Type)
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    int num = this->MainWin->TabWidget->currentIndex();
    MyDockWidget* dock;
    if (num == -1) {
        QMessageBox::warning(MainWin, "警告", "没有创建项目，请确认后在添加");
    }
    else {
        //查询表里有没有键
        if (TabCameraMap.contains(TabWidgetList[num])) {
            dock = TabCameraMap.value(TabWidgetList[num])->CreateCamera(idex, Type);
        }
        else {
            std::shared_ptr <CameraImageManage> cim(new CameraImageManage);
            dock = cim->CreateCamera(idex, Type);
            cim->SetSubTitle(MainWin->ReturnSubTitle(), DatCC->ReturnDataSting());
            TabCameraMap.insert(TabWidgetList[num], cim);
        }
        TabWidgetList[num]->layout()->addWidget(dock); 
        MainWin->actConnect->setEnabled(true);
        MainWin->actSetwebcam->setEnabled(true);
        MainWin->actTriggerSetting->setEnabled(true);
        MainWin->actNewLocalCamera->setEnabled(false);
        MainWin->actNewNetworkCamera->setEnabled(false);
        MainWin->actSimulationCamera->setEnabled(false);
        LOG(INFO) << "已在页面"+ std::to_string(num)+"添加相机";
    }
    QApplication::restoreOverrideCursor();
}



//关闭嵌入式多窗口响应函数
void MainController::on_videotab_tabCloseRequested(int index)
{
    int ret = QMessageBox::question(MainWin, "提示", "是否关闭本窗口", QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes) 
    {
        std::shared_ptr<Tabwidget> tab = TabWidgetList[index];
        //如果是相机项目释放相机资源
        if (TabCameraMap.contains(tab)) {
            bool a=TabCameraMap.remove(tab);
        }

        //如果是图片处理释放图片资源
        if (TabImageMap.contains(TabWidgetList[index])) {
            bool a=TabImageMap.remove(TabWidgetList[index]);
        }

        MainWin->TabWidget->removeTab(index);
        TabWidgetList.removeAt(index);
        LOG(INFO) << "已关闭页面" <<std::to_string(index);
    }
}



//相机连接
void MainController::actConnect_clicked()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    std::shared_ptr<CameraImageManage> cim = TabCameraMap.value(TabWidgetList[MainWin->TabWidget->currentIndex()]);
    cim->ConnectCamera(0);
    LOG(INFO) << "用户事件: 已连接相机"+ std::to_string(cim->GetCameraId());
    MainWin->actConnect->setEnabled(false);
    MainWin->actDisConnect->setEnabled(true);
    MainWin->actPlay->setEnabled(true);
    QApplication::restoreOverrideCursor();
}


//断开相机连接
void MainController::actDisConnect_clicked()
{

    QApplication::setOverrideCursor(Qt::WaitCursor);
    std::shared_ptr<CameraImageManage> cim = TabCameraMap.value(TabWidgetList[MainWin->TabWidget->currentIndex()]);
    cim->DisConnectCamera(0);
    MainWin->actConnect->setEnabled(true);
    MainWin->actDisConnect->setEnabled(false);
    MainWin->actPlay->setEnabled(false);
    MainWin->actPause->setEnabled(false);
    LOG(INFO) << "用户事件: 已连接相机" + std::to_string(cim->GetCameraId());
    QApplication::restoreOverrideCursor();      
}



//采集按钮点击事件函数
void MainController::actPlay_clicked()
{
    try {
        TabCameraMap.value(TabWidgetList[MainWin->TabWidget->currentIndex()])->StartGrap(0);
        MainWin->actPlay->setEnabled(false);
        MainWin->actPause->setEnabled(true);
        MainWin->actRecord->setEnabled(true);
        MainWin->actSnap->setEnabled(true);
        MainWin->actTitleStart->setEnabled(true);
        LOG(INFO) << "相机模块：开始采集成功";
    }
    catch (const std::exception& e) {
        MainWin->actPlay->setEnabled(false);
        MainWin->actPause->setEnabled(false);
        MainWin->actRecord->setEnabled(false);
        MainWin->actSnap->setEnabled(false);
        LOG(ERROR) << "相机模块：开始采集失败 异常：" << e.what();
    }
}




//停止采集按钮点击事件
void MainController::actPause_clicked()
{
    try {
        TabCameraMap.value(TabWidgetList[MainWin->TabWidget->currentIndex()])->StopGrap(0);
        MainWin->actPlay->setEnabled(true);
        MainWin->actPause->setEnabled(false);
        MainWin->actRecord->setEnabled(false);
        MainWin->actSnap->setEnabled(false);
        LOG(INFO) << "相机模块：停止采集成功";
    }
    catch (const std::exception& e) {
        MainWin->actPlay->setEnabled(false);
        MainWin->actPause->setEnabled(false);
        MainWin->actRecord->setEnabled(false);
        MainWin->actSnap->setEnabled(false);
        LOG(ERROR) << "相机模块：停止采集失败 异常：" << e.what();
    }
}



//录制按钮点击事件函数
void MainController::actRecord_clicked()
{
    //先读取配置文件参数
    QSettings settings("E:/ZImageSoft/CavitationAPP/Config/imagepath.cfg", QSettings::IniFormat);
    QString VideoPath = settings.value("videopath").toString() + "test";

    //将字符串转成std
    VideoSavePath = VideoPath.toLocal8Bit().data();

    //根据状态判断录制状态
    if (MainWin->actRecord->isChecked()) {
        TabCameraMap.value(TabWidgetList[MainWin->TabWidget->currentIndex()])->StartSaveVideo(VideoSavePath, ImageSaveVideo::MJPG, 30, 640, 480);
        MainWin->actRecord->setChecked(true);
        MainWin->actRecord->setIcon(QIcon("./icon/停止录制视频.svg"));
    }
    else {
        TabCameraMap.value(TabWidgetList[MainWin->TabWidget->currentIndex()])->StopSaveVideo(0);
        MainWin->actRecord->setChecked(false);
        MainWin->actRecord->setIcon(QIcon("./icon/开始录制视频.svg"));
    }
}


//快照按钮点击事件函数
void MainController::actSnap_clicked()
{
    if (MainWin->actSnap->isChecked()) {
        QString pathstr = "E:/ZImageSoft/CavitationAPP/Test/" + QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
        QDir().mkpath(pathstr);
        pathstr = pathstr + "/测试数据";
        ImageSavePath = pathstr.toLocal8Bit().data();
        //ImageSavePath = pathstr.toStdString();
        TabCameraMap.value(TabWidgetList[MainWin->TabWidget->currentIndex()])->StartSnapVideo(ImageSavePath, ImageSnapImage::PNG, 640, 480);
        MainWin->actSnap->setChecked(true);
        MainWin->actSnap->setIcon(QIcon("./icon/停止连续采集.svg"));
    }
    else 
    {
        TabCameraMap.value(TabWidgetList[MainWin->TabWidget->currentIndex()])->StopSnapVideo();
        MainWin->actSnap->setChecked(false);
        MainWin->actSnap->setIcon(QIcon("./icon/连续采集.svg"));
    }
}



//字幕显示按钮
void MainController::actTitleStart_clicked()
{
    TabCameraMap.value(TabWidgetList[MainWin->TabWidget->currentIndex()])->StartSubTitle();
    MainWin->actTitleStart->setEnabled(false);
    MainWin->actTitleStop->setEnabled(true);
}


//字幕停止按钮
void MainController::actTitleStop_clicked()
{
    TabCameraMap.value(TabWidgetList[MainWin->TabWidget->currentIndex()])->StopSubTitle();
    MainWin->actTitleStart->setEnabled(true);
    MainWin->actTitleStop->setEnabled(false);
}


void MainController::AplyFontFormat(std::string fontpath, uint offsetx, uint offsety, uint cR, uint cG, uint cB, uint fontheight)
{
    if (MainWin->TabWidget->currentIndex()>=0)
    {
        std::shared_ptr<Tabwidget> tab = TabWidgetList[MainWin->TabWidget->currentIndex()];
        if (TabCameraMap.contains(tab)) {
            TabCameraMap.value(tab)->SetFontParam(offsetx, offsety, cR, cG, cB, fontheight);
        }
    }
}



//路径设置按钮点击事件函数
void MainController::actImagePath_clicked()
{
    VideoPathSet videoset;
    videoset.setWindowTitle(QStringLiteral("图像文件设置"));
    videoset.setWindowIcon(MainWin->windowIcon());
    videoset.exec();
}


//相机属性页面
void MainController::actSetwebcam_clicked()
{
    TabCameraMap.value(TabWidgetList[MainWin->TabWidget->currentIndex()])->OpenCameraSetSheet();
}




//图像处理回退
void MainController::actImageRevocation_clicked()
{
    try {
        TabImageMap.value(TabWidgetList[MainWin->TabWidget->currentIndex()])->PopProcess();
        LOG(INFO) << "图像处理模块：撤回完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：撤回失败 异常：" << e.what();
    }
}




//图像重做函数
void MainController::actImageRework_clicked()
{

}



//保存处理后的图片
void MainController::actImageSaveclicked()
{
    QString path = QFileDialog::getSaveFileName(nullptr, "选择文件", "", "JPEG Files (*.jpg *.jpeg);;PNG Files (*.png);;BMP Files (*.bmp)");
    if (!path.isEmpty()) {
        std::string str = path.toLocal8Bit().data();
        TabImageMap.value(TabWidgetList[MainWin->TabWidget->currentIndex()])->SaveImage(str);
    }
}



//灰度化函数实现
void MainController::actGrayImage_clicked()
{
    try {
        std::shared_ptr<ImageGray> gray(new ImageGray);
        TabImageMap.value(TabWidgetList[MainWin->TabWidget->currentIndex()])->ImageProcessResult(gray.get());
        LOG(INFO) << "图像处理模块：灰度化完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：灰度化失败 异常："<<e.what();
    }
}


//二值化函数实现
void MainController::actBinaryImage_clicked()
{

    try {
        ImageBinaryzation* process=ImageLibConnect::CreateBinary(true);
        if (process != nullptr) {
            std::shared_ptr<ImageBinaryzation> binary(process);
            TabImageMap.value(TabWidgetList[MainWin->TabWidget->currentIndex()])->ImageProcessResult(binary.get());
            LOG(INFO) << "图像处理模块：二值化完成";
        }
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：二值化失败 异常：" << e.what();
    }
}



//均值滤波
void MainController::actImageMeanFilter_clicked()
{
    try {
        ImageMeanFilter* process = ImageLibConnect::CreateMean(true);
        if (process != nullptr) {
            std::shared_ptr<ImageMeanFilter> Mean(process);
            TabImageMap.value(TabWidgetList[MainWin->TabWidget->currentIndex()])->ImageProcessResult(Mean.get());
            LOG(INFO) << "图像处理模块：均值模糊完成";
        }
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：均值模糊失败 异常：" << e.what();
    }

}


//高斯滤波
void MainController::actImageGaussianFilter_clicked()
{
    try {
        ImageGaussianFilter* process = ImageLibConnect::CreateGaussian(true);
        if (process != nullptr) {
            std::shared_ptr<ImageGaussianFilter> Gaussian(process);
            TabImageMap.value(TabWidgetList[MainWin->TabWidget->currentIndex()])->ImageProcessResult(Gaussian.get());
            LOG(INFO) << "图像处理模块：高斯滤波完成";
        }
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：高斯滤波失败 异常：" << e.what();
    }
}



//中值滤波
void MainController::actImageMedianFilter_clicked()
{

    try {
        ImageMedianFilter* process = ImageLibConnect::CreateMedian(true);
        if (process != nullptr) {
            std::shared_ptr<ImageMedianFilter> Median(process);
            TabImageMap.value(TabWidgetList[MainWin->TabWidget->currentIndex()])->ImageProcessResult(Median.get());
            LOG(INFO) << "图像处理模块：中值滤波完成";
        }
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：中值滤波失败 异常：" << e.what();
    }
}




//双边滤波
void MainController::actImageBilateralFilter_clicked()
{
    try {
        ImageBilateralFilter* process = ImageLibConnect::CreateBilateral(true);
        if (process != nullptr) {
            std::shared_ptr<ImageBilateralFilter> Bilateral(new ImageBilateralFilter);
            TabImageMap.value(TabWidgetList[MainWin->TabWidget->currentIndex()])->ImageProcessResult(Bilateral.get());
            LOG(INFO) << "图像处理模块：双边滤波完成";
        }
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：双边滤波失败 异常：" << e.what();
    }
}


//Canny算子
void MainController::actCanny_clicked()
{
    try {
        Canny Canny;
        TabImageMap.value(TabWidgetList[MainWin->TabWidget->currentIndex()])->ImageProcessResult(&Canny);
        LOG(INFO) << "图像处理模块：Canny算子检测完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：Canny算子检测失败 异常：" << e.what();
    }
}


//Sobel算子
void MainController::actSobel_clicked()
{
    try {
        std::shared_ptr<Sobel> sob(new Sobel);
        TabImageMap.value(TabWidgetList[MainWin->TabWidget->currentIndex()])->ImageProcessResult(sob.get());
        LOG(INFO) << "图像处理模块：Sobel算子检测完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：Sobel算子检测失败 异常：" << e.what();
    }
}



//Scharr算子
void MainController::actScharr_clicked()
{
    try {
        Scharr Scharr;
        TabImageMap.value(TabWidgetList[MainWin->TabWidget->currentIndex()])->ImageProcessResult(&Scharr);
        LOG(INFO) << "图像处理模块：Scharr算子检测完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：Scharr算子检测失败 异常：" << e.what();
    }
}



//Laplacian算子
void MainController::actLaplacian_clicked()
{
    try {
        Laplacian filt;
        TabImageMap.value(TabWidgetList[MainWin->TabWidget->currentIndex()])->ImageProcessResult(&filt);
        LOG(INFO) << "图像处理模块：Laplacian算子检测完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：Laplacian算子检测失败 异常：" << e.what();
    }
}



//Roberts算子
void MainController::actRoberts_clicked()
{
    try {
        Roberts filt;
        TabImageMap.value(TabWidgetList[MainWin->TabWidget->currentIndex()])->ImageProcessResult(&filt);
        LOG(INFO) << "图像处理模块：Roberts算子检测完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：Roberts算子检测失败 异常：" << e.what();
    }
}




//SIFT
void MainController::actSIFT_clicked()
{
    try {
        SIFT filt;
        TabImageMap.value(TabWidgetList[MainWin->TabWidget->currentIndex()])->ImageProcessResult(&filt);
        LOG(INFO) << "图像处理模块：SIFT特征提取完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：SIFT特征提取失败 异常：" << e.what();
    }
}



//SURF
void MainController::actSURF_clicked()
{
    try {
        SURF filt;
        TabImageMap.value(TabWidgetList[MainWin->TabWidget->currentIndex()])->ImageProcessResult(&filt);
        LOG(INFO) << "图像处理模块：SURF特征提取完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：SURF特征提取失败 异常：" << e.what();
    }
}



//BRISK
void MainController::actBRISK_clicked()
{
    try {
        BRISK filt;
        TabImageMap.value(TabWidgetList[MainWin->TabWidget->currentIndex()])->ImageProcessResult(&filt);
        LOG(INFO) << "图像处理模块：BRISK特征提取完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：BRISK特征提取失败 异常：" << e.what();
    }
}


//AKAZE
void MainController::actAKAZE_clicked()
{
    try {
        AKAZE filt;
        TabImageMap.value(TabWidgetList[MainWin->TabWidget->currentIndex()])->ImageProcessResult(&filt);
        LOG(INFO) << "图像处理模块：AKAZE特征提取完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：AKAZE特征提取失败 异常：" << e.what();
    }
}



//亮度调节
void MainController::actBrightness_clicked()
{
    try {
        Bright bri;
        TabImageMap.value(TabWidgetList[MainWin->TabWidget->currentIndex()])->ImageProcessResult(&bri);
        LOG(INFO) << "图像处理模块：亮度调节完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：亮度调节失败 异常：" << e.what();
    }
}


//对比度调节
void MainController::actContrast_clicked()
{
    try {
        Contrast cts;
        TabImageMap.value(TabWidgetList[MainWin->TabWidget->currentIndex()])->ImageProcessResult(&cts);
        LOG(INFO) << "图像处理模块：对比度调节完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：对比度调节失败 异常：" << e.what();
    }
}


//饱和度调节
void MainController::actNTSC_clicked()
{
    try {
        NTSC ntsc;
        TabImageMap.value(TabWidgetList[MainWin->TabWidget->currentIndex()])->ImageProcessResult(&ntsc);
        LOG(INFO) << "图像处理模块：饱和度调节完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：饱和度调节失败 异常：" << e.what();
    }
}

//色温调节
void MainController::actCCT_clicked()
{
    try {
        CCT cct;
        TabImageMap.value(TabWidgetList[MainWin->TabWidget->currentIndex()])->ImageProcessResult(&cct);
        LOG(INFO) << "图像处理模块：色温调节完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：色温调节失败 异常：" << e.what();
    }
}


//色彩平衡调节
void MainController::actHLS_clicked()
{
    try {
        AKAZE filt;
        TabImageMap.value(TabWidgetList[MainWin->TabWidget->currentIndex()])->ImageProcessResult(&filt);
        LOG(INFO) << "图像处理模块：双边滤波完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：双边滤波失败 异常：" << e.what();
    }
}

//色阶调节
void MainController::actLevels_clicked()
{
    try {
        Levels lv;
        TabImageMap.value(TabWidgetList[MainWin->TabWidget->currentIndex()])->ImageProcessResult(&lv);
        LOG(INFO) << "图像处理模块：色阶调节完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：色阶调节失败 异常：" << e.what();
    }
}



//膨胀
void MainController::actDilation_clicked()
{    
    try {
        Expand epd;
        TabImageMap.value(TabWidgetList[MainWin->TabWidget->currentIndex()])->ImageProcessResult(&epd);
        LOG(INFO) << "图像处理模块：膨胀处理完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：膨胀处理失败 异常：" << e.what();
    }
}


//腐蚀
void MainController::actErosion_clicked()
{
    try {
        Corrosion crs;
        TabImageMap.value(TabWidgetList[MainWin->TabWidget->currentIndex()])->ImageProcessResult(&crs);
        LOG(INFO) << "图像处理模块：腐蚀处理完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：腐蚀处理失败 异常：" << e.what();
    }
}




//频谱图函数实现
void MainController::actImageFFT_clicked()
{
    AKAZE fft;
    TabImageMap.value(TabWidgetList[MainWin->TabWidget->currentIndex()])->ImageProcessResult(&fft);
}



//灰度直方图函数实现
void MainController::actImageHistogram_clicked()
{
    Histogram his;
    QVector<QVector<double>> qvec = TabImageMap.value(TabWidgetList[MainWin->TabWidget->currentIndex()])->StatisticsImage(&his);
    if (!qvec[0].empty()) {

        ChartWidget* chart = new ChartWidget(MainWin);

        // 设置坐标轴
        chart->SetXYName("灰度级", "像素数");

        //显示图片
        chart->Histogram(qvec[0], qvec[1]);

        MainWin->BottomNesting(chart, "直方图");

        LOG(INFO) << "图像处理模块：直方图绘制成功";
    }
}


//测试连接
void MainController::actTryRemotConnect_clicked()
{
    if (DataCommumication::Ping("192.168.1.2")) {
        LOG(INFO) << "数据连接模块：连接失败";
    }
    else {
        LOG(INFO) << "数据连接模块：连接成功";
    }
}



//模型训练
void MainController::actModelTraining_clicked()
{
    std::shared_ptr<RandomForest> test(mlManage::CreateRandomForest());
    QString str1 = "F:/桌面/G01523 东电抽蓄模型试验台/设计文件/空化照片/N";
    QString str2 = "F:/桌面/G01523 东电抽蓄模型试验台/设计文件/空化照片/Y";
    std::string path1= str1.toLocal8Bit().data();
    std::string path2 = str2.toLocal8Bit().data();
    test->SetOkPath(path1);
    test->SetNgPath(path2);
    test->ModelTrain();
}



//模型测试
void MainController::actModelTesting_clicked()
{

}



//模型保存
void MainController::actModelSave_clicked()
{

}



//帮助页面
void MainController::actHelp_clicked()
{
    DatCC->ReturnDataSting();
}



//关于页面
void MainController::actAboutUs_clicked()
{
    AboutMe am;
    am.exec();
}



//TAB页面改变伴随状态改变,观察者的一种变种
void MainController::TabCurrentChanged(int index)
{   
    if (index >= 0) {
        switch (TabWidgetList[index]->GetItemStyle())
        {
        case Tabwidget::CameraItem:
            ChangeCameraState(index);
            break;
        case Tabwidget::ImageItem:
            ChangeImageState(index);
            break;
        case Tabwidget::VideoItem:
            break;
        case Tabwidget::DataItem:
            ChangeDataState(index);
            break;
        case Tabwidget::MachineItem:
            break;
        default:
            break;
        }
    }
    //项目全关后禁用这些操作
    else {
        MainWin->DisableImage();
        MainWin->DisableIVision();
    }
}



//改变相机界面状态,这个方法说实话有点麻烦，应该有更好的办法，先这样有空在想
void MainController::ChangeCameraState(int idx)
{
    //判断相机加载状态
    if (TabCameraMap.contains(TabWidgetList[idx])) {
        std::shared_ptr <CameraImageManage> cim = TabCameraMap.value(TabWidgetList[idx]);
        MainWin->actNewLocalCamera->setEnabled(false);
        MainWin->actNewNetworkCamera->setEnabled(false);
        //获取连接状态
        bool cont = cim->GetCameraConnectState();
        MainWin->actConnect->setEnabled(!cont);
        MainWin->actDisConnect->setEnabled(cont);
        //获取采集状态
        bool bpst = cim->GetCameraGrapState();
        MainWin->actPlay->setEnabled(!bpst);
        MainWin->actPause->setEnabled(bpst);

        //获取录制状态
        bool sast = cim->GetSaveState();
        MainWin->actRecord->setChecked(sast);
        if(MainWin->actRecord->isChecked()) {
            MainWin->actRecord->setIcon(QIcon("./icon/停止录制视频.svg"));
        }
    else {
        MainWin->actRecord->setIcon(QIcon("./icon/开始录制视频.svg"));
    }
        MainWin->actRecord->setEnabled(true);


        //获取截图状态
        bool snst = cim->GetSnapState();
        MainWin->actSnap->setChecked(snst);
        MainWin->actSnap->setEnabled(true);

        //加载相机后就可以显示触发设置了
        MainWin->actTriggerSetting->setEnabled(true);
        MainWin->actSetwebcam->setEnabled(true);

        //设置标题状态
        bool sts = cim->GetSubTitleState();
        MainWin->actTitleStart->setEnabled(!sts);
        MainWin->actTitleStop->setEnabled(sts);

        //只要连接相机就可以加载模型
        MainWin->actLoadCavModel->setEnabled(true);


        //相机项目禁用所有图像处理业务
        MainWin->DisableImage();
    }
    else {
        MainWin->actNewLocalCamera->setEnabled(true);
        MainWin->actNewNetworkCamera->setEnabled(true);
        //相机项目禁用所有图像处理业务
        MainWin->DisableImage();
    }
}



//改变图像界面状态,这个方法说实话有点麻烦，应该有更好的办法，先这样有空在想
void MainController::ChangeImageState(int idx)
{
    MainWin->actImageRevocation->setEnabled(true);
    MainWin->actImageRework->setEnabled(true);
    MainWin->actImageSave->setEnabled(true);
    MainWin->actGrayImage->setEnabled(true);
    MainWin->actBinaryImage->setEnabled(true);
    MainWin->actImageBilateralFilter->setEnabled(true);
    MainWin->actImageFFT->setEnabled(true);
    MainWin->actImageHistogram->setEnabled(true);

    MainWin->galleryFileter->setEnabled(true);
    MainWin->galleryEdgeDetection->setEnabled(true);
    MainWin->galleryFeatureExtraction->setEnabled(true);

    MainWin->actBrightness->setEnabled(true);
    MainWin->actContrast->setEnabled(true);
    MainWin->actNTSC->setEnabled(true);
    MainWin->actCCT->setEnabled(true);
    MainWin->actHLS->setEnabled(true);
    MainWin->actLevels->setEnabled(true);
    MainWin->actDilation->setEnabled(true);
    MainWin->actErosion->setEnabled(true);

    MainWin->DisableIVision();
}



//改变数据状态,这个方法说实话有点麻烦，应该有更好的办法，先这样有空在想
void MainController::ChangeDataState(int idx)
{
    //先把其他项目类型禁用了
    MainWin->DisableIVision();
    MainWin->DisableImage();
}


