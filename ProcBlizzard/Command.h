#ifndef __PROC_BLIZZARD_COMMAND_H__
#	define __PROC_BLIZZARD_COMMAND_H__

#	include <vector>
#	include <string>
#	include <functional>

/// <summary>
/// Process blizzard namespace
/// </summary>
namespace ProcBlizzard
{
	/// <summary>
	/// Command class
	/// </summary>
	class Command
	{
	private:
		/// <summary>
		/// Minimum argument count
		/// </summary>
		unsigned int minArgCount;

		/// <summary>
		/// Delta argument count
		/// </summary>
		unsigned int deltaArgCount;

		/// <summary>
		/// Description
		/// </summary>
		std::string description;

		/// <summary>
		/// Help topics
		/// </summary>
		std::vector<std::string> helpTopics;

		/// <summary>
		/// On execute functions
		/// </summary>
		std::vector<std::function<void (const std::vector<std::string> &)>> onExecuteFunctions;

		Command();
	public:
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="description">Description</param>
		Command(unsigned int minArgCount, unsigned int deltaArgCount, const std::string & description);

		/// <summary>
		/// Copy constructor
		/// </summary>
		/// <param name="command">Command</param>
		Command(const Command & command);

		/// <summary>
		/// Destructor
		/// </summary>
		~Command();

		/// <summary>
		/// Assign operator
		/// </summary>
		/// <param name="command">Command</param>
		/// <returns>Itself</returns>
		Command & operator = (const Command & command);

		/// <summary>
		/// Get minimum argument count
		/// </summary>
		/// <returns></returns>
		unsigned int GetMinArgCount();

		/// <summary>
		/// Get maximum argument count
		/// </summary>
		/// <returns></returns>
		unsigned int GetMaxArgCount();

		/// <summary>
		/// Get description
		/// </summary>
		/// <returns>Description</returns>
		const std::string & GetDescription();

		/// <summary>
		/// Get help topics
		/// </summary>
		/// <returns>Help topics</returns>
		const std::vector<std::string> & GetHelpTopics();

		/// <summary>
		/// Execute
		/// </summary>
		/// <param name="args">Arguments</param>
		void Execute(std::vector<std::string> args);

		/// <summary>
		/// Add help topic
		/// </summary>
		/// <param name="help">Help</param>
		void AddHelpTopic(const std::string & help);

		/// <summary>
		/// Add execute function
		/// </summary>
		/// <param name="onExecuteFunction">Execute function</param>
		void AddExecuteFunction(const std::function<void (const std::vector<std::string> &)> & onExecuteFunction);
	};
}
#endif
