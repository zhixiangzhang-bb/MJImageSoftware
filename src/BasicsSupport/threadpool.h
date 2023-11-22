#pragma once
#include <taskflow.hpp>




/*****************************************************************
* 类名称：线程池技术
* 功能描述：用于异步调用，目前还比较简单
* 作者：zzx
* 创建日期：2023.8.17
* 最后修改：zzx
* 最后修改日期：
* 备注：
******************************************************************/




class ThreadPool
{
public:
	ThreadPool();

	/// <summary>
	/// 重载构造函数
	/// </summary>
	/// <param name="num"></param>执行器管理的线程数
	ThreadPool(int num);

	~ThreadPool();  

	//返回掌握的线程数量
	int ReturnThreadNum();

	//返回执行的任务流数量
	int ReturnTaskNum();

	//返回观察者数量
	int ReturnObserversNum();

	//返回拓扑数量
	int ReturnTopologiesNum();

	/// <summary>
	/// 按固定次数执行任务
	/// </summary>
	/// <param name="taskflow"></param>任务流
	/// <param name="num"></param>执行的次数
	void RunTaskFlow(tf::Taskflow& taskflow, int num=0,bool manage=false);


private:
	//任务流
	std::vector<std::shared_ptr<tf::Taskflow>> TaskFlowList;

	//任务列表
	std::vector<tf::Task> TaskList;

	//执行器
	std::shared_ptr<tf::Executor> executor;

};



/*****************************************************************
* 类名称：执行器观察者类
* 功能描述：通过重写实现根据执行器不同状态
* 作者：zzx
* 创建日期：2023.8.18
* 最后修改：zzx
* 最后修改日期：
* 备注：直接写在头文件里面
******************************************************************/



struct MyObserver : public tf::ObserverInterface 
{
	//构造函数
	MyObserver(const std::string& name) {
		std::cout << "constructing observer " << name << '\n';
	}

	
	void set_up(size_t num_workers) override final {
		std::cout << "setting up observer with " << num_workers << " workers\n";
	}

	/**
	 * @brief 运行任务之前被调用
	*/
	void on_entry(tf::WorkerView wv, tf::TaskView tv) override final {
		std::ostringstream oss;
		oss << "worker " << wv.id() << " ready to run " << tv.name() << '\n';
		std::cout << oss.str();
	}

	/**
	 * @brief 完成任务后调用此函数
	*/
	void on_exit(tf::WorkerView wv, tf::TaskView tv) override final {
		std::ostringstream oss;
		oss << "worker " << wv.id() << " finished running " << tv.name() << '\n';
		std::cout << oss.str();
	}

};





class CustomWorkerBehavior : public tf::WorkerInterface {
public:
	// to call before the worker enters the scheduling loop
	void scheduler_prologue(tf::Worker& w) override {
		std::cout << tf::stringify("worker ", w.id(), " enters the scheduler loop\n");
	}
	// to call after the worker leaves the scheduling loop
	void scheduler_epilogue(tf::Worker& w, std::exception_ptr) override {
		std::cout << tf::stringify("worker ", w.id(), " leaves the scheduler loop\n");
	}
};

