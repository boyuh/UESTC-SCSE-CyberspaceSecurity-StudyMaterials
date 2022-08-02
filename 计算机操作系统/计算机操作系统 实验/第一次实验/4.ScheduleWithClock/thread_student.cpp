#include "thread_hdr.h"

unsigned int ex_ticks;
unsigned int ex_interval;
extern unsigned int ex_ticks;
extern unsigned int ex_interval;

void add_ready_thread(thread* ready_thread)
{
	ready_queue.push_back(ready_thread);
}

void schedule()
{
	if(ready_queue.size()!=0){
		if(current_thread != NULL && current_thread != &idle_thread) ready_queue.push_back(current_thread);
		current_thread=ready_queue.front();
		current_thread->clock_times=0;
		ready_queue.pop_front();
	}else{
		if(current_thread != NULL) return;
		current_thread=&idle_thread;
	}
}

void current_thread_finished()
{
	if(current_thread != NULL && current_thread != &idle_thread) current_thread = NULL;
	schedule();
}

void current_thread_blocked()
{
	if(current_thread != NULL && current_thread != &idle_thread){
		blocked_queue.push_back(current_thread);
		current_thread = NULL;
	}
	schedule();
}

void notify()
{
	if(blocked_queue.size()==0) return;
	ready_queue.push_back(blocked_queue.front());
	blocked_queue.pop_front();
}

void notify_all()
{
	while(blocked_queue.size()!=0){
		ready_queue.push_back(blocked_queue.front());
		blocked_queue.pop_front();
	}
}

void on_clock()
{
	if(current_thread != NULL && current_thread != &idle_thread){
		current_thread->clock_times+=ex_interval;
		if(current_thread->clock_times>=ex_ticks && ready_queue.size()!=0){
			schedule();
		}
	}else{
		schedule();
	}
}

void set_time_ticks(unsigned int ticks)
{
	ex_ticks=ticks;
}

void set_time_interval(unsigned int interval)
{
	ex_interval=interval;
}
