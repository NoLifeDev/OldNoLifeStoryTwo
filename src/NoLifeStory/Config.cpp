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
		} else if (key == "ms_ip") {
			Network::IP = value;
		} else if (key == "ms_port") {
			Network::Port = atoi(value.c_str());
		}
	}
	Config::Save();
}

void NLS::Config::LoadDefault() {
	Paths.push_back("");
	Paths.push_back("C:/Nexon/MapleStory/");
	Network::IP = "63.251.217.3";
	Network::Port = 8484;
	Config::Save();
}

void NLS::Config::Save() {
	ofstream file("client.config");
	if (!file.is_open()) return;

	auto Write = [&](string key, string value){
		file << key << "=" << value << endl;
	};

	for_each(Paths.begin(), Paths.end(), [&](path s){Write("path", s);});
	Write("mindfuck", Mindfuck?"true":"false");
	Write("fullscreen", Fullscreen?"true":"false");
	if (Network::IP == "") {
		Network::IP = "63.251.217.3";
	}
	if (Network::Port == 0) {
		Network::Port = 8484;
	}
	Write("ms_ip", Network::IP);
	Write("ms_port", tostring(Network::Port));
}