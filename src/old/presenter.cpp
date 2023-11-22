
#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>

#ifndef GLOG_NO_ABBREVIATED_SEVERITIES
# ifdef ERROR
#  undef ERROR
# endif
const int INFO = GLOG_INFO, WARNING = GLOG_WARNING,
ERROR = GLOG_ERROR, FATAL = GLOG_FATAL;
#endif

#include "presenter.h"
#include <QInputDialog>



Presenter::Presenter(QObject *parent)
	: QObject(parent)
{

}

Presenter::~Presenter()
{

}




//返回选择的相机信息，并且初始化相机
void Presenter::SelcetNetcamId(uint idex, CameraType Type)
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    int num = ui->videotab->currentIndex();
    MyDockWidget* dock;
    if (num == -1) {
        QMessageBox::warning(this, "警告", "没有创建项目，请确认后在添加");
    }
    else {
        //查询表里有没有键
        if (TabCameraMap.contains(TabWidgetList[num])) {
            dock = TabCameraMap.value(TabWidgetList[num])->CreateCamera(idex, Type);
        }
        else {
            QString str;
            str.append(ui->ExperimentString->text() + "\n");
            str.append(ui->plainTextEdit->toPlainText());
            *subtitle = str.toStdString();
            std::shared_ptr <CameraImageManage> cim(new CameraImageManage);
            dock = cim->CreateCamera(idex, Type);
            cim->SetSubTitle(this->subtitle, DatCC->ReturnDataSting());
            TabCameraMap.insert(TabWidgetList[num], cim);
        }
        TabWidgetList[num]->layout()->addWidget(dock);
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
void Presenter::TabClose(int index)
{
    int ret = QMessageBox::question(this, "提示", "是否关闭本窗口", QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes)
    {
        std::shared_ptr<Tabwidget> tab = TabWidgetList[index];
        //如果是相机项目释放相机资源
        if (TabCameraMap.contains(tab)) {
            TabCameraMap.remove(tab);
        }

        //如果是图片处理释放图片资源
        if (TabImageMap.contains(tab)) {
            TabImageMap.remove(tab);
        }

        TabWidgetList.removeAt(index);
        ui->videotab->removeTab(index);
        LOG(INFO) << "已关闭页面" << std::to_string(index);
    }
}



//相机连接
void Presenter::actConnect_clicked()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    std::shared_ptr<CameraImageManage> cim = TabCameraMap.value(TabWidgetList[ui->videotab->currentIndex()]);
    cim->ConnectCamera(0);
    LOG(INFO) << "用户事件: 已连接相机" + std::to_string(cim->GetCameraId());
    this->actConnect->setEnabled(false);
    this->actDisConnect->setEnabled(true);
    this->actPlay->setEnabled(true);
    QApplication::restoreOverrideCursor();
}


//断开相机连接
void Presenter::actDisConnect_clicked()
{

    QApplication::setOverrideCursor(Qt::WaitCursor);
    std::shared_ptr<CameraImageManage> cim = TabCameraMap.value(TabWidgetList[ui->videotab->currentIndex()]);
    cim->DisConnectCamera(0);
    this->actConnect->setEnabled(true);
    this->actDisConnect->setEnabled(false);
    this->actPlay->setEnabled(false);
    this->actPause->setEnabled(false);
    LOG(INFO) << "用户事件: 已连接相机" + std::to_string(cim->GetCameraId());
    QApplication::restoreOverrideCursor();
}



//采集按钮点击事件函数
void Presenter::actPlay_clicked()
{
    try {
        TabCameraMap.value(TabWidgetList[ui->videotab->currentIndex()])->StartGrap(0);
        this->actPlay->setEnabled(false);
        this->actPause->setEnabled(true);
        this->actRecord->setEnabled(true);
        this->actSnap->setEnabled(true);
        this->actTitleStart->setEnabled(true);
        LOG(INFO) << "相机模块：开始采集成功";
    }
    catch (const std::exception& e) {
        this->actPlay->setEnabled(false);
        this->actPause->setEnabled(false);
        this->actRecord->setEnabled(false);
        this->actSnap->setEnabled(false);
        LOG(ERROR) << "相机模块：开始采集失败 异常：" << e.what();
    }
}




//停止采集按钮点击事件
void Presenter::actPause_clicked()
{
    try {
        TabCameraMap.value(TabWidgetList[ui->videotab->currentIndex()])->StopGrap(0);
        this->actPlay->setEnabled(true);
        this->actPause->setEnabled(false);
        this->actRecord->setEnabled(false);
        this->actSnap->setEnabled(false);
        LOG(INFO) << "相机模块：停止采集成功";
    }
    catch (const std::exception& e) {
        this->actPlay->setEnabled(false);
        this->actPause->setEnabled(false);
        this->actRecord->setEnabled(false);
        this->actSnap->setEnabled(false);
        LOG(ERROR) << "相机模块：停止采集失败 异常：" << e.what();
    }
}



//录制按钮点击事件函数
void Presenter::actRecord_clicked()
{
    //先读取配置文件参数
    QSettings settings("E:/ZImageSoft/CavitationAPP/Config/imagepath.cfg", QSettings::IniFormat);
    QString VideoPath = settings.value("videopath").toString() + "test";

    //将字符串转成std
    VideoSavePath = VideoPath.toLocal8Bit().data();

    //根据状态判断录制状态
    if (this->actRecord->isChecked()) {
        TabCameraMap.value(TabWidgetList[ui->videotab->currentIndex()])->StartSaveVideo(VideoSavePath, ImageSaveVideo::MJPG, 30, 640, 480);
        this->actRecord->setChecked(true);
        this->actRecord->setIcon(QIcon("./icon/停止录制视频.svg"));
    }
    else {
        TabCameraMap.value(TabWidgetList[ui->videotab->currentIndex()])->StopSaveVideo(0);
        this->actRecord->setChecked(false);
        this->actRecord->setIcon(QIcon("./icon/开始录制视频.svg"));
    }
}


//快照按钮点击事件函数
void Presenter::actSnap_clicked()
{
    if (this->actSnap->isChecked()) {
        QString pathstr = "E:/ZImageSoft/CavitationAPP/Test/" + QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
        QDir().mkpath(pathstr);
        pathstr = pathstr + "/测试数据";
        ImageSavePath = pathstr.toLocal8Bit().data();
        //ImageSavePath = pathstr.toStdString();
        TabCameraMap.value(TabWidgetList[ui->videotab->currentIndex()])->StartSnapVideo(ImageSavePath, ImageSnapImage::PNG, 640, 480);
        this->actSnap->setChecked(true);
        this->actSnap->setIcon(QIcon("./icon/停止连续采集.svg"));
    }
    else
    {
        TabCameraMap.value(TabWidgetList[ui->videotab->currentIndex()])->StopSnapVideo();
        this->actSnap->setChecked(false);
        this->actSnap->setIcon(QIcon("./icon/连续采集.svg"));
    }
}



//字幕显示按钮
void Presenter::actTitleStart_clicked()
{
    TabCameraMap.value(TabWidgetList[ui->videotab->currentIndex()])->StartSubTitle();
    this->actTitleStart->setEnabled(false);
    this->actTitleStop->setEnabled(true);
}



//字幕停止按钮
void Presenter::actTitleStop_clicked()
{
    TabCameraMap.value(TabWidgetList[ui->videotab->currentIndex()])->StopSubTitle();
    this->actTitleStart->setEnabled(true);
    this->actTitleStop->setEnabled(false);
}



//自定义文本值改变响应
void Presenter::on_plainTextEdit_textChanged()
{
    QString str;
    str.append(ui->ExperimentString->text() + "\n");
    str.append(ui->plainTextEdit->toPlainText());
    *subtitle = str.toStdString();
}





//路径设置按钮点击事件函数
void Presenter::actImagePath_clicked()
{
    VideoPathSet videoset;
    videoset.setWindowTitle(QStringLiteral("图像文件设置"));
    videoset.setWindowIcon(this->windowIcon());
    videoset.exec();
}


//相机属性页面
void Presenter::actSetwebcam_clicked()
{
    TabCameraMap.value(TabWidgetList[ui->videotab->currentIndex()])->OpenCameraSetSheet();
}




//图像处理回退
void Presenter::actImageRevocation_clicked()
{
    try {
        TabImageMap.value(TabWidgetList[ui->videotab->currentIndex()])->PopProcess();
        LOG(INFO) << "图像处理模块：撤回完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：撤回失败 异常：" << e.what();
    }
}




//图像重做函数
void Presenter::actImageRework_clicked()
{

}



//保存处理后的图片
void Presenter::actImageSaveclicked()
{
    QString path = QFileDialog::getSaveFileName(nullptr, "选择文件", "", "JPEG Files (*.jpg *.jpeg);;PNG Files (*.png);;BMP Files (*.bmp)");
    if (!path.isEmpty()) {
        std::string str = path.toLocal8Bit().data();
        TabImageMap.value(TabWidgetList[ui->videotab->currentIndex()])->SaveImage(str);
    }
}



//灰度化函数实现
void Presenter::actGrayImage_clicked()
{
    try {
        std::shared_ptr<ImageGray> gray(new ImageGray);
        TabImageMap.value(TabWidgetList[ui->videotab->currentIndex()])->ImageProcessResult(gray.get());
        LOG(INFO) << "图像处理模块：灰度化完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：灰度化失败 异常：" << e.what();
    }
}


//二值化函数实现
void Presenter::actBinaryImage_clicked()
{

    try {
        ImageBinaryzation* process = ImageLibConnect::CreateBinary(true);
        if (process != nullptr) {
            std::shared_ptr<ImageBinaryzation> binary(process);
            TabImageMap.value(TabWidgetList[ui->videotab->currentIndex()])->ImageProcessResult(binary.get());
            LOG(INFO) << "图像处理模块：二值化完成";
        }
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：二值化失败 异常：" << e.what();
    }
}



//均值滤波
void Presenter::actImageMeanFilter_clicked()
{
    try {
        ImageMeanFilter* process = ImageLibConnect::CreateMean(true);
        if (process != nullptr) {
            std::shared_ptr<ImageMeanFilter> Mean(process);
            TabImageMap.value(TabWidgetList[ui->videotab->currentIndex()])->ImageProcessResult(Mean.get());
            LOG(INFO) << "图像处理模块：均值模糊完成";
        }
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：均值模糊失败 异常：" << e.what();
    }

}


//高斯滤波
void Presenter::actImageGaussianFilter_clicked()
{
    try {
        ImageGaussianFilter* process = ImageLibConnect::CreateGaussian(true);
        if (process != nullptr) {
            std::shared_ptr<ImageGaussianFilter> Gaussian(process);
            TabImageMap.value(TabWidgetList[ui->videotab->currentIndex()])->ImageProcessResult(Gaussian.get());
            LOG(INFO) << "图像处理模块：高斯滤波完成";
        }
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：高斯滤波失败 异常：" << e.what();
    }
}



//中值滤波
void Presenter::actImageMedianFilter_clicked()
{

    try {
        ImageMedianFilter* process = ImageLibConnect::CreateMedian(true);
        if (process != nullptr) {
            std::shared_ptr<ImageMedianFilter> Median(process);
            TabImageMap.value(TabWidgetList[ui->videotab->currentIndex()])->ImageProcessResult(Median.get());
            LOG(INFO) << "图像处理模块：中值滤波完成";
        }
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：中值滤波失败 异常：" << e.what();
    }
}




//双边滤波
void Presenter::actImageBilateralFilter_clicked()
{
    try {
        ImageBilateralFilter* process = ImageLibConnect::CreateBilateral(true);
        if (process != nullptr) {
            std::shared_ptr<ImageBilateralFilter> Bilateral(new ImageBilateralFilter);
            TabImageMap.value(TabWidgetList[ui->videotab->currentIndex()])->ImageProcessResult(Bilateral.get());
            LOG(INFO) << "图像处理模块：双边滤波完成";
        }
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：双边滤波失败 异常：" << e.what();
    }
}


//Canny算子
void Presenter::actCanny_clicked()
{
    try {
        Canny Canny;
        TabImageMap.value(TabWidgetList[ui->videotab->currentIndex()])->ImageProcessResult(&Canny);
        LOG(INFO) << "图像处理模块：Canny算子检测完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：Canny算子检测失败 异常：" << e.what();
    }
}


//Sobel算子
void Presenter::actSobel_clicked()
{
    try {
        std::shared_ptr<Sobel> sob(new Sobel);
        TabImageMap.value(TabWidgetList[ui->videotab->currentIndex()])->ImageProcessResult(sob.get());
        LOG(INFO) << "图像处理模块：Sobel算子检测完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：Sobel算子检测失败 异常：" << e.what();
    }
}



//Scharr算子
void Presenter::actScharr_clicked()
{
    try {
        Scharr Scharr;
        TabImageMap.value(TabWidgetList[ui->videotab->currentIndex()])->ImageProcessResult(&Scharr);
        LOG(INFO) << "图像处理模块：Scharr算子检测完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：Scharr算子检测失败 异常：" << e.what();
    }
}



//Laplacian算子
void Presenter::actLaplacian_clicked()
{
    try {
        Laplacian filt;
        TabImageMap.value(TabWidgetList[ui->videotab->currentIndex()])->ImageProcessResult(&filt);
        LOG(INFO) << "图像处理模块：Laplacian算子检测完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：Laplacian算子检测失败 异常：" << e.what();
    }
}



//Roberts算子
void Presenter::actRoberts_clicked()
{
    try {
        Roberts filt;
        TabImageMap.value(TabWidgetList[ui->videotab->currentIndex()])->ImageProcessResult(&filt);
        LOG(INFO) << "图像处理模块：Roberts算子检测完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：Roberts算子检测失败 异常：" << e.what();
    }
}




//SIFT
void Presenter::actSIFT_clicked()
{
    try {
        SIFT filt;
        TabImageMap.value(TabWidgetList[ui->videotab->currentIndex()])->ImageProcessResult(&filt);
        LOG(INFO) << "图像处理模块：SIFT特征提取完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：SIFT特征提取失败 异常：" << e.what();
    }
}



//SURF
void Presenter::actSURF_clicked()
{
    try {
        SURF filt;
        TabImageMap.value(TabWidgetList[ui->videotab->currentIndex()])->ImageProcessResult(&filt);
        LOG(INFO) << "图像处理模块：SURF特征提取完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：SURF特征提取失败 异常：" << e.what();
    }
}



//BRISK
void Presenter::actBRISK_clicked()
{
    try {
        BRISK filt;
        TabImageMap.value(TabWidgetList[ui->videotab->currentIndex()])->ImageProcessResult(&filt);
        LOG(INFO) << "图像处理模块：BRISK特征提取完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：BRISK特征提取失败 异常：" << e.what();
    }
}


//AKAZE
void Presenter::actAKAZE_clicked()
{
    try {
        AKAZE filt;
        TabImageMap.value(TabWidgetList[ui->videotab->currentIndex()])->ImageProcessResult(&filt);
        LOG(INFO) << "图像处理模块：AKAZE特征提取完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：AKAZE特征提取失败 异常：" << e.what();
    }
}



//亮度调节
void Presenter::actBrightness_clicked()
{
    try {
        Bright bri;
        TabImageMap.value(TabWidgetList[ui->videotab->currentIndex()])->ImageProcessResult(&bri);
        LOG(INFO) << "图像处理模块：亮度调节完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：亮度调节失败 异常：" << e.what();
    }
}


//对比度调节
void Presenter::actContrast_clicked()
{
    try {
        Contrast cts;
        TabImageMap.value(TabWidgetList[ui->videotab->currentIndex()])->ImageProcessResult(&cts);
        LOG(INFO) << "图像处理模块：对比度调节完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：对比度调节失败 异常：" << e.what();
    }
}


//饱和度调节
void Presenter::actNTSC_clicked()
{
    try {
        NTSC ntsc;
        TabImageMap.value(TabWidgetList[ui->videotab->currentIndex()])->ImageProcessResult(&ntsc);
        LOG(INFO) << "图像处理模块：饱和度调节完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：饱和度调节失败 异常：" << e.what();
    }
}

//色温调节
void Presenter::actCCT_clicked()
{
    try {
        CCT cct;
        TabImageMap.value(TabWidgetList[ui->videotab->currentIndex()])->ImageProcessResult(&cct);
        LOG(INFO) << "图像处理模块：色温调节完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：色温调节失败 异常：" << e.what();
    }
}


//色彩平衡调节
void Presenter::actHLS_clicked()
{
    try {
        AKAZE filt;
        TabImageMap.value(TabWidgetList[ui->videotab->currentIndex()])->ImageProcessResult(&filt);
        LOG(INFO) << "图像处理模块：双边滤波完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：双边滤波失败 异常：" << e.what();
    }
}

//色阶调节
void Presenter::actLevels_clicked()
{
    try {
        Levels lv;
        TabImageMap.value(TabWidgetList[ui->videotab->currentIndex()])->ImageProcessResult(&lv);
        LOG(INFO) << "图像处理模块：色阶调节完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：色阶调节失败 异常：" << e.what();
    }
}



//膨胀
void Presenter::actDilation_clicked()
{
    try {
        Expand epd;
        TabImageMap.value(TabWidgetList[ui->videotab->currentIndex()])->ImageProcessResult(&epd);
        LOG(INFO) << "图像处理模块：膨胀处理完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：膨胀处理失败 异常：" << e.what();
    }
}


//腐蚀
void Presenter::actErosion_clicked()
{
    try {
        Corrosion crs;
        TabImageMap.value(TabWidgetList[ui->videotab->currentIndex()])->ImageProcessResult(&crs);
        LOG(INFO) << "图像处理模块：腐蚀处理完成";
    }
    catch (const std::exception& e) {
        LOG(ERROR) << "图像处理模块：腐蚀处理失败 异常：" << e.what();
    }
}




//频谱图函数实现
void Presenter::actImageFFT_clicked()
{
    AKAZE fft;
    TabImageMap.value(TabWidgetList[ui->videotab->currentIndex()])->ImageProcessResult(&fft);
}



//灰度直方图函数实现
void Presenter::actImageHistogram_clicked()
{
    Histogram his;
    QVector<QVector<double>> qvec = TabImageMap.value(TabWidgetList[ui->videotab->currentIndex()])->StatisticsImage(&his);
    if (!qvec[0].empty()) {

        ChartWidget* chart = new ChartWidget(this);

        // 设置坐标轴
        chart->SetXYName("灰度级", "像素数");

        //显示图片
        chart->Histogram(qvec[0], qvec[1]);

        this->BottomNesting(chart, "直方图");

        LOG(INFO) << "图像处理模块：直方图绘制成功";
    }
}


//测试连接
void Presenter::actTryRemotConnect_clicked()
{
    if (DataCommumication::Ping("192.168.1.2")) {
        LOG(INFO) << "数据连接模块：连接失败";
    }
    else {
        LOG(INFO) << "数据连接模块：连接成功";
    }
}


//模型训练
void Presenter::actModelTraining_clicked()
{

}



//模型测试
void Presenter::actModelTesting_clicked()
{

}


//模型保存
void Presenter::actModelSave_clicked()
{

}

//导入OK文件夹
void Presenter::actLoadOk_clicked()
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
void Presenter::actLoadNo_clicked()
{

}

//随机森林框架
void Presenter::actRandomForest_clicked()
{

}

//SVM框架
void Presenter::actSVM_clicked()
{

}


//KNN框架
void Presenter::actKNN_clicked()
{

}


//帮助页面
void Presenter::actHelp_clicked()
{
    DatCC->ReturnDataSting();
}



//关于页面
void Presenter::actAboutUs_clicked()
{
    AboutMe am;
    am.exec();
}


