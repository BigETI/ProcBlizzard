#ifndef __PROC_BLIZZARD_THREAD_INFO_H__
#	define __PROC_BLIZZARD_THREAD_INFO_H__
#	define WIN32_LEAN_AND_MEAN

#	include <Windows.h>

/// <summary>
/// Process blizzard namespace
/// </summary>
namespace ProcBlizzard
{
	/// <summary>
	/// Thread info class
	/// </summary>
	class ThreadInfo
	{
	private:
		/// <summary>
		/// Process ID
		/// </summary>
		DWORD processID;

		/// <summary>
		/// Thread ID
		/// </summary>
		DWORD threadID;

		ThreadInfo();
	public:
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="processID">Process ID</param>
		/// <param name="threadID">Thread ID</param>
		ThreadInfo(DWORD processID, DWORD threadID);

		/// <summary>
		/// Copy constructor
		/// </summary>
		/// <param name="threadInfo">Thread info</param>
		ThreadInfo(const ThreadInfo & threadInfo);

		/// <summary>
		/// Destructor
		/// </summary>
		~ThreadInfo();

		/// <summary>
		/// Assign operator
		/// </summary>
		/// <param name="threadInfo">Thread info</param>
		/// <returns>Itself</returns>
		ThreadInfo & operator = (const ThreadInfo & threadInfo);

		/// <summary>
		/// Get process ID
		/// </summary>
		/// <returns>Process ID</returns>
		DWORD GetProcessID();

		/// <summary>
		/// Get thread ID
		/// </summary>
		/// <returns>Thread ID</returns>
		DWORD GetThreadID();
	};
}
#endif
