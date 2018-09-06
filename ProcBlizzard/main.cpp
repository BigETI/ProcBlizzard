#include "resource.h"
#include "ProcessesSnapshot.h"
#include "ThreadsSnapshot.h"
#include "Thread.h"
#include "Command.h"
#include "ECommandParseState.h"
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;
using namespace ProcBlizzard;

/// <summary>
/// Help command
/// </summary>
static Command helpCommand(0U, 1U, "Show help topic");

/// <summary>
/// Time command
/// </summary>
static Command timeCommand(1U, 0U, "Set time in milliseconds to freeze specified processes");

/// <summary>
/// Verbose command
/// </summary>
static Command verboseCommand(0U, 0U, "Enables verbose logging");

/// <summary>
/// Show command help
/// </summary>
static Command *showCommandHelp(nullptr);

/// <summary>
/// Freeze time
/// </summary>
static DWORD freezeTime(5000);

/// <summary>
/// Verbose logging
/// </summary>
static bool verboseLogging(false);

/// <summary>
/// Commands
/// </summary>
const static map<string, Command *> commands =
{
	{ string("-h"), &helpCommand },
	{ string("--help"), &helpCommand },
	{ string("-t"), &timeCommand },
	{ string("--time"), &timeCommand },
	{ string("-v"), &verboseCommand },
	{ string("--verbose"), &verboseCommand },
};

/// <summary>
/// Print help topic
/// </summary>
/// <param name="command"></param>
void PrintHelpTopic(Command & command)
{
	if (command.GetHelpTopics().empty())
	{
		cout << endl << "Process blizzard help topic was not found for this command" << endl << endl;
	}
	else
	{
		cout << endl << "Process blizzard help topic" << endl << endl;
		for (const string & help : command.GetHelpTopics())
		{
			cout << help << endl;
		}
		cout << endl << "End of help topic of process blizzard" << endl;
	}
}

/// <summary>
/// Get error message
/// </summary>
/// <param name="errorCode">Error code</param>
/// <param name="result">Result</param>
/// <returns>Error message</returns>
string & GetErrorMessage(int errorCode, string & result)
{
	result.clear();
	if (errorCode != 0)
	{
		LPSTR messageBuffer(nullptr);
		size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPSTR>(&messageBuffer), 0, nullptr);
		result = string(messageBuffer, size);
		LocalFree(messageBuffer);
	}
	return result;
}

/// <summary>
/// Main entry point
/// </summary>
/// <param name="argc">Argument count</param>
/// <param name="argv">Arguments</param>
/// <returns>Exit code</returns>
int main(int argc, char *argv[])
{
	int ret(0);
	set<string> processes_filter;
	set<DWORD> threads_filter;
	vector<ProcessInfo> processes;
	vector<ThreadInfo> threads;
	Command *selected_command(nullptr);
	vector<string> args;
	string arg;
	bool parse_in_command(false);
	map<string, Command *>::const_iterator commands_end(commands.end());
	DWORD own_process_id(GetCurrentProcessId());
	try
	{
		helpCommand.AddHelpTopic("Description:");
		helpCommand.AddHelpTopic("\tThis tool freezes specified processes for a specified amount of time.");
		helpCommand.AddHelpTopic("\tBy default it freezes specified processes for " + to_string(freezeTime) + " milliseconds.");
		helpCommand.AddHelpTopic("\t\"-t\" or \"--time\" allows to set the time in milliseconds to freeze specified processes.");
		helpCommand.AddHelpTopic("\tEnable verbose logging with \"-v\" or \"--verbose\".");
		helpCommand.AddHelpTopic("");
		helpCommand.AddHelpTopic("Usage:");
		helpCommand.AddHelpTopic("\tProcBlizzard <Process names or process IDs> <Optional: \"-t\" or \"--time\" and time in milliseconds to freeze specified processes> <Optional: \"-v\" or \"--verbose\">");
		helpCommand.AddHelpTopic("");
		helpCommand.AddHelpTopic("Example:");
		helpCommand.AddHelpTopic("\tProcBlizzard notepad.exe paint.exe -t 10000 -v");
		helpCommand.AddHelpTopic("");
		helpCommand.AddHelpTopic("Commands:");
		for (const pair<string, Command *> & command : commands)
		{
			helpCommand.AddHelpTopic("\t" + command.first + "\t" + command.second->GetDescription());
		}
		helpCommand.AddExecuteFunction([](const vector<string> & args)
		{
			if (args.empty())
			{
				showCommandHelp = &helpCommand;
			}
			else
			{
				map<string, Command *>::const_iterator it(commands.find(args[0]));
				if (it != commands.end())
				{
					showCommandHelp = it->second;
				}
			}
		});
		timeCommand.AddHelpTopic("Description:");
		timeCommand.AddHelpTopic("\t" + timeCommand.GetDescription());
		timeCommand.AddHelpTopic("");
		timeCommand.AddHelpTopic("Usage:");
		timeCommand.AddHelpTopic("\tProcBlizzard <Process names or process IDs> --time <time in milliseconds to freeze specified processes>");
		timeCommand.AddExecuteFunction([](const vector<string> & args)
		{
			if (args.empty())
			{
				showCommandHelp = &timeCommand;
			}
			else
			{
				freezeTime = stoi(args[0]);
			}
		});
		verboseCommand.AddHelpTopic("Description:");
		verboseCommand.AddHelpTopic("\t" + verboseCommand.GetDescription());
		verboseCommand.AddHelpTopic("");
		verboseCommand.AddHelpTopic("Usage:");
		verboseCommand.AddHelpTopic("\tProcBlizzard <Process names or process IDs> --verbose");
		verboseCommand.AddExecuteFunction([](const vector<string> & args)
		{
			verboseLogging = true;
		});
		for (int i = 1; i < argc; i++)
		{
			arg = argv[i];
			if (parse_in_command)
			{
				args.push_back(arg);
				if (selected_command->GetMaxArgCount() <= args.size())
				{
					selected_command->Execute(args);
					args.clear();
					parse_in_command = false;
				}
			}
			else
			{
				transform(arg.begin(), arg.end(), arg.begin(), tolower);
				map<string, Command *>::const_iterator it(commands.find(arg));
				if (it != commands_end)
				{
					selected_command = it->second;
					if (it->second->GetMaxArgCount() > 0U)
					{
						parse_in_command = true;
					}
					else
					{
						selected_command->Execute(args);
					}
				}
				else
				{
					processes_filter.insert(arg);
				}
			}
		}
		if (parse_in_command)
		{
			if (selected_command->GetMinArgCount() <= args.size())
			{
				selected_command->Execute(args);
			}
			else
			{
				showCommandHelp = selected_command;
			}
			args.clear();
			parse_in_command = false;
		}
		if (processes_filter.empty())
		{
			if (showCommandHelp == nullptr)
			{
				showCommandHelp = &helpCommand;
			}
		}
		if (showCommandHelp)
		{
			PrintHelpTopic(*showCommandHelp);
		}
		else
		{
			if (verboseLogging)
			{
				cout << endl << "Specified process names or process IDs:" << endl;
				for (const string & process_filter : processes_filter)
				{
					cout << "\t" << process_filter << endl;
				}
			}
			ProcessesSnapshot processesSnapshot;
			processesSnapshot.FilterProcesses(processes_filter, processes);
			ret = processesSnapshot.GetLastError();
			if (ret == 0)
			{
				if (verboseLogging)
				{
					if (processes.empty())
					{
						cout << endl << "No specified processes found." << endl;
					}
					else
					{
						cout << endl << "Found specified processes:" << endl << "\t[Process ID]\t[Process name]" << endl;
						for (ProcessInfo & process_info : processes)
						{
							cout << "\t" << ((own_process_id == process_info.GetID()) ? "[!] " : "") << "[" << process_info.GetID() << ((own_process_id == process_info.GetID()) ? "]\t" : "]\t\t") << process_info.GetName() << endl;
						}
					}
				}
				for (ProcessInfo & process_info : processes)
				{
					if (own_process_id != process_info.GetID())
					{
						threads_filter.insert(process_info.GetID());
					}
				}
				if (!(threads_filter.empty()))
				{
					ThreadsSnapshot thread_snapshot;
					thread_snapshot.GetThreadsFromProcessIDs(threads_filter, threads);
					ret = thread_snapshot.GetLastError();
					if (ret == 0)
					{
						if (verboseLogging)
						{
							cout << endl << "Suspending associated threads:" << endl << "\t[Thread ID]\t[Process ID]" << endl;
							for (ThreadInfo & thread_info : threads)
							{
								cout << "\t[" << thread_info.GetThreadID() << "]\tin\t[" << thread_info.GetProcessID() << "]" << endl;
							}
						}
						for (ThreadInfo & thread_info : threads)
						{
							Thread(thread_info).Suspend();
						}
						if (verboseLogging)
						{
							cout << endl << "Please wait to finish..." << endl;
						}
						Sleep(freezeTime);
						if (verboseLogging)
						{
							cout << "Done!" << endl;
						}
						if (verboseLogging)
						{
							cout << endl << "Resuming all suspended threads..." << endl;
						}
						for (ThreadInfo & thread_info : threads)
						{
							Thread(thread_info).Resume();
						}
						if (verboseLogging)
						{
							cout << "Done!" << endl;
						}
					}
				}
			}
		}
	}
	catch (const exception & e)
	{
		cerr << e.what() << endl;
	}
	catch (...)
	{
		cerr << "An unknown error has occured!" << endl;
	}
	if (ret != 0)
	{
		string message;
		cerr << GetErrorMessage(ret, message) << endl;
	}
	return ret;
}
