////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

typedef bool (*CommandFunction)(const string &args);
struct Command {
	Command addToMap() {
		Command x = *this;
		notes.clear();
		syntax = "";
		return x;
	}
	CommandFunction command;
	string syntax;
	vector<string> notes;
};
typedef unordered_map<string, Command> CommandListType;

namespace CommandFunctions {
	extern CommandListType CommandList;
	void initialize();
	bool runRegexPattern(const string &args, const string &pattern, cmatch &matches);
	void showSyntax(const string &command, bool fromHelp = false);
	bool handleCommand(const string &command, const string &args);
}