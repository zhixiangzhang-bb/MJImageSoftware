#pragma once

#include <QObject>

class cameraagent  : public QObject
{
	Q_OBJECT

public:
	cameraagent(QObject *parent);
	~cameraagent();
};
