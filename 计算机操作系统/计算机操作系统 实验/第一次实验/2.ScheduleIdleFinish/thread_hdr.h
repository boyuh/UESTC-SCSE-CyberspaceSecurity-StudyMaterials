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

extern thread* current_thread;

void add_ready_thread(thread* ready_thread);
void schedule();
void current_thread_finished();