
#include "randomforestconfig.h"
#include <chartwidget.h>
#include "machinelearning.h"
#include "datapreprocessing.h"
#include <taskflow.hpp>


/*****************************************************************
* 类名称：随机森林类
* 功能描述：提供随机森林模型的训练、测试和部署
* 作者：zzx
* 创建日期：2023.8.11
* 最后修改：zzx
* 最后修改日期：
* 备注：
******************************************************************/



//利用命名空间区分
namespace zzxml {


	class  MachineLearning_API RandomForest
	{
	public:
		RandomForest();

		~RandomForest();

		//返回配置页面
		RandomForestConfig* ReturnConfig();

		//预加载数据
		void PreLoadData();

		//模型训练
		void ModelTrain();

		//模型测试
		void TestModel();

		//设置分类1路径
		void SetOkPath(std::string& path);


		//设置分类2路径
		void SetNgPath(std::string& ngpath);

		//设置模型存储路径
		void SetModelPath(std::string& modelpath);

		//绘制拟合曲线
		ChartWidget* ReturnFitChart();

	private:
		//决策树最大深度
		int depth;

		//节点最小样本数
		int mincount;

		//最大迭代次数
		int max_iterations;

		//最大容忍误差
		double epsilon;

		//计算变量重要性
		bool importance;

		//随机变量数目
		int randomcount;

		//分类1加载路径
		std::string okpath;

		//分类2加载路径
		std::string ngpath;

		//模型存储路径
		std::string modelpath;

		//配置页面
		std::shared_ptr<RandomForestConfig> config;

		//拟合曲线
		std::shared_ptr<ChartWidget> chart;
	};

}