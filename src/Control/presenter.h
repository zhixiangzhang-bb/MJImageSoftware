#pragma once

#include <QInputDialog>
#include <QApplication>
#include "chartwidget.h"
#include "mjis_agent_api.h"


class Presenter  : public QObject
{
	Q_OBJECT

public:
	Presenter(QObject *parent = nullptr);

	~Presenter();

	//创建图像处理及相机类
	void CreateImageAgent(Tabwidget* tab);

	//创建相机实例
	void CreateCamera(uint idex, mjis::ICamera::CameraType Type, int page);

	//释放图像处理及相机实例资源
	void CloseTab(int page);

	//返回相机实例指针
	mjis::ICamera* ReturnCameraPoint(int page);

	//连接相机
	void Connect(int page);
	
	//断开连接相机
	void DisConnect(int page);

	//返回相机连接状态
	bool ReturnCameraConnect(int page);

	//开始采集
	void Start(int page);

	//停止采集
	void Stop(int page);

	//返回相机采集状态
	bool ReturnCameraGrap(int page);

	//开始保存视频
	void StartSaveVideo(int page);

	//停止保存视频
	void StopSaveVideo(int page);

	//返回保存视频状态
	bool ReturnSaveState(int page);

	//开始保存图像
	void StartSnapImage(int page);

	//停止保存图像
	void StopSnapImage(int page);

	//返回保存图片状态
	bool ReturnSnapState(int page);

	//显示字幕
	void StartSub(int page, std::string* text, std::string* data);

	//清除字幕
	void StopSub(int page);

	//返回保存图片状态
	bool ReturnSubState(int page);

	//应用字体设置
	void SetFont(int page,uint offsetx, uint offsety, uint cR, uint cG, uint cB, uint fontheight);

	//打开图片信号
	void OpenImage(const QString& path,int page);

	//图像处理
	void ProcessImage(mjlib::ImageProcess* process, int page);

	//图像处理回退
	void PopProcess(int page);

	//图像处理取消回退
	void BackProcess(int page);

	//图像保存
	void SaveImage(int page);

	//绘制灰度直方图
	void DrawChart(ChartWidget* chart, int page);

	void LoadModel();

private:
	//图像处理列表
	QVector<std::shared_ptr<ImageAgent>> AgentList;


signals:
	//改变状态栏状态
	void ChangeToolState();

	//灰度直方图绘制完成
	void DrawChartSuccess(ChartWidget* chart,const QString& name);
};
