#include "Command.h"

using namespace std;
using namespace ProcBlizzard;

Command::Command(unsigned int minArgCount, unsigned int deltaArgCount, const string & description) : minArgCount(minArgCount), deltaArgCount(deltaArgCount), description(description)
{
	// ...
}

Command::Command(const Command & command) : minArgCount(command.minArgCount), deltaArgCount(command.deltaArgCount), description(command.description), helpTopics(command.helpTopics)
{
	// ...
}

Command::~Command()
{
	// ...
}

Command & Command::operator=(const Command & command)
{
	minArgCount = command.minArgCount;
	deltaArgCount = command.deltaArgCount;
	description = command.description;
	helpTopics = command.helpTopics;
	return (*this);
}

unsigned int Command::GetMinArgCount()
{
	return minArgCount;
}

unsigned int Command::GetMaxArgCount()
{
	return minArgCount + deltaArgCount;
}

const string & Command::GetDescription()
{
	return description;
}

const vector<string> & Command::GetHelpTopics()
{
	return helpTopics;
}

void Command::Execute(vector<string> args)
{
	for (const function<void(vector<string>)> & on_execute_function : onExecuteFunctions)
	{
		on_execute_function(args);
	}
}

void Command::AddHelpTopic(const string & help)
{
	helpTopics.push_back(help);
}

void Command::AddExecuteFunction(const function<void(const vector<string> &)> & onExecuteFunction)
{
	onExecuteFunctions.push_back(onExecuteFunction);
}
