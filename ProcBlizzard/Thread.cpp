#include "Thread.h"

using namespace std;
using namespace ProcBlizzard;

Thread::Thread(DWORD threadID) : handle(nullptr)
{
	handle = OpenThread(THREAD_ALL_ACCESS, FALSE, threadID);
}

Thread::Thread(ThreadInfo & threadInfo) : handle(nullptr)
{
	handle = OpenThread(THREAD_ALL_ACCESS, FALSE, threadInfo.GetThreadID());
}

Thread::~Thread()
{
	if (handle)
	{
		CloseHandle(handle);
		handle = nullptr;
	}
}

void Thread::Suspend()
{
	if (handle)
	{
		SuspendThread(handle);
	}
}

void Thread::Resume()
{
	if (handle)
	{
		ResumeThread(handle);
	}
}
