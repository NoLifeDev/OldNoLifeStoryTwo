////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

set<NLS::WZ::File*> Files;
string Path;
NLS::Node NLS::WZ::Top;
NLS::Node NLS::WZ::Empty;
#define Read(f, v) f.read((char*)&v, sizeof(v))

bool NLS::WZ::Init(string path) {
	Path = path;
	new File("Base");
	return true;
}

NLS::WZ::Object::Object() {
	parsed = false;
}

NLS::WZ::File::File(string name) {
	this->name = name;
	type = TypeFile;
	string filename = Path+name+".wz";
	file.open(filename, file.in|file.binary);
	if (!file.is_open()) {
		cerr << "ERROR: Failed to load WZ file: " << filename << endl;
	}
	Files.insert(this);
	Header* head = new Header(name, this);
	for (int i = 1; i < 0x7F; i++) {
		uint32_t vh = Hash(head->version, i);
		if (vh) {
			head->versionHash = vh;
			version = i;
		}
	}
	new Directory(name, this, Top);
	parsed = true;
}

uint32_t NLS::WZ::File::Hash(uint16_t enc, uint16_t real) {
	char s[5];
	int hash = 0;
	int l = sprintf(s, "%d", real);
	for (int i = 0; i < l; i++) {
		hash = 32*hash+s[i]+1;
	}
	uint32_t result = 0xFF^(hash>>24)^(hash<<8>>24)^(hash<<16>>24)^(hash<<24>>24);
	if (result == enc) {
		return hash;
	} else {
		return 0;
	}
}

NLS::WZ::Header::Header(string name, File* file) {
	this->name = name;
	type = TypeHeader;
	char s1[4];
	file->file.read(s1, 4);
	ident.assign(s1, 4);
	Read(file->file, fileSize);
	Read(file->file, fileStart);
	file->file >> copyright;
	file->file.seekg(fileStart);
	Read(file->file, version);
	parsed = true;
}

NLS::WZ::Directory::Directory(string name, File* file, Node n) {
	this->name = name;
	Node nn = n.g(name);
}

NLS::Node::Node() {
	data = 0;
}

NLS::Node::Node(const Node& other) {
	data = other.data;
}

NLS::Node& NLS::Node::operator[] (const string& key) {
	if (data) {
		return data->children[key];
	} else {
		return WZ::Empty;
	}
}

NLS::Node& NLS::Node::operator[] (const char key[]) {
	if (data) {
		return data->children[key];
	} else {
		return WZ::Empty;
	}
}

NLS::NodeData::NodeData() {
	image = 0;
	has = 0;
}