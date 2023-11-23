#pragma once

#include <QDialog>
#include <QPushButton>
#include <QCombobox>
#include <mjis_hmi_global.h>


namespace Ui {
class DataSetInformation;
}

namespace mjis {

    namespace hmi {


        class DataSetInformation : public QDialog
        {
            Q_OBJECT

        public:


            explicit DataSetInformation(QWidget* parent = nullptr);


            explicit DataSetInformation(const QString& name);

            ~DataSetInformation();

            //设置数据
            void SetName(const QString& name);

            //读取配置
            void ReadConfig();

        private slots:
            //添加读取配置
            void on_readadd_clicked();

            //删除读取配置
            void on_readdelete_clicked();

            //添加写入配置
            void on_writeadd_clicked();

            //删除写入配置
            void on_writedelete_clicked();

            //保存配置
            void on_state_accepted();

            //取消按钮
            void on_state_rejected();

        private:
            Ui::DataSetInformation* ui;

            //连接名称
            QString name;

            //创建数据类型
            QComboBox* CreateDataStyle(int idex = 0);

            //创建字节顺序
            QComboBox* CreateByteOrder(int idex = 0);

            //创建写入数据列表
            QComboBox* CreateDataWriteList(int idex = 0);

        signals:
            //完成配置
            void CompleteConfig();



        };


    }
}

