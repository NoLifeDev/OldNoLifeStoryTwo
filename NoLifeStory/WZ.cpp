////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"
#include "Keys.h"

set<NLS::WZ::File*> Files;
string Path;
NLS::Node NLS::WZ::Top;
NLS::Node NLS::WZ::Empty;

#pragma region File Reading Stuff
template <class t>
inline void Read(ifstream& file, t& v) {
	file.read((char*)&v, sizeof(v));
}

inline int32_t ReadCInt(ifstream& file) {
	int8_t a;
	Read(file, a);
	if (a != -128) {
		return a;
	} else {
		int32_t b;
		Read(file, b);
		return b;
	}
}

inline uint32_t ReadOffset(NLS::WZ::File* file) {
	uint32_t p = file->file.tellg();
	p = (p-file->head->fileStart)^0xFFFFFFFF;
	p *= file->head->versionHash;
	p -= 0x581C3F6D;
	p = (p<<(p&0x1F))|(p>>(32-p&0x1F));
	uint32_t more;
	Read(file->file, more);
	p ^= more;
	p += file->head->fileStart*2;
	return p;
}

inline string ReadEncString(ifstream& file) {
	int8_t slen;
	Read(file, slen);
	if (slen == 0) {
		return string();
	} else if (slen > 0) {
		uint32_t len;
		if (slen == 0x7F) {
			Read(file, len);
		} else {
			len = slen;
		}
		if (len <= 0) {
			return string();
		}
		string s(len, '\0');
		uint16_t mask = 0xAAAA;
		for (int i = 0; i < len; i++) {
			uint16_t enc;
			Read(file, enc);
			enc ^= mask;
			enc ^= (WZKey[i*2+1]<<8)+WZKey[i*2];
			mask++;
			s[i] = enc;
		}
		return s;
	} else {
		uint32_t len;
		if (slen == -128) {
			Read(file, len);
		} else {
			len = -slen;
		}
		if (len <= 0) {
			return string();
		}
		string s(len, '\0');
		uint16_t mask = 0xAA;
		for (int i = 0; i < len; i++) {
			uint8_t enc;
			Read(file, enc);
			enc ^= mask;
			enc ^= WZKey[i];
			mask++;
			s[i] = enc;
		}
		return s;
	}
}

string ReadString(ifstream& file, uint32_t offset) {
	uint8_t a;
	Read(file, a);
	switch (a) {
	case 0x00:
	case 0x73:
		return ReadEncString(file);
	case 0x01:
	case 0x1B:
		{
			int32_t off;
			Read(file, off);
			offset += off;
			uint32_t p = file.tellg();
			file.seekg(offset);
			string s = ReadEncString(file);
			file.seekg(p);
			return s;
		}
	default:
		return string();
	}
}
#pragma endregion

#pragma region Parsing Stuff
bool NLS::WZ::Init(string path) {
	Path = path;
	Top.data = new NodeData();
	new File("Base");
	new File("Character");
	new File("Effect");
	new File("Etc");
	new File("Item");
	new File("Map");
	new File("Mob");
	new File("Morph");
	new File("Npc");
	new File("Quest");
	new File("Reactor");
	new File("Skill");
	new File("Sound");
	new File("String");
	new File("TamingMob");
	new File("UI");
	return true;
}

NLS::WZ::File::File(string name) {
	string filename = Path+name+".wz";
	file.open(filename, file.in|file.binary);
	if (!file.is_open()) {
		cerr << "ERROR: Failed to load WZ file: " << filename << endl;
		throw(273);
	}
	Files.insert(this);
	head = new Header(this);
	for (int i = 1; i < 0x7F; i++) {
		uint32_t vh = Hash(head->version, i);
		if (vh) {
			head->versionHash = vh;
			version = i;
		}
	}
	new Directory(this, Top.g(name));
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

NLS::WZ::Header::Header(File* file) {
	char s1[4];
	file->file.read(s1, 4);
	ident.assign(s1, 4);
	Read(file->file, fileSize);
	Read(file->file, fileStart);
	file->file >> copyright;
	file->file.seekg(fileStart);
	Read(file->file, version);
}

NLS::WZ::Directory::Directory(File* file, Node n) {
	int32_t count = ReadCInt(file->file);
	for (int i = 0; i < count; i++) {
		string name;
		uint8_t type;
		Read(file->file, type);
		if (type == 1) {
			char garbage[6];
			file->file.read(garbage, 10);
			continue;
		} else if (type == 2) {
			int32_t s;
			Read(file->file, s);
			uint32_t p = file->file.tellg();
			file->file.seekg(file->head->fileStart+s);
			Read(file->file, type);
			name = ReadEncString(file->file);
			file->file.seekg(p);
		} else if (type == 3) {
			name = ReadEncString(file->file);
		} else if (type == 4) {
			name = ReadEncString(file->file);
		} else {
			continue;
		}
		int32_t fsize = ReadCInt(file->file);
		int32_t checksum = ReadCInt(file->file);
		uint32_t offset = ReadOffset(file);
		if (type == 3) {
			uint32_t p = file->file.tellg();
			file->file.seekg(offset);
			new Directory(file, n.g(name));
			file->file.seekg(p);
		} else {
			name.erase(name.size()-4);
			new Image(file, n.g(name), offset);
		}
	}
	delete this;
}

NLS::WZ::Image::Image(File* file, Node n, uint32_t offset) {
	this->n = n;
	this->offset = offset;
	this->file = file;
}

void NLS::WZ::Image::Parse() {
	uint32_t p = file->file.tellg();
	file->file.seekg(offset);
	uint8_t a;
	Read(file->file, a);
	if (a != 0x73) {
		cerr << "ERROR: Parsing fail" << endl;
		throw(273);
	}
	string s = ReadEncString(file->file);
	if (s != "Property") {
		cerr << "ERROR: Parsing fail" << endl;
		throw(273);
	}
	uint16_t b;
	Read(file->file, b);
	if (b != 0) {
		cerr << "ERROR: Parsing fail" << endl;
		throw(273);
	}
	new SubProperty(file, n, offset);
	file->file.seekg(p);
	//Resolve the UOLs
	delete this;
}

NLS::WZ::SubProperty::SubProperty(File* file, Node n, uint32_t offset) {
	int32_t count = ReadCInt(file->file);
	for (int i = 0; i < count; i++) {
		string name = ReadString(file->file, offset);
		uint8_t a;
		Read(file->file, a);
		switch (a) {
		case 0x00:
			n.g(name);
			break;
		case 0x0B:
		case 0x02:
			{
				uint16_t v;
				Read(file->file, v);
				n.g(name) = v;
				break;
			}
		case 0x03:
			n.g(name) = ReadCInt(file->file);
			break;
		case 0x04:
			{
				uint8_t type;
				Read(file->file, type);
				if (type == 0x80) {
					float v;
					Read(file->file, v);
					n.g(name) = v;
				}
				break;
			}
		case 0x05:
			{
				double v;
				Read(file->file, v);
				n.g(name) = v;
				break;
			}
		case 0x08:
			n.g(name) = ReadString(file->file, offset);
			break;
		case 0x09:
			{
				uint32_t temp;
				Read(file->file, temp);
				uint32_t eob = temp+file->file.tellg();
				new ExtendedProperty(file, n.g(name), offset, eob);
				file->file.seekg(eob);
				break;
			}
		default:
			cerr << "ERROR: Wat?" << endl;
			throw(273);
		}
	}
	delete this;
}

NLS::WZ::ExtendedProperty::ExtendedProperty(File* file, Node n, uint32_t offset, uint32_t eob) {
	//Magic
}
#pragma endregion

#pragma region Node Stuff
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
		if (data->image) {
			data->image->Parse();
			data->image = 0;
		}
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
	assert(data);
	Node& n = data->children[key];
	n.data = new NodeData();
	n.data->parent = *this;
	return n;
}

map<string, NLS::Node>::iterator NLS::Node::Begin() {
	assert(data);
	return data->children.begin();
}

map<string, NLS::Node>::iterator NLS::Node::End() {
	assert(data);
	return data->children.end();
}

NLS::Node::operator bool() {
	return (bool)data;
}

NLS::Node::operator string() {
	assert(data);
	return data->stringValue;
}

NLS::Node::operator double() {
	assert(data);
	return data->floatValue;
}

NLS::Node::operator int() {
	assert(data);
	return data->intValue;
}

NLS::Node& NLS::Node::operator= (const string& v) {
	assert(data);
	data->intValue = toint(v);
	data->floatValue = todouble(v);
	data->stringValue = v;
	return *this;
}

NLS::Node& NLS::Node::operator= (const double& v) {
	assert(data);
	data->intValue = v;
	data->floatValue = v;
	data->stringValue = tostring(v);
	return *this;
}

NLS::Node& NLS::Node::operator= (const int& v) {
	assert(data);
	data->intValue = v;
	data->floatValue = v;
	data->stringValue = tostring(v);
	return *this;
}

NLS::NodeData::NodeData() {
	image = 0;
	intValue = 0;
	floatValue = 0;
}
#pragma endregion