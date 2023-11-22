#pragma once
 
#include <QtCore/QtGlobal>

#if defined(ImageProcessLib)
#  define ImageMainContoller_EXPORT Q_DECL_EXPORT
#else
#  define ImageMainContoller_EXPORT Q_DECL_IMPORT
#endif

#include <QObject>
#include <QThread>
#include <ImageProcessManage.h>		
#include <dockvideo.h>
#include <mvcamera.h>
#include <localcamera.h>


struct ImageMainContoller_EXPORT ImageGroup {
	ICamera* Camera;

	ImageProcessManage* ImageProcess;

	QThread* CameraThread;
};		


class  ImageMainContoller_EXPORT ImageMainContoller  : public QObject
{
	Q_OBJECT

public:
	ImageMainContoller(QObject* parent = nullptr);
	~ImageMainContoller();

	//链表，用于设置相机线程
	QList<MyDockWidget*> VideoList;

	//链表，用于设置相机线程
	QList<ImageGroup*> ImageGroupList;

	//链表，用于设置相机线程
	QList<QThread*> CameraThread;

	//UI界面哈希表
	QHash<MyDockWidget*, ImageGroup*> VideoMap;

	//创建相机
	MyDockWidget* CreateStructure(uint idex, CameraType Type);

	//创建图片
	MyDockWidget* OpenImage(std::string stdFilePath);

	//释放界面资源
	void ReleaseResource(MyDockWidget*);

	//相机开始采集
	void StartGrap(MyDockWidget* Video);
	
	//相机停止采集
	void StopGrap(MyDockWidget* Video);

	//连接相机
	void ConnectCamera(MyDockWidget* Video);

	//关闭相机连接
	void DisConnectCamera(MyDockWidget* Video);

	//相机是否在运行
	bool CameraisRunning(MyDockWidget* Video);

	//开始保存视频
	void StartSaveVideo(MyDockWidget* Video, std::string Path, VideoStyle Vdostyle, uint fps, int frame_width, int  frame_height);

	//停止保存视频
	void StopSaveVideo(MyDockWidget* Video);

	//开始快照
	void StartSnapVideo( MyDockWidget* Video, std::string Path, ImageStyle Imgstyle, int frame_width, int  frame_height);

	//停止快照
	void StopSnapVideo(MyDockWidget* Video);

	//显示字幕
	void StartSubTitle(MyDockWidget* Video);

	//设置字体格式
	void SetFontParam(MyDockWidget* Video, uint offsetx, uint offsety, uint cR, uint cG, uint cB, uint fontheight);

	//设置字幕文字
	void SetSubTitle(MyDockWidget* Video,std::string title);

	//停止字幕显示
	void StopSubTitle(MyDockWidget* Video);



private:
	ImageSaveVideo* savevideo;

	ImageSnapImage* sanpimage;

	static ICamera* createCamera(const CameraType cameraType);

	bool TryConnectCamera(ICamera* Cmaera);
	


private slots:

};
