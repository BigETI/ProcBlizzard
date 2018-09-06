#include "ThreadInfo.h"

using namespace std;
using namespace ProcBlizzard;


ThreadInfo::ThreadInfo(DWORD processID, DWORD threadID) : processID(processID), threadID(threadID)
{
	// ...
}

ThreadInfo::ThreadInfo(const ThreadInfo & threadInfo) : processID(threadInfo.processID), threadID(threadInfo.threadID)
{
	// ...
}

ThreadInfo::~ThreadInfo()
{
	// ...
}

ThreadInfo & ThreadInfo::operator=(const ThreadInfo & threadInfo)
{
	processID = threadInfo.processID;
	threadID = threadInfo.threadID;
	return (*this);
}

DWORD ThreadInfo::GetProcessID()
{
	return processID;
}

DWORD ThreadInfo::GetThreadID()
{
	return threadID;
}
