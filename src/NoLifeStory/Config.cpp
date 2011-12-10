////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

bool NLS::Profiling = false;
vector<string> NLS::ProfileMaps;

void NLS::Config::Load() {
	ifstream file("client.config");
	if (!file.is_open()) return LoadDefault();
	while (!file.eof()) {
		string line;
		getline(file, line);
		if (line.size() == 0 || line[0] == '#') continue; // Skip lines with comments or just nothing at all
		size_t pos = line.find_first_of('=');
		if (pos == string::npos) continue;
		string key = line.substr(0, pos);
		string value =  line.substr(pos+1);
		if (key == "path") Paths.push_back(value);
		else if (key == "mindfuck") Mindfuck = value == "true";
		else if (key == "mute") bMute = value == "true";
		else if (key == "fullscreen") Fullscreen = value == "true";
		else if (key == "online") Network::Online = value == "true";
		else if (key == "ms_ip") Network::IP = value;
		else if (key == "ms_port") Network::Port = toint(value);
		else if (key == "profile") Profiling = value == "true";
		else if (key == "ui")
			if (value == "beta") UI::Style = UI::Beta;//Unsupported
			else if (value == "classic") UI::Style = UI::Classic;//Unsupported
			else if (value == "modern") UI::Style = UI::Modern;
			else UI::Style = UI::Clean;
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
	Write("mute", bMute?"true":"false");
	Write("fullscreen", Fullscreen?"true":"false");
	if (Network::IP == "") Network::IP = "63.251.217.3";
	if (Network::Port == 0) Network::Port = 8484;
	Write("online", Network::Online?"true":"false");
	Write("ms_ip", Network::IP);
	Write("ms_port", tostring(Network::Port));
	Write("profile", Profiling?"true":"false");
	switch (UI::Style) {
	case UI::Beta: Write("ui", "beta"); break;
	case UI::Classic: Write("ui", "classic"); break;
	case UI::Modern: Write("ui", "modern"); break;
	case UI::Clean: Write("ui", "clean"); break;
	}
}