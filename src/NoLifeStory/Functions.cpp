////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

bool Functions::help(const string &args) {
	using CommandFunctions::CommandList;
	if (args.length() != 0) {
		if (CommandList.find(args) != CommandList.end()) {
			CommandFunctions::showSyntax(args, true);
		}
		else {
			NLS::C("INFO") << "Command \"" << args << "\" does not exist." << endl;
		}
	}
	else {
		ostringstream strm;
		bool has = false;
		for (auto iter = CommandList.begin(); iter != CommandList.end(); iter++) {
			if (!has) {
				strm << "Available commands: ";
				has = true;
			}
			strm << iter->first << " ";
		}
		NLS::C("INFO") << strm.str() << endl;
	}
	return true;
}