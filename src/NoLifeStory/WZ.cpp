////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

path WZPath;
NLS::Node NLS::WZ;
vector<path> NLS::Paths;
uint8_t *WZKey = 0;
int16_t EncVersion;
uint16_t NLS::Version = 0;
uint32_t VersionHash;

#pragma region File reading stuff
template <class T>
inline T Read(ifstream* file) {
	T v;
	file->read((char*)&v, sizeof(v));
	return v;
}

inline int32_t ReadCInt(ifstream* file) {
	int8_t a = Read<int8_t>(file);
	if (a != -128) {
		return a;
	} else {
		int32_t b = Read<int32_t>(file);
		return b;
	}
}

inline string ReadEncString(ifstream* file) {
	int8_t slen = Read<int8_t>(file);
	if (slen == 0) {
		return string();
	} else if (slen > 0) {
		int32_t len;
		if (slen == 127) {
			len = Read<int32_t>(file);
		} else {
			len = slen;
		}
		if (len <= 0) {
			return string();
		}
		uint16_t mask = 0xAAAA;
		static wchar_t ws[0x10000];
		file->read((char*)ws, 2*len);
		for (int i = 0; i < len; i++) {
			ws[i] ^= mask;
			ws[i] ^= *(uint16_t*)(WZKey+2*i);
			mask++;
		}
		ws[len] = '\0';
		static char s[0x10000];
		sf::Utf8::FromWide(ws, ws+len+1, s);
		cout << "Wide: " << s << endl;
		return s;
	} else {
		int32_t len;
		if (slen == -128) {
			len = Read<int32_t>(file);
		} else {
			len = -slen;
		}
		if (len <= 0) {
			return string();
		}
		uint8_t mask = 0xAA;
		static char as[0x10000];
		file->read((char*)as, len);
		for (int i = 0; i < len; i++) {
			as[i] ^= mask;
			as[i] ^= WZKey[i];
			mask++;
		}
		as[len] = '\0';
		static char s[0x10000];
		sf::Utf8::FromAnsi(as, as+len+1, s, locale::classic());
		return s;
	}
}

inline void ReadEncFast(ifstream* file) {
	int8_t slen = Read<int8_t>(file);
	if (slen == 0) {return;}
	if (slen > 0) {
		int32_t len;
		if (slen == 127) {
			len = Read<int32_t>(file);
		} else {
			len = slen;
		}
		if (len <= 0) {return;}
		file->ignore(len*2);
	} else {
		int32_t len;
		if (slen == -128) {
			len = Read<int32_t>(file);
		} else {
			len = -slen;
		}
		if (len <= 0) {return;}
		file->ignore(len);
	}
}

inline string ReadString(ifstream* file, uint32_t offset) {
	uint8_t a = Read<uint8_t>(file);
	switch (a) {
	case 0x00:
	case 0x73:
		return ReadEncString(file);
	case 0x01:
	case 0x1B:
		{
			int32_t off = Read<int32_t>(file);
			offset += off;
			uint32_t p = file->tellg();
			file->seekg(offset);
			string s = ReadEncString(file);
			file->seekg(p);
			return s;
		}
	default:
		return string();
	}
}

inline string ReadStringOffset(ifstream* file, uint32_t offset) {
	uint32_t p = file->tellg();
	file->seekg(offset);
	string s = ReadEncString(file);
	file->seekg(p);
	return s;
}
#pragma endregion

#pragma region WZ Parsing
void NLS::InitWZ() {
	function <uint32_t(ifstream*, uint32_t)> ReadOffset;
	function <void(Node)> File;
	function <void(Node, ifstream*, uint32_t)> Directory;
	ReadOffset = [](ifstream* file, uint32_t fileStart)->uint32_t {
		uint32_t p = file->tellg();
		p = (p-fileStart)^0xFFFFFFFF;
		p *= VersionHash;
		p -= OffsetKey;
		p = (p<<(p&0x1F))|(p>>(32-p&0x1F));
		uint32_t more = Read<uint32_t>(file);
		p ^= more;
		p += fileStart*2;
		return p;
	};
	File = [&ReadOffset, &Directory](Node n) {
		path filename = WZPath/path(n.Name()+".wz");
		if (!exists(filename)) {
			cerr << "WZ file does not exist: " << filename << endl;
		}
		ifstream *file = new ifstream(filename, ios::in|ios::binary);
		if (!file->is_open()) {
			cerr << "Failed to load " << filename << endl;
			return;//Don't throw an error because of Nexon's stupid ExcelReport crap
		}
		char ident[4];
		file->read(ident, 4);
		if (string(ident, 4) != "PKG1") {
			cerr << "Invalid ident header: " << string(ident) << endl;
			throw(273);
		}
		uint64_t fileSize = Read<uint64_t>(file);
		uint32_t fileStart = Read<uint32_t>(file);
		string copyright;
		getline(*file, copyright, '\0');
		file->seekg(fileStart);
		if (!Version) {
			cout << string(copyright) << endl;
			EncVersion = Read<int16_t>(file);
			int32_t count = ReadCInt(file);
			uint32_t c = 0;
			for (int k = 0; k < count; k++) {
				uint8_t type = Read<uint8_t>(file);
				if (type == 3) {
					ReadEncFast(file);
					ReadCInt(file);
					ReadCInt(file);
					Read<uint32_t>(file);
					continue;
				} else if (type == 4) {
					ReadEncFast(file);
					ReadCInt(file);
					ReadCInt(file);
					c = file->tellg();
					break;
				} else {
					cerr << "Malformed WZ structure" << endl;
					throw(273);
				}
			}
			if (c == 0) {
				cerr << "Unable to find a top level .img for hash verification" << endl;
				throw(273);
			}
			bool success = false;
			for (uint8_t j = 0; j < 3 and !success; j++) {
				WZKey = WZKeys[j];
				for (Version = 0; Version < 512; Version++) {
					char s[4];
					int l = sprintf(s, "%i", Version);
					VersionHash = 0;
					for (int i = 0; i < l; i++) {
						VersionHash = 32*VersionHash+s[i]+1;
					}
					uint32_t result = 0xFF^(VersionHash>>24)^(VersionHash<<8>>24)^(VersionHash<<16>>24)^(VersionHash<<24>>24);
					if (result == EncVersion) {
						file->clear();
						file->seekg(c);
						uint32_t offset = ReadOffset(file, fileStart);
						if (offset > fileSize) {
							continue;
						}
						file->seekg(offset);
						uint8_t a = Read<uint8_t>(file);
						if(a != 0x73) {
							continue;
						}
						string ss = ReadEncString(file);
						if (ss != "Property") {
							continue;
						}
						cout << "Detected WZ version: " << Version << endl;
						success = true;
						break;
					}
				}
			}
			if (!success) {
				cerr << "Unable to determine WZ version" << endl;
				throw(273);
			}
			file->seekg(fileStart+2);
		} else {
			int16_t eversion = Read<int16_t>(file);
			if (eversion != EncVersion) {
				cerr << "Version of WZ file does not match existing files" << endl;
				throw(273);
			}
		}
		if (ReadCInt(file) == 0) {
			cerr << "Empty WZ file: " << filename << endl;
			return;
		}
		file->seekg(fileStart+2);
		Directory(n, file, fileStart);
	};
	Directory = [&File, &ReadOffset, &Directory](Node n, ifstream* file, uint32_t fileStart) {
		int32_t count = ReadCInt(file);
		if (count == 0) {
			File(n);
			return;
		}
		set<pair<string, uint32_t>> dirs;
		for (int i = 0; i < count; i++) {
			string name;
			uint8_t type = Read<uint8_t>(file);
			if (type == 1) {
				file->seekg(10, ios::cur);
				continue;
			} else if (type == 2) {
				int32_t s = Read<int32_t>(file);
				uint32_t p = file->tellg();
				file->seekg(fileStart+s);
				type = Read<uint8_t>(file);
				name = ReadEncString(file);
				file->seekg(p);
			} else if (type == 3) {
				name = ReadEncString(file);
			} else if (type == 4) {
				name = ReadEncString(file);
			} else {
				cerr << "Unknown node type" << endl;
				throw(273);
			}
			int32_t fsize = ReadCInt(file);
			int32_t checksum = ReadCInt(file);
			uint32_t offset = ReadOffset(file, fileStart);
			if (type == 3) {
				dirs.insert(pair<string, uint32_t>(name, offset));
			} else if (type == 4) {
				name.erase(name.size()-4, 4);
				new Img(file, n.g(name), offset);
			} else {
				cerr << "Unknown node type" << endl;
				throw(273);
			}
		}
		for (auto it = dirs.begin(); it != dirs.end(); it++) {
			file->seekg(it->second);
			Directory(n.g(it->first), file, fileStart);
		}
	};
	memset(WZKeys[0], 0, 0x10000);
	for (int i = 0; i < Paths.size(); i++) {
		WZPath = Paths[i];
		if (exists(WZPath/path("Data.wz"))) {
			cout << "Loading beta WZ file structure from " << WZPath << endl;
			WZ.Name("Data");
			File(WZ);
			return;
		}
		if (exists(WZPath/path("Base.wz"))) {
			cout << "Loading standard WZ file structure from " << WZPath << endl;
			WZ.Name("Base");
			File(WZ);
			return;
		}
	}
	cerr << "I CAN'T FIND YOUR WZ FILES YOU NUB" << endl;
	throw(273);
}

NLS::Img::Img(ifstream* file, Node n, uint32_t offset) {
	this->n = n;
	n.Set(this);
	this->offset = offset;
	this->file = file;
}

void NLS::Img::Parse() {
	function <void(ifstream*, Node, uint32_t)> SubProperty;
	function <void(ifstream*, Node, uint32_t)> ExtendedProperty;
	function <void(Node)> Resolve;
	SubProperty = [&ExtendedProperty](ifstream* file, Node n, uint32_t offset) {
		int32_t count = ReadCInt(file);
		for (int i = 0; i < count; i++) {
			string name = ReadString(file, offset);
			uint8_t a = Read<uint8_t>(file);
			switch (a) {
			case 0x00:
				n.g(name).Set(i);
				break;
			case 0x0B:
			case 0x02:
				n.g(name).Set(Read<uint16_t>(file));
				break;
			case 0x03:
				n.g(name).Set(ReadCInt(file));
				break;
			case 0x04:
				if (Read<uint8_t>(file) == 0x80) {
					n.g(name).Set(Read<float>(file));
				}
				break;
			case 0x05:
				n.g(name).Set(Read<double>(file));
				break;
			case 0x08:
				n.g(name).Set(ReadString(file, offset));
				break;
			case 0x09:
				{
					uint32_t temp = Read<uint32_t>(file);
					temp += file->tellg();
					ExtendedProperty(file, n.g(name), offset);
					file->seekg(temp);
					break;
				}
			default:
				cerr << "Unknown Property type" << endl;
				throw(273);
			}
		}
	};
	ExtendedProperty = [&SubProperty, &ExtendedProperty](ifstream* file, Node n, uint32_t offset) {
		string name;
		uint8_t a = Read<uint8_t>(file);
		if (a == 0x1B) {
			int32_t inc = Read<int32_t>(file);
			uint32_t pos = offset+inc;
			uint32_t p = file->tellg();
			file->seekg(pos);
			name = ReadEncString(file);
			file->seekg(p);
		} else {
			name = ReadEncString(file);
		}
		if (name == "Property") {
			file->seekg(2, ios::cur);
			SubProperty(file, n, offset);
		} else if (name == "Canvas") {
			file->seekg(1, ios::cur);
			uint8_t b = Read<uint8_t>(file);
			if (b == 1) {
				file->seekg(2, ios::cur);
				SubProperty(file, n, offset);
			}
			new PNGProperty(file, n);
		} else if (name == "Shape2D#Vector2D") {
			n.g("x").Set(ReadCInt(file));
			n.g("y").Set(ReadCInt(file));
		} else if (name == "Shape2D#Convex2D") {
			int32_t ec = ReadCInt(file);
			for (int i = 0; i < ec; i++) {
				ExtendedProperty(file, n.g(tostring(ec)), offset);
			}
		} else if (name == "Sound_DX8") {
			new SoundProperty(file, n);
		} else if (name == "UOL") {
			file->seekg(1, ios::cur);
			uint8_t b = Read<uint8_t>(file);
			switch (b) {
			case 0:
				n.g(name).Set(ReadEncString(file));
				break;
			case 1:
				{
					uint32_t off = Read<uint32_t>(file);
					n.g(name).Set(ReadStringOffset(file, offset+off));
					break;
				}
			default:
				cerr << "Unknown UOL type" << endl;
				throw(273);
			}
		} else {
			cerr << "Unknown ExtendedProperty type" << endl;
			throw(273);
		};
	};
	Resolve = [&Resolve](Node n) {
		if (n["UOL"]) {
			string s = n["UOL"];
			vector <string> parts = split(s, '/');
			Node nn = n[".."];
			for (auto it = parts.begin(); it != parts.end(); it++) {
				if (!nn) {
					break;
				}
				nn = nn[*it];
			}
			if (nn) {
				n.Assign(nn);
			}
		} else {
			for (auto it = n.begin(); it != n.end(); it++) {
				if (it->second) {
					Resolve(it->second);
				}
			}
		}
	};
	cout << "Parsing " << n.Name() << ".img" << endl;
	file->seekg(offset);
	uint8_t a = Read<uint8_t>(file);
	if (a != 0x73) {
		cerr << "Invalid WZ image!" << endl;
		throw(273);
	}
	string s = ReadEncString(file);
	if (s != "Property") {
		cerr << "Invalid WZ image!" << endl;
		throw(273);
	}
	uint16_t b = Read<uint16_t>(file);
	if (b != 0) {
		cerr << "Invalid WZ image!" << endl;
		throw(273);
	}
	SubProperty(file, n, offset);
	Resolve(n);
	delete this;
}

NLS::PNGProperty::PNGProperty(ifstream* file, Node n) {
	this->file = file;
	sprite.data = new SpriteData;
	sprite.data->loaded = false;
	sprite.data->width = ReadCInt(file);
	sprite.data->height = ReadCInt(file);
	sprite.data->png = this;
	sprite.data->originx = n["origin"]["x"];
	sprite.data->originy = n["origin"]["y"];
	n.Set(sprite);
	format = ReadCInt(file);
	format2 = Read<uint8_t>(file);
	file->seekg(4, ios::cur);
	length = Read<int32_t>(file);
	if (length <= 0) {
		cerr << "What sort of shit is this?" << endl;
		throw(273);
	}
	offset = file->tellg();
	offset++;
}

void NLS::PNGProperty::Parse() {
	static uint8_t Buf1[0x1000000];
	static uint8_t Buf2[0x1000000];
	uint8_t* Src = Buf1;
	uint8_t* Dest = Buf2;
	auto Swap = [&]() {
		swap(Src, Dest);
	};
	auto DecompressBlock = [&](uint32_t len) {
		static z_stream strm;
		strm.next_in = Src;
		strm.avail_in = len;
		strm.opaque = nullptr;
		strm.zfree = nullptr;
		strm.zalloc = nullptr;
		inflateInit(&strm);
		strm.next_out = Dest;
		strm.avail_out = 0x1000000;
		int err = inflate(&strm, Z_FINISH);
		if (err != Z_BUF_ERROR) {
			cerr << "Unexpected error from zlib: " << err << endl;
		}
		inflateEnd(&strm);
		Swap();
	};
	auto Decompress = [&](uint32_t len) {
		if (Src[0] == 0x78 and Src[1] == 0x9C) {
			DecompressBlock(len);
		} else {
			int i, p;
			for (p = 0, i = 0; i < len-1;) {
				uint32_t blen = *(uint32_t*)&Src[i];
				i += 4;
				for (int j = 0; j < blen; j++) {
					Dest[p+j] = Src[i+j]^WZKey[j];
				}
				i += blen;
				p += blen;
			}
			Swap();
			DecompressBlock(p);
		}
	};
	file->seekg(offset);
	file->read((char*)Dest, length);
	Swap();
	int32_t f = format+format2;
	glGenTextures(1, &sprite.data->texture);
	glBindTexture(GL_TEXTURE_2D, sprite.data->texture);
	GLsizei ww = sprite.data->width;
	GLsizei hh = sprite.data->height;
	GLsizei w = ww;
	GLsizei h = hh;
	if (!Graphics::NPOT) {
		w = pot(w);
		h = pot(h);
	}
	sprite.data->fw = w;
	sprite.data->fh = h;
	auto Resize = [&](int f) {
		memset(Dest, 0, w*h*f);
		for (int i = 0; i < hh; i++) {
			memcpy(&Dest[i*w*f], &Src[i*ww*f], ww*f);
		}
		Swap();
	};
	auto SetTex = [&](GLenum type){glTexImage2D(GL_TEXTURE_2D, 0, 4, w, h, 0, GL_BGRA, type, Src);};
	switch (f) {
	case 1:
		{
			uint32_t len = 2*ww*hh;
			Decompress(length);
			if (ww%2 and Graphics::NPOT or Graphics::Shit) {
				for (uint32_t i = 0; i < len; i++) {
					Dest[i*2] = (Src[i]&0x0F)*0x11;
					Dest[i*2+1] = ((Src[i]&0xF0)>>4)*0x11;
				}
				Swap();
				if (!Graphics::NPOT) {
					Resize(4);
				}
				SetTex(GL_UNSIGNED_BYTE);
			} else {
				if (!Graphics::NPOT) {
					Resize(2);
				}
				SetTex(GL_UNSIGNED_SHORT_4_4_4_4_REV);
			}
			break;
		}
	case 2:
		{
			Decompress(length);
			if (!Graphics::NPOT) {
				Resize(4);
			}
			SetTex(GL_UNSIGNED_BYTE);
			break;
		}
	case 513:
		{
			Decompress(length);
			if (!Graphics::NPOT) {
				Resize(2);
			}
			SetTex(GL_UNSIGNED_SHORT_5_6_5_REV);
			break;
		}
	case 517:
		{
			if (pot(ww) != ww or pot(hh) != hh) {
				cerr << "Non-square type 517 sprite found" << endl;
				throw(273);
			}
			w >>= 4;
			h >>= 4;
			Decompress(length);
			SetTex(GL_UNSIGNED_SHORT_5_6_5_REV);
			break;
		}
	default:
		cerr << "Unknown sprite format " << f << endl;
		throw(273);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	sprite.data->loaded = true;
}

NLS::SoundProperty::SoundProperty(ifstream* file, Node n) {
	this->file = file;
	file->seekg(1, ios::cur);
	len = ReadCInt(file);
	ReadCInt(file);
	offset = file->tellg();
	offset += 82;
	data = 0;
	n.Set(Sound(this));
}

uint32_t NLS::SoundProperty::GetStream(bool loop) {
	if (!data) {
		file->seekg(offset);
		data = new uint8_t[len];
		file->read((char*)data, len);
	}
	return BASS_StreamCreateFile(true, data, 0, len, BASS_SAMPLE_FLOAT|(loop?BASS_SAMPLE_LOOP:0));
}
#pragma endregion

#pragma region Node Stuff
class NLS::NodeData {
public:
	NodeData() {
		image = 0;
		intValue = 0;
		floatValue = 0;
	}
	string stringValue;
	double floatValue;
	int intValue;
	Sprite sprite;
	Sound sound;
	Node parent;
	string name;
	Img* image;
	map <string, Node> children;
private:
	NodeData(const NodeData&);
	NodeData& operator= (const NodeData&);
};

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

NLS::Node NLS::Node::operator[] (const string& key) {
	if (!data) {
		return Node();
	}
	if (data->image) {
		Img* img = data->image;;
		data->image = nullptr;
		img->Parse();
	}
	if (key == "..") {
		return data->parent;
	}
	if (key == ".") {
		return *this;
	}
	auto n = data->children.find(key);
	if (n == data->children.end()) {
		return Node();
	}
	return n->second;
}

NLS::Node NLS::Node::operator[] (const char key[]) {
	return (*this)[string(key)];
}

NLS::Node NLS::Node::operator[] (const int& key) {
	return (*this)[tostring(key)];
}
NLS::Node NLS::Node::operator[] (const Node& key) {
	return (*this)[(string)key];
}

NLS::Node NLS::Node::g(const string& key) {
	assert(data);
	Node& n = data->children[key];
	n.data = new NodeData();
	n.data->parent = *this;
	n.data->name = key;
	return n;
}

map<string, NLS::Node>::iterator NLS::Node::begin() {
	if (!data) {
		return map<string, NLS::Node>::iterator();
	}
	return data->children.begin();
}

map<string, NLS::Node>::iterator NLS::Node::end() {
	if (!data) {
		return map<string, NLS::Node>::iterator();
	}
	return data->children.end();
}

map<string, NLS::Node>::reverse_iterator NLS::Node::rbegin() {
	if (!data) {
		return map<string, NLS::Node>::reverse_iterator();
	}
	return data->children.rbegin();
}

map<string, NLS::Node>::reverse_iterator NLS::Node::rend() {
	if (!data) {
		return map<string, NLS::Node>::reverse_iterator();
	}
	return data->children.rend();
}

string NLS::Node::Name() {
	if (!data) {
		return string();
	}
	return data->name;
}

void NLS::Node::Name(const string& s) {
	if (!data) {
		data = new NodeData();
	}
	data->name = s;
}

void NLS::Node::Assign(const Node& other) {
	data->children = other.data->children;
	data->floatValue = other.data->floatValue;
	data->intValue = other.data->intValue;
	data->stringValue = other.data->stringValue;
	data->sprite = other.data->sprite;
	data->image = other.data->image;
}

NLS::Node::operator bool() const {
	return (bool)data;
}

NLS::Node::operator string() const {
	if (!data) {
		return string();
	}
	return data->stringValue;
}

NLS::Node::operator double() const {
	if (!data) {
		return 0;
	}
	return data->floatValue;
}

NLS::Node::operator int() const {
	if (!data) {
		return 0;
	}
	return data->intValue;
}

NLS::Node::operator NLS::Sprite() const {
	if (!data) {
		return Sprite();
	}
	return data->sprite;
}

NLS::Node::operator NLS::Sound() const {
	if (!data) {
		return Sound();
	}
	return data->sound;
}

void NLS::Node::Set(const string& v) {
	data->intValue = toint(v);
	data->floatValue = todouble(v);
	data->stringValue = v;
}

void NLS::Node::Set(const double& v) {
	data->intValue = v;
	data->floatValue = v;
	data->stringValue = tostring(v);
}

void NLS::Node::Set(const int& v) {
	data->intValue = v;
	data->floatValue = v;
	data->stringValue = tostring(v);
}

void NLS::Node::Set(const Sprite& v) {
	data->sprite = v;
}

void NLS::Node::Set(const Sound& v) {
	data->sound = v;
}

void NLS::Node::Set(Img* v) {
	data->image = v;
}
#pragma endregion
