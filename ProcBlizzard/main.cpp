#define WIN32_LEAN_AND_MEAN
#include "resource.h"
#include <Windows.h>
#include <tlhelp32.h>
#include <set>
#include <vector>
#include <algorithm>
#include <thread>
#include "ECMDParseState.h"

// Using
using namespace std;

// Sleep time
DWORD sleepTime(5000);

// Windows Main
int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	int ret = 0;
	int argc = __argc;
	char **argv = __argv;
	set<string> processes;
	vector<thread *> process_threads;
	string arg;
	PROCESSENTRY32 entry;
	set<string>::iterator it, end;
	thread *t;
	ECMDParseState parse_state(ECMDParseState_Default);
	for (int i = 1; i < argc; i++)
	{
		arg = argv[i];
		std::transform(arg.begin(), arg.end(), arg.begin(), ::tolower);
		switch (parse_state)
		{
		case ECMDParseState_Default:
			if (arg.find("-t") == 0)
			{
				parse_state = ECMDParseState_Time;
			}
			else
			{
				processes.insert(arg);
			}
			break;
		case ECMDParseState_Time:
			sleepTime = atoi(arg.c_str());
			parse_state = ECMDParseState_Default;
			break;
		}
	}
	end = processes.end();
	entry.dwSize = sizeof(PROCESSENTRY32);
	HANDLE snapshot(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL));
	if (Process32First(snapshot, &entry) == TRUE)
	{
		while (Process32Next(snapshot, &entry) == TRUE)
		{
			arg = entry.szExeFile;
			std::transform(arg.begin(), arg.end(), arg.begin(), ::tolower);
			it = processes.find(arg);
			if (it != end)
			{
				try
				{
					t = new thread([](DWORD process_id)
					{
						HANDLE threads_snapshot;
						THREADENTRY32 thread_entry;
						vector<HANDLE> thread_handles;
						HANDLE process_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, process_id);
						if (process_handle)
						{
							threads_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
							if (threads_snapshot != INVALID_HANDLE_VALUE)
							{
								thread_entry.dwSize = sizeof(THREADENTRY32);
								if (Thread32First(threads_snapshot, &thread_entry))
								{
									do
									{
										if (thread_entry.th32OwnerProcessID == process_id)
										{
											HANDLE thread_handle = OpenThread(THREAD_ALL_ACCESS, FALSE, thread_entry.th32ThreadID);
											if (thread_handle)
											{
												SuspendThread(thread_handle);
												thread_handles.push_back(thread_handle);
											}
										}
									} while (Thread32Next(threads_snapshot, &thread_entry));
									Sleep(sleepTime);
									for (HANDLE thread_handle : thread_handles)
									{
										ResumeThread(thread_handle);
										CloseHandle(thread_handle);
									}
									thread_handles.clear();
								}
								CloseHandle(threads_snapshot);
							}
							CloseHandle(process_handle);
						}
					}, entry.th32ProcessID);
					if (t)
					{
						process_threads.push_back(t);
					}
				}
				catch (exception e)
				{
					MessageBoxA(nullptr, e.what(), "Error", MB_ICONERROR | MB_OK);
				}
				catch (...)
				{
					MessageBoxA(nullptr, "Unknow error", "Error", MB_ICONERROR | MB_OK);
				}
			}
		}
	}
	else
	{
		ret = GetLastError();
	}
	CloseHandle(snapshot);
	for (thread *process_thread : process_threads)
	{
		try
		{
			process_thread->join();
			delete process_thread;
		}
		catch (exception e)
		{
			MessageBoxA(nullptr, e.what(), "Error", MB_ICONERROR | MB_OK);
		}
		catch (...)
		{
			MessageBoxA(nullptr, "Unknow error", "Error", MB_ICONERROR | MB_OK);
		}
	}
	processes.clear();
	process_threads.clear();
	return ret;
}