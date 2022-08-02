#pragma once
#include <cstdlib>
#include <cstdio>
#include <deque>

typedef struct _thread {
	unsigned int id;
	unsigned int clock_times;
	unsigned int max_clock_times;
}thread, *pthread;

extern thread idle_thread;

typedef std::deque<thread*> thread_queue;

extern thread_queue first_ready_queue;

extern thread_queue second_ready_queue;

extern thread_queue blocked_queue;

extern thread* current_thread;

void add_ready_thread(thread* ready_thread);
void current_thread_finished();
void current_thread_blocked();					// 当前线程被阻塞时调用
void notify();									// 线程阻塞结束后被调用
void notify_all();
void on_clock();								// 模拟的时钟信号函数
void set_first_time_ticks(unsigned int ticks);		// 设置第一级Ready队列中作业的最长时间片
void set_second_time_ticks(unsigned int ticks);		// 设置第二级Ready队列中作业的最长时间片
void set_time_interval(unsigned int interval);	// 设置时钟中断触发一次对应的时间增量