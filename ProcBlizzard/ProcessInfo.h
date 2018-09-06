#ifndef __PROC_BLIZZARD_PROCESS_INFO_H__
#	define __PROC_BLIZZARD_PROCESS_INFO_H__
#	define WIN32_LEAN_AND_MEAN

#	include <Windows.h>

#	include <string>

/// <summary>
/// Process blizzard namespace
/// </summary>
namespace ProcBlizzard
{
	/// <summary>
	/// Process class
	/// </summary>
	class ProcessInfo
	{
	private:
		/// <summary>
		/// Process ID
		/// </summary>
		DWORD id;

		/// <summary>
		/// Process name
		/// </summary>
		std::string name;

		ProcessInfo();
	public:
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="id">Process ID</param>
		/// <param name="name">Process name</param>
		ProcessInfo(DWORD id, const std::string & name);

		/// <summary>
		/// Copy constructor
		/// </summary>
		/// <param name="processInfo">Process info</param>
		ProcessInfo(const ProcessInfo & processInfo);

		/// <summary>
		/// Destructor
		/// </summary>
		~ProcessInfo();

		/// <summary>
		/// Assign operator
		/// </summary>
		/// <param name="processInfo">Process info</param>
		/// <returns>Itself</returns>
		ProcessInfo & operator = (const ProcessInfo & processInfo);

		/// <summary>
		/// Get process ID
		/// </summary>
		/// <returns>Process ID</returns>
		DWORD GetID();

		/// <summary>
		/// Get process name
		/// </summary>
		/// <returns>Process name</returns>
		const std::string & GetName();
	};
}
#endif
