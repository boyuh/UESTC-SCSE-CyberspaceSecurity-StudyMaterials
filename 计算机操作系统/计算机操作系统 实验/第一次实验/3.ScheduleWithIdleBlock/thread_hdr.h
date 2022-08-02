#pragma once
#include <cstdlib>
#include <cstdio>
#include <deque>

typedef struct _thread {
	unsigned int id;
} thread, * pthread;

extern thread idle_thread;

typedef std::deque<pthread> thread_queue;

extern thread_queue ready_queue;

extern thread_queue blocked_queue;

extern thread* current_thread;

void add_ready_thread(thread* ready_thread);
void schedule();
void current_thread_finished();
void current_thread_blocked();  // 当前线程被阻塞时调用
void notify();   // 线程阻塞结束后被调用
void notify_all();