#pragma once


/*****************************************************************
* 类名称：相机和图像总管理类
* 功能描述：做为总的接口,响应代理的命令
* 作者：zzx
* 创建日期：2023.6.25
* 最后修改：zzx
* 最后修改日期：
* 备注：做为相机监控总的接口，与代理配合
******************************************************************/



#include <QObject>
#include "dockvideo.h"
#include "imagefileio.h"
#include <QMutex>


#if defined(zzxlib_ImageProcess)
#  define CameraImageManage_EXPORT Q_DECL_EXPORT
#else
#  define CameraImageManage_EXPORT Q_DECL_IMPORT
#endif


class   CameraImageManage_EXPORT CameraImageManage  : public QObject
{
	Q_OBJECT

public:
	CameraImageManage(QObject* parent = nullptr);

	//析构函数释放所有资源
	~CameraImageManage();

	//创建相机项目
	MyDockWidget* CreateCamera(uint idex, ICamera::CameraType Type);

	//相机开始采集
	void StartGrap(int idx=-1);

	//相机停止采集
	void StopGrap(int idx=-1);

	//连接相机
	void ConnectCamera(int idx=-1);

	//关闭相机连接
	void DisConnectCamera(int idx=-1);

	//开始保存视频
	void StartSaveVideo(std::string& Path, ImageSaveVideo::VideoStyle Vdostyle, uint fps, int frame_width, int  frame_height, int idx = -1);

	//停止保存视频
	void StopSaveVideo(int idx=-1);

	//开始快照
	void StartSnapVideo(std::string& Path, ImageSnapImage::ImageStyle Imgstyle, int frame_width, int  frame_height, int idx = -1);

	//停止快照
	void StopSnapVideo(int idx=-1);

	//显示字幕
	void StartSubTitle(int idx=-1);

	//设置字体格式
	void SetFontParam(uint offsetx, uint offsety, uint cR, uint cG, uint cB, uint fontheight, int idx=-1);

	//设置字幕文字
	void SetSubTitle(std::string* title, std::string* data,int idx=-1);

	//停止字幕显示
	void StopSubTitle(int idx=-1);

	//打开相机属性页面
	void OpenCameraSetSheet(int idx=-1);

	//获取相机ID
	int GetCameraId(int idx = -1);

	//判断是否已经添加相机了，1启动，0停止
	bool GetCameraIdxState();

	//判断相机是否还在连接，1启动，0停止
	bool GetCameraConnectState();

	//判断相机是否在采集，1启动，0停止
	bool GetCameraGrapState();

	//判断是否在录制,1为在录制，0停止
	bool GetSaveState();

	//判断是否在截图，1启动，0停止
	bool GetSnapState();

	//判断是否在截图，1启动，0停止
	bool GetSubTitleState();

	//读取图像进图像处理环境
	void ReadQImage(cv::Mat& image);

	//图像处理接口进队列里
	void PushImageProcess(ImageProcess* process);

	//图像处理接口出队列
	void BackImageProcess(ImageProcess* process);

	//文件I/O进队列
	void PushImageFile(ImageProcess* process);

	//文件I/O出队列
	void BackImageFile(ImageProcess* process);

	//获取相机字幕状态
	bool TitleCuValue();

private:
	QMutex mutex;

	//相机
	std::shared_ptr<ICamera> Camera;

	//图像显示窗口
	std::shared_ptr<MyDockWidget> DockWidget;

	//视频保存智能指针不用自己释放内存
	std::shared_ptr<ImageSaveVideo> SavetVideo;

	//图片保存智能指针不用自己释放内存
	std::shared_ptr<ImageSnapImage> SavetImage;

	//字幕类，本身也是重写图像处理基类，目前先交作业,应该还有优化空间
	std::shared_ptr<ImageSubTitle> subtitle;

	//图片路径
	std::string ImagePath;

	//视频路径
	std::string VideoPath;

	//执行图像处理流程
	void ImageProcessExecute(cv::Mat& image);

	//执行文件I/O流程
	void ImageFileExecute(cv::Mat& image);

	//执行字幕叠加流程
	void ImageSubTitleExecute(cv::Mat& image);

	//转成QT能识别的图像类型
	QImage MatImageToQt(cv::Mat src);

	//图像处理队列
	QVector<ImageProcess*> ProcessQueue;

	//文件队列
	QVector<ImageProcess*> FileQueue;

	//字幕控制状态
	bool titlecu;

	//录制状态
	bool savestate;

	//截图状态
	bool snapstate;


signals:
	void ReturnProcessImage(QImage& image);
};
