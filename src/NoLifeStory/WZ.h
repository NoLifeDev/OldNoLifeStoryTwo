////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	/*
	\class NLS::Node
	\brief Node is used to access the WZ data.
	Node is an extremely useful class which you will be using extensively.
	In order to access the WZ data you start with the top level node:
	NLS::WZ
	From there you use the [] operator to access child nodes
	Node lol = NLS::WZ["somenode"]["SomeOtherNode"]["What fun!"];
	Remember, you can only go one node level per []
	To obtain the value of a node just cast it
	(string)somenode
	(int)somenode
	(Sprite)somenode
	etc.
	You can also assign the value automatically to a variable
	string lol = somenode;
	int foo = somenode;
	Sprite wat = somenode;
	To iterate through child nodes you can use Begin and End
	for (auto it = somenode.Begin(); it != somenode.End(); it++) {
		it->first;//Name of the node
		it->second;//The node itself
	}
	Don't use the assignment operators.
	Those are intended for the wz loading library only.
	If you use them the wz data will no longer be what it used to be.
	data is the only variable member of a Node.
	Its a pointer to the actual data held by the node.
	Unless you know what you're doing and there is no suitable function alternative,
	don't touch data!
	*/
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
		uint8_t format2;
		int32_t length;
		uint32_t offset;
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
};