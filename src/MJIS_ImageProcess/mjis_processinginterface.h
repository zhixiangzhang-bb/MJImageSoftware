#ifndef PROCESSINGINTERFACE_H
#define PROCESSINGINTERFACE_H

#include <QWidget>

namespace Ui {
class processinginterface;
}

class ProcessingInterface : public QWidget
{
    Q_OBJECT

public:
    explicit ProcessingInterface(QWidget *parent = nullptr);

    ~ProcessingInterface();

    //添加行
    void AddStep(const QString name,const QString descriptions,int time);

    //删除行
    void DeleteStep();

private:
    Ui::processinginterface*ui;
};

#endif // PROCESSINGINTERFACE_H
