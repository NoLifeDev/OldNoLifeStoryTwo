////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	//Node classes
	class Node {
	public:
		Node();
		Node(const Node&);
		Node& operator= (const Node&);
		Node& operator[] (const string&);
		Node& operator[] (const char[]);
		Node& g(const string&);
		map<string, Node>::iterator Begin();
		map<string, Node>::iterator End();
		operator bool();
		operator string();
		operator double();
		operator int();
		Node& operator= (const string&);
		Node& operator= (const double&);
		Node& operator= (const int&);
		class NodeData* data;
	};
	namespace WZ {
		extern Node Top;
		extern Node Empty;
		enum PropertyType {
			PropUnknown = 0,
			PropPrim = 400,
			PropNull = 401,
			PropUnsignedShort = 402,
			PropCompressedInt = 403,
			PropVector = 404,
			PropFloat = 405,
			PropDouble = 406,
			PropString = 407,
			PropUOL = 408,
			PropSub = 500,
			PropCanvas = 501,
			PropConvex = 502,
			PropPNG = 700,
			PropMP3 = 800
		};
		class Header;
		class Directory;
		class File;
		class Image;
		class PrimitiveProperty;
		class SubProperty;
		class CanvasProperty;
		class PNGProperty;
		class SoundProperty;
		//And now lets define them somehow
		class Header {
		public:
			Header(File* file);
			string ident;
			uint64_t fileSize;
			uint32_t fileStart;
			uint16_t version;
			string copyright;
			uint32_t versionHash;
		};
		class Directory {
		public:
			Directory(File* file, Node n);
			File* file;
		};
		class File {
		public:
			File(string name);
			ifstream file;
			uint32_t Hash(uint16_t enc, uint16_t real);
			uint16_t version;
			Header* head;
		};
		class Image {
		public:
			Image(File* file, Node n, uint32_t offset);
			void Parse();
			Node n;
			string name;
			uint32_t offset;
			File* file;
		};
		class SubProperty {
		public:
			SubProperty(File* file, Node n, uint32_t offset);
		};
		class ExtendedProperty {
		public:
			ExtendedProperty(File* file, Node n, uint32_t offset, uint32_t eob);
		};
		//Functions
		bool Init(string path);
	}
	class NodeData {
	public:
		NodeData();
		string stringValue;
		double floatValue;
		int intValue;
		Node parent;
		string name;
		map <string, Node> children;
		WZ::Image* image;
	private:
		NodeData(const NodeData&);
		NodeData& operator= (const NodeData&);
	};
};