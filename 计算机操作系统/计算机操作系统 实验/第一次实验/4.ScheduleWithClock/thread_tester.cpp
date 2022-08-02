#include "thread_hdr.h"
#include <iostream>

thread idle_thread = { 0 };

thread_queue ready_queue;

thread_queue blocked_queue;

thread* current_thread = &idle_thread;

bool test_multi_thread()
{
	ready_queue.clear();
	set_time_ticks(40);
	set_time_interval(20);
	current_thread = &idle_thread;

	thread thread1 = { 1 };
	thread thread2 = { 2 };
	thread thread3 = { 3 };
	add_ready_thread(&thread1);
	add_ready_thread(&thread2);
	add_ready_thread(&thread3);

	on_clock();
	on_clock();
	on_clock();
	on_clock();
	if (current_thread != &thread2)
	{
		return false;
	}

	on_clock();
	on_clock();
	if (current_thread != &thread3)
	{
		return false;
	}

	return true;
}

int main()
{
	bool ret = test_multi_thread();
	std::cout << ret << std::endl;
	return 0;
}
