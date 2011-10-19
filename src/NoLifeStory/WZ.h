////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	class Node {
	public:
		Node();
		Node(const Node&);
		Node& operator= (const Node&);
		Node operator[] (const string&);
		Node operator[] (const char[]);
		Node operator[] (const int&);
		Node g(const string&);
		map<string, Node>::iterator begin();
		map<string, Node>::iterator end();
		string Name();
		void Name(const string&);
		Node Parent();
		void Assign(const Node&);
		operator bool();
		operator string();
		operator double();
		operator int();
		operator Sprite();
		operator Sound();
		void Set(const string&);
		void Set(const double&);
		void Set(const int&);
		void Set(class Img*);
		void Set(const class Sound&);
		void Set(const class Sprite&);
	private:
		class NodeData* data;
	};
	class PNGProperty {
	public:
		PNGProperty(ifstream* file, Node n);
		void Parse();
	private:
		ifstream* file;
		Sprite sprite;
		int32_t format;
		int32_t length;
		uint32_t offset;
		uint8_t format2;
	};
	class SoundProperty {
	public:
		SoundProperty(ifstream* file, Node n);
		uint32_t GetStream(bool loop);
	private:
		int32_t len;
		uint8_t* data;
		uint32_t offset;
		ifstream* file;
	};
	class Img {
	public:
		Img(ifstream* file, Node n, uint32_t offset);
		void Parse();
	private:
		Node n;
		uint32_t offset;
		ifstream* file;
	};
	extern Node WZ;
	void InitWZ(const path& wzpath);
}
