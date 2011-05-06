///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////

namespace wz {
	class node;
	class node_data;
	class node {//This class is pretty much all you need to know here
	public:
		node();
		~node();
		wz::node& operator [] (string key);//This is how you access nodes
		wz::node& operator [] (const char* key);//This is an extra overload to catch certain cases
		wz::node& g (string key);
		map <string, wz::node>::iterator begin();//These are for if you want to iterate
		map <string, wz::node>::iterator end();
		operator bool();// Used for if blocks
		operator double();//Just do (double)some_node to get its value as a double
		operator int();//ditto for these
		operator string();
		operator Sprite();
		operator sound();
		void operator = (double value);//You'll never need to use these
		void operator = (int value);
		void operator = (string value);
		void operator = (Sprite value);
		void operator = (sound value);
		void operator = (wz::node value);//Nor this
		wz::node_data* data;
	};
	class node_data {//You'll never use this, ever, so don't touch this
	public:
		node_data();
		double realValue;
		string stringValue;
		Sprite spriteValue;
		sound soundValue;
		char has;
		string name;
		wz::node parent;
		map <std::string, wz::node> children;
		WZLib_Image* image;
		bool loaded;
	};
	class top_node {//This is the top node containing all the wz data
	public://Read up on node for more info, they are similar
		top_node();
		~top_node();
		map <std::string, wz::node> children;
		wz::node& operator [] (string key);
		wz::node& g (string key);
		map <std::string, wz::node>::iterator begin();
		map <std::string, wz::node>::iterator end();
	};
	extern top_node top;//And this is the node you will access everything from. wz::top["hai"]
	extern wz::node empty_node;
	bool init(string path);//You'll never need this
	bool load(string name);//Nor this
	bool parse_dir(WZLib_Directory* dir, wz::node& cur_node);//Nor any of these
	bool parse_dir_beta(WZLib_Directory* dir);
	bool parse_img(WZLib_Image* dir, wz::node& cur_node);
	bool parse_prop(WZLib_Property* dir, wz::node& cur_node, int i);
	bool parse_obj(WZLib_Object* dir, wz::node& cur_node, int i);
	bool parse_sub(WZLib_SubProperty* dir, wz::node& cur_node);

	bool parse_canvas(WZLib_CanvasProperty* dir, wz::node& cur_node);
	bool parse_convex(WZLib_ConvexProperty* dir, wz::node& cur_node);
	bool parse_mp3(WZLib_SoundProperty* dir, wz::node& cur_node);

	bool parse_int(WZLib_Property* dir, wz::node& cur_node);
	bool parse_double(WZLib_Property* dir, wz::node& cur_node);
	bool parse_extended(WZLib_Property* dir, wz::node& cur_node);
	bool parse_float(WZLib_Property* dir, wz::node& cur_node);
	bool parse_null(WZLib_Property* dir, wz::node& cur_node, int index);
	bool parse_string(WZLib_Property* dir, wz::node& cur_node);
	bool parse_short(WZLib_Property* dir, wz::node& cur_node);
	bool parse_uol(WZLib_Property* dir, wz::node& cur_node);
	bool parse_vector(WZLib_Property* dir, wz::node& cur_node);//So just don't touch them okay?
};