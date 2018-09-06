#ifndef __PROC_BLIZZARD_A_SNAPSHOT_H__
#	define __PROC_BLIZZARD_A_SNAPSHOT_H__
#	define WIN32_LEAN_AND_MEAN

#	include <Windows.h>

/// <summary>
/// Process blizzard namespace
/// </summary>
namespace ProcBlizzard
{
	/// <summary>
	/// Snapshot abstract class
	/// </summary>
	class ASnapshot
	{
	private:
		/// <summary>
		/// Snapshot
		/// </summary>
		HANDLE snapshotHandle;

		/// <summary>
		/// Last error
		/// </summary>
		DWORD lastError;

		ASnapshot();
		ASnapshot(const ASnapshot &);
		ASnapshot & operator = (const ASnapshot &);
	protected:
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="flags">Snapshot flags</param>
		ASnapshot(DWORD flags);

		/// <summary>
		/// Destructor
		/// </summary>
		~ASnapshot();

		/// <summary>
		/// Get snapshot handle
		/// </summary>
		/// <returns>Snapshot handle</returns>
		HANDLE GetSnapshotHandle();

		/// <summary>
		/// Update last error
		/// </summary>
		void UpdateLastError();
	public:
		/// <summary>
		/// Get last error
		/// </summary>
		/// <returns>Last error</returns>
		DWORD GetLastError();
	};
}
#endif
