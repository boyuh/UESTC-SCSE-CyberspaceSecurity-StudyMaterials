#include "thread_hdr.h"
#include <windows.h>
#include <iostream>

thread_queue ready_queue;

thread* current_thread = NULL;

bool test_two_thread()
{
	current_thread = NULL;
	ready_queue.clear();
	// 向ready队列中加入一个线程
	thread thread1 = { 1 };
	thread thread2 = { 2 };
	add_ready_thread(&thread1);
	add_ready_thread(&thread2);
	// 进行切换时，将current_thread切换为thread1
	schedule();
	if (current_thread != &thread1 || ready_queue.size() != 1)
	{
		return false;
	}
	// 进行切换时，将current_thread切换为thread1

	schedule();
	if (current_thread != &thread2 || ready_queue.size() != 1)
	{
		return false;
	}
	return true;
}

int main()
{
	bool ret = test_two_thread();
	std::cout << ret << std::endl;

	return 0;
}
