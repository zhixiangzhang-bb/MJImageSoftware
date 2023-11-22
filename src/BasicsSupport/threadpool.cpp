#include "threadpool.h"


ThreadPool::ThreadPool():executor(new tf::Executor)
{

}




/// <summary>
/// 重载构造函数，根据设定数量实例化
/// </summary>
/// <param name="num"></param>线程数量
ThreadPool::ThreadPool(int num) :executor(new tf::Executor(num))
{
	
}



/// <summary>
/// 析构函数
/// </summary>
ThreadPool::~ThreadPool()
{

}


//返回持有的线程数
int ThreadPool::ReturnThreadNum()
{
	return executor->num_workers();
}


//返回执行的任务流数量
int ThreadPool::ReturnTaskNum()
{
	return executor->num_taskflows();
}


//返回观察者数量
int ThreadPool::ReturnObserversNum()
{
	return executor->num_observers();
}

//返回拓扑数量
int ThreadPool::ReturnTopologiesNum()
{
	return executor->num_topologies();
}



void ThreadPool::RunTaskFlow(tf::Taskflow& taskflow, int num, bool manage)
{
	if (num <= 0) {
		if (manage) {
			executor->run(std::move(taskflow));
		}
		else {
			executor->run(taskflow);
		}
	}
	else 
	{
		if (manage) {
			executor->run_n(std::move(taskflow), num);
		}
		else {
			executor->run_n(taskflow, num);
		}
	}
}




