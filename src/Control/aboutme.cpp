#include "aboutme.h"
#include "ui_aboutme.h"
#include <QFile>


AboutMe::AboutMe(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutMe)
{
    ui->setupUi(this);

    setWindowTitle("关于作者");

}



AboutMe::~AboutMe()
{
    delete ui;
}


