#include "randomforestconfig.h"
#include "ui_randomforestconfig.h"


RandomForestConfig::RandomForestConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::randomforestconfig)
{
    ui->setupUi(this);
}


RandomForestConfig::~RandomForestConfig()
{
    delete ui;
}


//获取设置的参数信息
std::tuple<int, int, int, double, bool, int> RandomForestConfig::ReturnCofig()
{
    int depth = ui->depth->value();
    int mincount = ui->mincount->value();
    int max_iterations = ui->max_iterations->value();
    double epsilon = ui->epsilon->value();
    bool importance = ui->importance->isChecked();
    int randomcount = ui->randomcount->value();
    return std::make_tuple(depth, mincount, max_iterations, epsilon, importance, randomcount);
}



