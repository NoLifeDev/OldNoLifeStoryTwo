////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

void NLS::Config::Load() {
	ifstream file("client.config");
	if (!file.is_open()) return LoadDefault();
	while (!file.eof()) {
		string line;
		getline(file, line);
		size_t pos = line.find_first_of('=');
		string key = line.substr(0, pos);
		string value =  line.substr(pos+1);
		if (key == "path") {
			Paths.push_back(value);
		} else if (key == "mindfuck") {
			Mindfuck = value == "true";
		} else if (key == "fullscreen") {
			Fullscreen = value == "true";
		}
	}
	Config::Save();
}
void NLS::Config::LoadDefault() {
	Paths.push_back("");
	Paths.push_back("C:/Nexon/MapleStory/");
	Config::Save();
}
void NLS::Config::Save() {
	ofstream file("client.config");
	if (!file.is_open()) return;
	auto Write = [&](string key, string value){file << key << "=" << value << endl;};
	for_each(Paths.begin(), Paths.end(), [&](path s){Write("path", s);});
	Write("mindfuck", Mindfuck?"true":"false");
	Write("fullscreen", Fullscreen?"true":"false");
}