


#include "presenter.h"
#include <loghead.h>
#include <QSettings>
#include <QDir>
#include <QVector>
#include <opencv2/ml.hpp>
//#include <openvino/openvino.hpp>


Presenter::Presenter(QObject *parent)
	: QObject(parent)
{

}


Presenter::~Presenter()
{

}


//创建图像处理及相机类
void Presenter::CreateImageAgent(Tabwidget* tab)
{
	std::shared_ptr<ImageAgent> agent(new ImageAgent(tab));
	AgentList.append(agent);
}



//创建相机实例
void Presenter::CreateCamera(uint idex, mjis::ICamera::CameraType Type, int page)
{
	AgentList[page]->CreateCamera(idex, Type);
}


//释放图像处理及相机实例资源
void Presenter::CloseTab(int page)
{
	AgentList.removeAt(page);
}


//返回相机实例指针
mjis::ICamera* Presenter::ReturnCameraPoint(int page)
{
	if (page+1 >AgentList.size()) {
		return nullptr;
	}
	else {
		return AgentList[page]->ReturnCamera();
	}
}

//连接相机
void Presenter::Connect(int page)
{
	AgentList[page]->ConnectCamera();
	emit ChangeToolState();
}


//断开连接相机
void Presenter::DisConnect(int page)
{
	AgentList[page]->DisConnectCamera();
	emit ChangeToolState();
}


//返回相机连接状态
bool Presenter::ReturnCameraConnect(int page)
{
	return AgentList[page]->ReturnCameraConnect();
}



//开始采集
void Presenter::Start(int page)
{
	AgentList[page]->StartGrap();
	emit ChangeToolState();
}


//停止采集
void Presenter::Stop(int page)
{
	AgentList[page]->StopGrap();
	emit ChangeToolState();
}



//返回相机采集状态
bool Presenter::ReturnCameraGrap(int page)
{
	return AgentList[page]->ReturnCameraGrap();
}


//开始保存视频
void Presenter::StartSaveVideo(int page)
{
	try
	{
		QSettings settings("D:/ZImageSoft/CavitationAPP/Config/imagepath.cfg", QSettings::IniFormat);
		QString VideoPath = settings.value("videopath").toString() + "试验视频";
		std::string str = VideoPath.toLocal8Bit().toStdString();
		int type = settings.value("videostyle").toInt();
		AgentList[page]->StartSaveVideo(str, static_cast<mjlib::ImageSaveVideo::VideoStyle>(type), 640, 480);
		emit ChangeToolState();
	}
	catch (const std::exception& e)
	{
		
	}
}


//停止保存视频
void Presenter::StopSaveVideo(int page)
{
	try
	{
		AgentList[page]->StopSaveVideo();
		emit ChangeToolState();
	}
	catch (const std::exception&)
	{

	}
}


//返回保存视频状态
bool Presenter::ReturnSaveState(int page)
{
	return AgentList[page]->ReturnSaveState();	
}



//开始保存图像
void Presenter::StartSnapImage(int page)
{
	try
	{
		QString folderPath = "new_folder";
		QDir dir;
		bool result = dir.mkdir(folderPath);
		QSettings settings("D:/ZImageSoft/CavitationAPP/Config/imagepath.cfg", QSettings::IniFormat);
		QString VideoPath = settings.value("imagepath").toString();
		int type = settings.value("imagestyle").toInt();
		AgentList[page]->StartSnapVideo(VideoPath, static_cast<mjlib:: ImageSnapImage::ImageStyle > (type), 640, 480);
		emit ChangeToolState();
	}
	catch (const std::exception&)
	{

	}
}



//停止保存图像
void Presenter::StopSnapImage(int page)
{
	try
	{
		AgentList[page]->StopSnapVideo();
		emit ChangeToolState();
	}
	catch (const std::exception&)
	{

	}
}



//返回保存图片状态
bool Presenter::ReturnSnapState(int page)
{
	return AgentList[page]->ReturnSnapState();
}



//显示字幕
void Presenter::StartSub(int page, std::string* text, std::string* data)
{
	try
	{
		AgentList[page]->StartSubtitle(text, data);
		emit ChangeToolState();
	}
	catch (const std::exception&)
	{

	}
}



//清除字幕
void Presenter::StopSub(int page)
{
	try
	{
		AgentList[page]->StopSubtitle();
		emit ChangeToolState();
	}
	catch (const std::exception&)
	{

	}
}

//返回保存图片状态
bool Presenter::ReturnSubState(int page)
{
	return AgentList[page]->ReturnSnapState();
}




//应用字体设置
void Presenter::SetFont(int page, uint offsetx, uint offsety, uint cR, uint cG, uint cB, uint fontheight)
{
	try
	{
		AgentList[page]->SetFont(offsetx, offsety, cR, cG, cB, fontheight);
	}
	catch (const std::exception&)
	{

	}
}


//打开图片信号
void Presenter::OpenImage(const QString& path, int page)
{
	try
	{
		AgentList[page]->OpenImage(path);
	}
	catch (const std::exception&)
	{

	}
}



//图像处理
void Presenter::ProcessImage(mjlib::ImageProcess* process, int page)
{
	try
	{
		AgentList[page]->ProcessImage(process);
		delete process;
	}
	catch (const std::exception&)
	{

	}
}



//图像处理回退
void Presenter::PopProcess(int page)
{
	try
	{
		AgentList[page]->PopProcess();
	}
	catch (const std::exception&)
	{

	}
}



//图像处理取消回退
void Presenter::BackProcess(int page)
{
	try
	{
		AgentList[page]->BackProcess();
	}
	catch (const std::exception&)
	{

	}
}


//图像保存
void Presenter::SaveImage(int page)
{
	try
	{
	}
	catch (const std::exception&)
	{

	}
}



//绘制灰度直方图
void Presenter::DrawChart(ChartWidget* chart, int page)
{
	try
	{
		std::tuple<std::vector<double>, std::vector<double>> list=AgentList[page]->DrawHistogram();

		std::vector<double> x = std::get<0>(list);

		std::vector<double> y = std::get<1>(list);

		//显示图片
		chart->Histogram(QVector<double>(x.begin(), x.end()), QVector<double>(y.begin(), y.end()));

		emit DrawChartSuccess(chart,"灰度直方图");

	}
	catch (const std::exception&)
	{

	}
}




//加载模型
void Presenter::LoadModel()
{
	/*
	// 使用OpenCV加载SavedModel模型
	std::string path1 = "D:/Work/CNN_Model/frozen_graph.pb";
	auto model = cv::dnn::readNetFromTensorflow(path1);

	//model.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
	//model.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);

	QString path2 = "F:/桌面/G01523 东电抽蓄模型试验台/设计文件/空化照片/t/ed9ed77e22217e5a1c016d5bb20d4ee.jpg";
	cv::Mat img = cv::imread(path2.toLocal8Bit().toStdString());


	// 设置感兴趣区域（ROI）
	cv::Rect roi(900, 400, 1600, 1200);  // 在图像中定义矩形区域

	// 检查感兴趣区域是否超出图像范围	
	roi = roi & cv::Rect(0, 0, img.cols, img.rows);

	// 截取感兴趣区域图像
	cv::Mat croppedImage = img(roi);

	cv::imshow("1231", croppedImage);
	cv::waitKey(0);

	cv::Mat blob = cv::dnn::blobFromImage(img, 1./255, cv::Size(700, 800));

	auto names = model.getLayerNames();
	auto num=model.getUnconnectedOutLayers();

	model.setInput(blob);

	std::cout << img.size << std::endl;

	cv::Mat out;
	model.enableWinograd(false);
	out=model.forward();	

	// 获取正类和负类的概率
	float prob_0 = out.at<float>(0, 0);
	float prob_1 = out.at<float>(0, 1);

	std::cout << out << std::endl;

	

	auto a = ov::get_openvino_version();

	ov::Core core;


	std::string path1 = "D:/Work/CNN_Model/frozen_graph.pb";
	ov::CompiledModel compiled_model = core.compile_model("D:/Work/CNN_Model/frozen_graph.xml", "AUTO");


	ov::InferRequest infer_request = compiled_model.create_infer_request();

	// Get input port for model with one input
	auto input_port = compiled_model.input();
	// Create tensor from external memory
	//ov::Tensor input_tensor(input_port.get_element_type(), input_port.get_shape(), memory_ptr);
	// Set input tensor for model with one input
	//infer_request.set_input_tensor(input_tensor);

	//infer_request.start_async();
	//infer_request.wait();

	*/

}

	

