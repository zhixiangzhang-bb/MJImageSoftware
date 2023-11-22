#include "mjis_processinginterface.h"
#include "ui_mjis_processinginterface.h"
#include <QTableWidgetItem>




ProcessingInterface::ProcessingInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::processinginterface)
{
    ui->setupUi(this);
}



ProcessingInterface::~ProcessingInterface()
{
    int rowCount = ui->table->rowCount() - 1;
    if (rowCount >= 0)
    {
        for (size_t i = 0; i < rowCount; i++)
        {
            delete ui->table->item(rowCount, 0);
            delete ui->table->item(rowCount, 1);
            delete ui->table->item(rowCount, 2);
        }
   }
    delete ui;
}



//添加行
void ProcessingInterface::AddStep(const QString name, const QString descriptions, int time)
{
    int rowCount = ui->table->rowCount();
    ui->table->insertRow(rowCount);

    ui->table->setItem(rowCount, 0, new QTableWidgetItem(name));
    ui->table->setItem(rowCount, 1, new QTableWidgetItem(descriptions));
    ui->table->setItem(rowCount, 2, new QTableWidgetItem(QString::number(time)));
}


//删除行
void ProcessingInterface::DeleteStep()
{
    int rowCount = ui->table->rowCount()-1;
    delete ui->table->item(rowCount,0);
    delete ui->table->item(rowCount, 1);
    delete ui->table->item(rowCount, 2);
    ui->table->removeRow(rowCount);
}


