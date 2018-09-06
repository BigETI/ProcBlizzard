#ifndef __PROC_BLIZZARD_PROCESSES_H__
#	define __PROC_BLIZZARD_PROCESSES_H__

#	include "ASnapshot.h"
#	include "ProcessInfo.h"
#	include <vector>
#	include <set>

/// <summary>
/// Process blizzard namespace
/// </summary>
namespace ProcBlizzard
{
	/// <summary>
	/// Processes snapshot class
	/// </summary>
	class ProcessesSnapshot : public ASnapshot
	{
	private:
		ProcessesSnapshot(const ProcessesSnapshot &);

		ProcessesSnapshot & operator = (const ProcessesSnapshot &);
	public:
		/// <summary>
		/// Constructor
		/// </summary>
		ProcessesSnapshot();

		/// <summary>
		/// Destructor
		/// </summary>
		~ProcessesSnapshot();

		/// <summary>
		/// Get processes
		/// </summary>
		/// <param name="result">Result</param>
		/// <returns>Processes</returns>
		std::vector<ProcessInfo> & GetProcesses(std::vector<ProcessInfo> & result);

		/// <summary>
		/// Get processes
		/// </summary>
		/// <param name="filter">Filter</param>
		/// <param name="result">Result</param>
		/// <returns>Processes</returns>
		std::vector<ProcessInfo> & FilterProcesses(const std::set<std::string> & filter, std::vector<ProcessInfo> & result);
	};
}
#endif
