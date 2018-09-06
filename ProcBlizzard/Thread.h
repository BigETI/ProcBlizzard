#ifndef __PROC_BLIZZARD_THREAD_H__
#	define __PROC_BLIZZARD_THREAD_H__

#	include "ThreadInfo.h"

/// <summary>
/// Process blizzard namespace
/// </summary>
namespace ProcBlizzard
{
	/// <summary>
	/// Thread class
	/// </summary>
	class Thread
	{
	private:
		/// <summary>
		/// Thread handle
		/// </summary>
		HANDLE handle;

		Thread();
	public:
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="threadID">Thread ID</param>
		Thread(DWORD threadID);

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="threadInfo">Thread info</param>
		Thread(ThreadInfo & threadInfo);

		/// <summary>
		/// Destructor
		/// </summary>
		~Thread();
		
		/// <summary>
		/// Suspend thread
		/// </summary>
		void Suspend();

		/// <summary>
		/// Resume thread
		/// </summary>
		void Resume();
	};
}
#endif
