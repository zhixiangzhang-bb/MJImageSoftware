﻿#pragma once

#include "mjis_core_global.h"
#include "mjis_hmi_api.h"
#include <QStack>


namespace mjis {


	class MJIS_Core_API ImageAgent : public QObject
	{
		Q_OBJECT

	public:
		ImageAgent(QObject* parent = nullptr);

		ImageAgent(hmi::Tabwidget* tab);

		~ImageAgent();

		//根据返回的ID创建窗口
		void CreateCamera(uint idex, camera::ICamera::CameraType Type);

		//返回相机指针
		camera::ICamera* ReturnCamera();

		//相机连接
		void ConnectCamera();

		//断开连接
		void DisConnectCamera();

		//返回相机连接状态
		bool ReturnCameraConnect();

		//连接相机
		void StartGrap();

		//停止采集
		void StopGrap();

		//返回相机采集状态
		bool ReturnCameraGrap();

		//开始保存视频
		void StartSaveVideo(const std::string& Path, mjlib::ImageSaveVideo::VideoStyle Vdostyle, int frame_width, int  frame_height);

		//停止保存视频
		void StopSaveVideo();

		//返回保存视频状态
		bool ReturnSaveState();

		//开始保存图像
		void StartSnapVideo(const QString& Path, mjlib::ImageSnapImage::ImageStyle Imgstyle, int frame_width, int  frame_height);

		//停止保存图像
		void StopSnapVideo();

		//返回保存图片状态
		bool ReturnSnapState();

		//开始显示字幕
		void StartSubtitle(std::string* title, std::string* data);

		//停止显示字幕
		void StopSubtitle();

		//返回字幕显示状态
		bool ReturnSubState();

		//应用字体设置
		void SetFont(uint offsetx, uint offsety, uint cR, uint cG, uint cB, uint fontheight);

		//打开图片信号
		void OpenImage(const QString& path);

		//图像处理
		void ProcessImage(mjlib::ImageProcess* process);

		//图像处理回退
		void PopProcess();

		//图像处理取消回退
		void BackProcess();

		//绘制灰度直方图
		std::tuple<std::vector<double>, std::vector<double>> DrawHistogram();

	private:
		//转成QT图片
		QImage MatImageToQt(cv::Mat& src);

		//显示界面指针
		hmi::Tabwidget* tab;

		//相机实例
		std::shared_ptr<camera::ICamera> Camera;

		//保存视频实例
		std::shared_ptr<mjlib::ImageSaveVideo> save;

		//采集图像实例
		std::shared_ptr<mjlib::ImageSnapImage> snap;

		//显示字幕
		std::shared_ptr<mjlib::ImageSubTitle> subtitle;

		//字幕显示状态
		bool titlestate;

		//相机处理流程
		QVector<std::shared_ptr<mjlib::ImageProcess>> ProcessList;

		//图像处理前进栈
		QStack<cv::Mat> ProcessAdvanceStack;

		//图像处理类型前进栈
		QStack<int> ProcessNameAdvanceStack;

		//图像处理回退栈
		QStack<cv::Mat> ProcessBackStack;

		//读取图片
		void ReadQImage(cv::Mat image);


	signals:
		//相机读取图片完成
		void UpdateImage(const QImage& image);


	};


}