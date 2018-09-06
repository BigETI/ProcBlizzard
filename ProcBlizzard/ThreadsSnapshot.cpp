#include "ThreadsSnapshot.h"
#include <tlhelp32.h>

using namespace std;
using namespace ProcBlizzard;

ThreadsSnapshot::ThreadsSnapshot() : ASnapshot(TH32CS_SNAPTHREAD)
{
	// ...
}


ThreadsSnapshot::~ThreadsSnapshot()
{
	// ...
}

vector<ThreadInfo> & ThreadsSnapshot::GetThreads(vector<ThreadInfo> & result)
{
	HANDLE snapshot(GetSnapshotHandle());
	THREADENTRY32 entry;
	entry.dwSize = sizeof(THREADENTRY32);
	result.clear();
	if (snapshot != INVALID_HANDLE_VALUE)
	{
		entry.dwSize = sizeof(THREADENTRY32);
		if (Thread32First(snapshot, &entry))
		{
			do
			{
				result.push_back(ThreadInfo(entry.th32OwnerProcessID, entry.th32ThreadID));
			} while (Thread32Next(snapshot, &entry));
		}
	}
	return result;
}

vector<ThreadInfo> & ThreadsSnapshot::GetThreadsFromProcessIDs(const set<DWORD> & filter, vector<ThreadInfo> & result)
{
	vector<ThreadInfo> threads;
	set<DWORD>::const_iterator it, end(filter.end());
	result.clear();
	GetThreads(threads);
	for (ThreadInfo & thread_info : threads)
	{
		it = filter.find(thread_info.GetProcessID());
		if (it != end)
		{
			result.push_back(thread_info);
		}
	}
	return result;
}
