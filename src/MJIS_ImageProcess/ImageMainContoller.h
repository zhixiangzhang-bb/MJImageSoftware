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

	//����������������߳�
	QList<MyDockWidget*> VideoList;

	//����������������߳�
	QList<ImageGroup*> ImageGroupList;

	//����������������߳�
	QList<QThread*> CameraThread;

	//UI�����ϣ��
	QHash<MyDockWidget*, ImageGroup*> VideoMap;

	//�������
	MyDockWidget* CreateStructure(uint idex, CameraType Type);

	//����ͼƬ
	MyDockWidget* OpenImage(std::string stdFilePath);

	//�ͷŽ�����Դ
	void ReleaseResource(MyDockWidget*);

	//�����ʼ�ɼ�
	void StartGrap(MyDockWidget* Video);
	
	//���ֹͣ�ɼ�
	void StopGrap(MyDockWidget* Video);

	//�������
	void ConnectCamera(MyDockWidget* Video);

	//�ر��������
	void DisConnectCamera(MyDockWidget* Video);

	//����Ƿ�������
	bool CameraisRunning(MyDockWidget* Video);

	//��ʼ������Ƶ
	void StartSaveVideo(MyDockWidget* Video, std::string Path, VideoStyle Vdostyle, uint fps, int frame_width, int  frame_height);

	//ֹͣ������Ƶ
	void StopSaveVideo(MyDockWidget* Video);

	//��ʼ����
	void StartSnapVideo( MyDockWidget* Video, std::string Path, ImageStyle Imgstyle, int frame_width, int  frame_height);

	//ֹͣ����
	void StopSnapVideo(MyDockWidget* Video);

	//��ʾ��Ļ
	void StartSubTitle(MyDockWidget* Video);

	//���������ʽ
	void SetFontParam(MyDockWidget* Video, uint offsetx, uint offsety, uint cR, uint cG, uint cB, uint fontheight);

	//������Ļ����
	void SetSubTitle(MyDockWidget* Video,std::string title);

	//ֹͣ��Ļ��ʾ
	void StopSubTitle(MyDockWidget* Video);



private:
	ImageSaveVideo* savevideo;

	ImageSnapImage* sanpimage;

	static ICamera* createCamera(const CameraType cameraType);

	bool TryConnectCamera(ICamera* Cmaera);
	


private slots:

};
