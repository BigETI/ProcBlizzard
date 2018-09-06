#ifndef __PROC_BLIZZARD_THREADS_SNAPSHOT_H__
#	define __PROC_BLIZZARD_THREADS_SNAPSHOT_H__

#	include "ASnapshot.h"
#	include "ThreadInfo.h"
#	include <vector>
#	include <set>

/// <summary>
/// Process blizzard namespace
/// </summary>
namespace ProcBlizzard
{
	/// <summary>
	/// Threads class
	/// </summary>
	class ThreadsSnapshot : public ASnapshot
	{
	private:
		ThreadsSnapshot(const ThreadsSnapshot &);

		ThreadsSnapshot & operator = (const ThreadsSnapshot &);
	public:
		/// <summary>
		/// Constructor
		/// </summary>
		ThreadsSnapshot();

		/// <summary>
		/// Destructor
		/// </summary>
		~ThreadsSnapshot();

		/// <summary>
		/// Get threads
		/// </summary>
		/// <param name="result">Result</param>
		/// <returns>Thread IDs</returns>
		std::vector<ThreadInfo> & GetThreads(std::vector<ThreadInfo> & result);

		/// <summary>
		/// Get threads from process IDs
		/// </summary>
		/// <param name="filter">Filter</param>
		/// <param name="result">Result</param>
		/// <returns>Thread IDs</returns>
		std::vector<ThreadInfo> & GetThreadsFromProcessIDs(const std::set<DWORD> & filter, std::vector<ThreadInfo> & result);
	};
}
#endif
