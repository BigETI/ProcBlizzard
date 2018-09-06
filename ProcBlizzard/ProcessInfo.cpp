#include "ProcessInfo.h"

using namespace std;
using namespace ProcBlizzard;

ProcessInfo::ProcessInfo(DWORD id, const string & name) : id(id), name(name)
{
	// ...
}

ProcessInfo::ProcessInfo(const ProcessInfo & processInfo) : id(processInfo.id), name(processInfo.name)
{
	// ...
}

ProcessInfo::~ProcessInfo()
{
	// ...
}

ProcessInfo & ProcessInfo::operator=(const ProcessInfo & processInfo)
{
	id = processInfo.id;
	name = processInfo.name;
	return (*this);
}

DWORD ProcessInfo::GetID()
{
	return id;
}

const string & ProcessInfo::GetName()
{
	return name;
}
