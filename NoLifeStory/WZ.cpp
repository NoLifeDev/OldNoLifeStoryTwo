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
	Top.data = new NodeData();
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
	int l = sprintf(s, "%d", real);
	int hash = 0;
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

NLS::Node& NLS::Node::operator= (const Node& other) {
	data = other.data;
	return *this;
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

NLS::Node& NLS::Node::g(const string& key) {
	if (!data) {
		throw(string("Horrible loading skills"));
	}
	Node& n = data->children[key];
	n.data = new NodeData();
	n.data->parent = *this;
	return n;
}

map<string, NLS::Node>::iterator NLS::Node::Begin() {
	if (!data) {
		throw(string("Failed to obtain iterator"));
	}
	return data->children.begin();
}

map<string, NLS::Node>::iterator NLS::Node::End() {
	if (!data) {
		throw(string("Failed to obtain iterator"));
	}
	return data->children.end();
}

NLS::Node::operator bool() {
	return (bool)data;
}

NLS::Node::operator string() {
	if (!data) {
		return string();
	} else if (data->has&0x1) {
		return data->stringValue;
	} else if (data->has&0x2) {
		data->stringValue = tostring(data->floatValue);
		data->has |= 0x2;
		return data->stringValue;
	} else if (data->has&0x4) {
		data->stringValue = tostring(data->intValue);
		data->has |= 0x4;
		return data->stringValue;
	} else {
		return string();
	}
}

NLS::Node::operator double() {
	if (!data) {
		return 0;
	} else if (data->has&0x2) {
		return data->floatValue;
	} else if (data->has&0x1) {
		data->floatValue = todouble(data->stringValue);
		data->has |= 0x1;
		return data->floatValue;
	} else if (data->has&0x4) {
		data->floatValue = (double)data->intValue;
		data->has |= 0x4;
		return data->floatValue;
	} else {
		return 0;
	}
}

NLS::Node::operator int() {
	if (!data) {
		return 0;
	} else if (data->has&0x4) {
		return data->intValue;
	} else if (data->has&0x1) {
		data->intValue = toint(data->stringValue);
		data->has |= 0x1;
		return data->intValue;
	} else if (data->has&0x2) {
		data->intValue = (int)data->floatValue;
		data->has |= 0x2;
		return data->intValue;
	} else {
		return 0;
	}
}

NLS::Node& NLS::Node::operator= (const string& v) {
	if (!data) {
		throw(string("You fail at loading"));
	}
	data->stringValue = v;
	data->has |= 0x1;
	return *this;
}

NLS::Node& NLS::Node::operator= (const double& v) {
	if (!data) {
		throw(string("You fail at loading"));
	}
	data->floatValue = v;
	data->has |= 0x2;
	return *this;
}

NLS::Node& NLS::Node::operator= (const int& v) {
	if (!data) {
		throw(string("You fail at loading"));
	}
	data->intValue = v;
	data->has |= 0x4;
	return *this;
}

NLS::NodeData::NodeData() {
	image = 0;
	has = 0;
}