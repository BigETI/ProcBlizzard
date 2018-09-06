#include "ASnapshot.h"
#include <tlhelp32.h>

using namespace std;
using namespace ProcBlizzard;

ASnapshot::ASnapshot(DWORD flags) : snapshotHandle(INVALID_HANDLE_VALUE), lastError(0)
{
	snapshotHandle = CreateToolhelp32Snapshot(flags, 0);
	if (snapshotHandle == INVALID_HANDLE_VALUE)
	{
		lastError = ::GetLastError();
	}
}

ASnapshot::~ASnapshot()
{
	if (snapshotHandle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(snapshotHandle);
		snapshotHandle = INVALID_HANDLE_VALUE;
	}
}

HANDLE ASnapshot::GetSnapshotHandle()
{
	return snapshotHandle;
}

void ASnapshot::UpdateLastError()
{
	lastError = ::GetLastError();
}

DWORD ASnapshot::GetLastError()
{
	return lastError;
}
