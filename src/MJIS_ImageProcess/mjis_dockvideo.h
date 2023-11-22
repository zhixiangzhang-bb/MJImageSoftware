#ifndef DOCKVIDEO_H
#define DOCKVIDEO_H

#include "mjis_imageprocess_macro.h"




namespace Ui {
class DockVideo;
}

class MJIS_ImageProcess_API MyDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit MyDockWidget(QWidget *parent = nullptr);
    ~MyDockWidget();
    
    void closeEvent(QCloseEvent* event) override;

private:

    std::shared_ptr<QGraphicsPixmapItem> pixmapItem;


    QGraphicsScene* scene;


    Ui::DockVideo *ui;



protected:
    void wheelEvent(QWheelEvent* event) override;



public slots:
    void returnCameraQImage(QImage image);

signals:
    void MyDockeWidgetClose();


private slots:
    void on_scaling_currentIndexChanged(int index);
};

#endif // DOCKVIDEO_H
