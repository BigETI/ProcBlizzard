#include "ProcessesSnapshot.h"
#include <tlhelp32.h>
#include <cctype>
#include <algorithm>

using namespace std;
using namespace ProcBlizzard;

ProcessesSnapshot::ProcessesSnapshot() : ASnapshot(TH32CS_SNAPPROCESS)
{
	// ...
}

ProcessesSnapshot::~ProcessesSnapshot()
{
	// ...
}

vector<ProcessInfo> & ProcessesSnapshot::GetProcesses(vector<ProcessInfo> & result)
{
	HANDLE snapshot(GetSnapshotHandle());
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);
	result.clear();
	if (snapshot != INVALID_HANDLE_VALUE)
	{
		if (Process32First(snapshot, &entry) == TRUE)
		{
			while (Process32Next(snapshot, &entry) == TRUE)
			{
				result.push_back(ProcessInfo(entry.th32ProcessID, entry.szExeFile));
			}
		}
		else
		{
			UpdateLastError();
		}
	}
	return result;
}

vector<ProcessInfo> & ProcessesSnapshot::FilterProcesses(const set<string> & filter, vector<ProcessInfo> & result)
{
	vector<ProcessInfo> processes;
	string process_name;
	set<string>::const_iterator it, end(filter.end());
	result.clear();
	GetProcesses(processes);
	for (ProcessInfo & process_Info : processes)
	{
		process_name = process_Info.GetName();
		transform(process_name.begin(), process_name.end(), process_name.begin(), tolower);
		it = filter.find(process_name);
		if (it == end)
		{
			it = filter.find(to_string(process_Info.GetID()));
		}
		if (it != end)
		{
			result.push_back(process_Info);
		}
	}
	return result;
}
