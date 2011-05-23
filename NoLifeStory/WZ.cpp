////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

vector<NLS::WZ::File*> Files;
string Path;
NLS::Node NLS::WZ::Top; 

bool NLS::WZ::Init(string path) {
	Path = path;
	new File("Base");
	return true;
}

NLS::WZ::File::File(string name) {
	this->name = name;
	string filename = Path+name+".wz";
	file.open(filename,file.in|file.binary);
	if(!file.is_open()){
		delete this;
		return;
	}
	Files.push_back(this);
	Header* head = new Header(name,this);
}

NLS::WZ::Header::Header(string name, File* file) {
	this->name = name;
	type = ObjectType::TypeHeader;
	char s1[4];
	file->file.read(s1,4);
	ident.assign(s1,4);
}