////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	//Node classes
	class Node {
	public:
		class NodeData* data;
	};
	class NodeData {
	public:
		NodeData();
		string stringValue;
		double realValue;
		uint8_t has;
		map <string, Node> children;
		Node parent;
	private:
		NodeData(const NodeData&);
	};
	namespace WZ {
		extern Node Top;
		//Enumerations
		enum ObjectType {
			TypeUnknown = 0,
			TypeFile,
			TypeHeader,
			TypeImage,
			TypeDirectory,
			TypeProperty
		};
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
		class Key;
		class Object;
		class Header;
		class Directory;
		class File;
		class Image;
		class Property;
		class PrimitiveProperty;
		class SubProperty;
		class CanvasProperty;
		class PNGProperty;
		class SoundProperty;
		class Entry;
		//And now lets define them somehow
		class Object {
		public:
			uint32_t Size();
			ObjectType type;
			string name;
			bool parsed;
			Object* parent;
			uint32_t blocksize;
			uint32_t checksum;
			uint32_t offset;
			uint32_t count;
		private:
		};
		class Header: public Object {
		public:
			Header(string name, File* file);
			string ident;
			uint64_t fileSize;
			uint32_t fileStart;
			uint16_t version;
			string copyright;
			uint32_t versionHash;
		private:
			Header();
			Header(const Header&);
		};
		class Directory: public Object {
		};
		class File: public Object {
		public:
			File(string name);
			ifstream file;
			uint32_t Hash(uint16_t enc, uint16_t real);
			uint16_t version;
		private:
			File();
			File(const File&);
		};
		class Property {
		public:
			PropertyType type;
		};
		//Functions
		bool Init(string path);
	}
};