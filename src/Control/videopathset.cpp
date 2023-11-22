#include "videopathset.h"
#include "ui_videopathset.h"
#include <QDir>
#include <QFileDialog>

VideoPathSet::VideoPathSet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VideoPathSet)
{
    ui->setupUi(this);
    QSettings settings("D:/ZImageSoft/CavitationAPP/Config/imagepath.cfg", QSettings::IniFormat);
    QString currentPath = QDir::currentPath();
    ui->lineEdit->setText(settings.value("videopath").toString());
    ui->lineEdit_2->setText(settings.value("imagepath").toString());
    ui->comboBox->setCurrentIndex(settings.value("videostyle").toInt());
    ui->comboBox_2->setCurrentIndex(settings.value("imagestyle").toInt());
}


VideoPathSet::~VideoPathSet()
{
    delete ui;
}



void VideoPathSet::on_pushButton_3_clicked()
{
    QSettings settings("D:/ZImageSoft/CavitationAPP/Config/imagepath.cfg", QSettings::IniFormat);
    settings.setValue("videopath", ui->lineEdit->text());
    settings.setValue("videostyle", ui->comboBox->currentIndex());
    settings.setValue("imagepath", ui->lineEdit_2->text());
    settings.setValue("imagestyle", ui->comboBox_2->currentIndex());
}


void VideoPathSet::on_pushButton_2_clicked()
{
    this->close();
}



void VideoPathSet::on_toolButton_clicked()
{
    // 创建选择文件的对话框
    QString dirPath = QFileDialog::getExistingDirectory(this, "选择文件夹");

    // 如果用户选择了文件
    if (!dirPath.isEmpty()) {
        ui->lineEdit->setText(dirPath);
    }
}



void VideoPathSet::on_toolButton_2_clicked()
{
    // 创建选择文件的对话框
    QString dirPath = QFileDialog::getExistingDirectory(this, "选择文件夹");

    // 如果用户选择了文件
    if (!dirPath.isEmpty()) {
        ui->lineEdit_2->setText(dirPath);
    }
}

