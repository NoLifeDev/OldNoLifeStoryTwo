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
		map<string,Node> children;
		Node parent;
	private:
		NodeData(const NodeData&);
	};
	namespace WZ {
		extern Node Top;
		//Enumerations
		enum ObjectType {
			TypeUnknown=0,
			TypeFile,
			TypeHeader,
			TypeImage,
			TypeDirectory,
			TypeProperty
		};
		enum PropertyType {
			PropUnknown=0,
			PropPrim=400,
			PropNull=401,
			PropUnsignedShort=402,
			PropCompressedInt=403,
			PropVector=404,
			PropFloat=405,
			PropDouble=406,
			PropString=407,
			PropUOL=408,
			PropSub=500,
			PropCanvas=501,
			PropConvex=502,
			PropPNG=700,
			PropMP3=800
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
		//Other classes
		class Key {
		};
		class Object {
		public:
			uint32_t Size();
			ObjectType type;
			string name;
			bool parsed;
		private:
			Object* parent;
			uint32_t blocksize;
			uint32_t checksum;
			uint32_t offset;
			uint32_t count;
		};
		class Header: public Object {
		public:
			Header(string name, File* file);
		private:
			Header();
			Header(const Header&);
			string ident;
			uint64_t fileSize;
			uint32_t fileStart;
			uint16_t version;
			string copyright;
			uint32_t versionHash;
		};
		class Directory: public Object {
		};
		class File: public Object {
		public:
			ifstream file;
			File(string name);
		private:
			File();
			File(const File&);
		};
		class Image {
		};
		class Property {
			PropertyType type;
		};
		class PrimitiveProperty {
		};
		class SubProperty {
		};
		class CanvasProperty {
		};
		class PNGProperty {
		};
		class SoundProperty {
		};
		class Entry {
		};
		//Functions
		bool Init(string path);
	}
};