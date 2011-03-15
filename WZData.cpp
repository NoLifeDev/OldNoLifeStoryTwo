///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////
#include "Global.h"

////////////////////////////////////////////////////////////////
// Various functions to load stuff.
// You will only need wz::init and wz::load.
// Ignore the rest
////////////////////////////////////////////////////////////////

string wzpath = "";
bool wz::init(string path) {
	wzpath = path;
	return true;
}
bool wz::load(string name) {
	cout << "Loading " << name << ".wz" << endl;
	WZLib_File* file=WZLib_File_Open((wzpath+"/"+name+".wz").c_str());
	if(WZLib_File_Parse(file)!=ErrorCode::WZLib_Error_NoError){
		cout << "Failed" << endl;
		return false;
	}
	WZLib_Directory* dir = file->_wzDir;
	if(name=="Data"){
		wz::parse_dir_beta(dir);
	} else {
		wz::parse_dir(dir, wz::top.g(name));
	}
	return true;
}

bool wz::parse_dir(WZLib_Directory* dir, wz::node& cur_node) {
	int size = WZLib_Directory_GetSize(dir);
	for(unsigned int i=0;i<size;i++) {
		WZLib_Object* obj = WZLib_Directory_Get_i(dir,i);
		string name = obj->name;
		auto pos = name.find(".img");
		if(pos!=name.npos) {
			name.erase(pos);
		}
		wz::parse_obj(obj, cur_node.g(name), i);
	}
	return true;
}

bool wz::parse_dir_beta(WZLib_Directory* dir) {
	int size = WZLib_Directory_GetSize(dir);
	for(unsigned int i=0;i<size;i++) {
		WZLib_Object* obj = WZLib_Directory_Get_i(dir,i);
		string name = obj->name;
		auto pos = name.find(".img");
		if(pos!=name.npos) {
			name.erase(pos);
		}
		wz::parse_obj(obj,wz::top.g(name),i);
	}
	return true;
}

bool wz::parse_obj(WZLib_Object* dir, wz::node& cur_node, int i) {
	switch(dir->type){
	case WZLib_ObjectType::WZLib_ObjectType_Directory:
		wz::parse_dir((WZLib_Directory*)dir, cur_node);
		break;
	case WZLib_ObjectType::WZLib_ObjectType_File:
		cout << "lolwut?" << endl;
		break;
	case WZLib_ObjectType::WZLib_ObjectType_Header:
		cout << "lolwut?" << endl;
		break;
	case WZLib_ObjectType::WZLib_ObjectType_Image:
		wz::parse_img((WZLib_Image*)dir, cur_node);
		break;
	case WZLib_ObjectType::WZLib_ObjectType_Property:
		wz::parse_prop((WZLib_Property*)dir, cur_node, i);
		break;
	case WZLib_ObjectType::WZLib_ObjectType_Unknown:
		cout << "lolwut?" << endl;
		break;
	}
	return true;
}

bool wz::parse_img(WZLib_Image* dir, wz::node& cur_node) {
	cur_node.data->image = dir;
	return true;
}
bool wz::parse_prop(WZLib_Property* dir, wz::node& cur_node, int i) {
	switch(dir->propType) {
	case WZLib_PropertyType::WZLib_Prop_Canvas:
		wz::parse_canvas((WZLib_CanvasProperty*)dir, cur_node);
		break;
	case WZLib_PropertyType::WZLib_Prop_CompressedInt:
		wz::parse_int(dir, cur_node);
		break;
	case WZLib_PropertyType::WZLib_Prop_Convex:
		wz::parse_convex((WZLib_ConvexProperty*)dir, cur_node);
		break;
	case WZLib_PropertyType::WZLib_Prop_Double:
		wz::parse_double(dir, cur_node);
		break;
	case WZLib_PropertyType::WZLib_Prop_Float:
		wz::parse_float(dir, cur_node);
		break;
	case WZLib_PropertyType::WZLib_Prop_MP3:
		wz::parse_mp3((WZLib_SoundProperty*)dir, cur_node);
		break;
	case WZLib_PropertyType::WZLib_Prop_Null:
		wz::parse_null(dir, cur_node, i);
		break;
	case WZLib_PropertyType::WZLib_Prop_PNG:
		cout << "lolwut!" << endl;
		break;
	case WZLib_PropertyType::WZLib_Prop_Primitive:
		cout << "lolwut!" << endl;
		break;
	case WZLib_PropertyType::WZLib_Prop_String:
		wz::parse_string(dir, cur_node);
		break;
	case WZLib_PropertyType::WZLib_Prop_Sub:
		wz::parse_sub((WZLib_SubProperty*)dir, cur_node);
		break;
	case WZLib_PropertyType::WZLib_Prop_Unknown:
		cout << "lolwut!" << endl;
		break;
	case WZLib_PropertyType::WZLib_Prop_UnsignedShort:
		wz::parse_short(dir, cur_node);
		break;
	case WZLib_PropertyType::WZLib_Prop_UOL:
		wz::parse_uol(dir, cur_node);
		break;
	case WZLib_PropertyType::WZLib_Prop_Vector:
		wz::parse_vector(dir, cur_node);
		break;
	}
	return true;
}

bool wz::parse_sub(WZLib_SubProperty* dir, wz::node& cur_node) {
	int size = WZLib_SubProperty_GetSize(dir);
	for(unsigned int i=0;i<size;i++) {
		WZLib_Property* prop = WZLib_SubProperty_Get_i(dir,i);
		string name = ((WZLib_Object*)prop)->name;
		if(name==cur_node.data->name+".img"){
			wz::parse_prop(prop, cur_node, i);
		} else {
			wz::parse_prop(prop, cur_node.g(name), i);
		}
	}
	return true;
}

bool wz::parse_canvas(WZLib_CanvasProperty* dir, wz::node& cur_node) {
	wz::parse_sub((WZLib_SubProperty*)dir,cur_node);
	cur_node.g("width") = dir->png->width;
	cur_node.g("height") = dir->png->height;
	Sprite newsprite;
	newsprite = dir->png;
	newsprite.width = cur_node["width"];
	newsprite.height = cur_node["height"];
	newsprite.originx = cur_node["origin"]["x"];
	newsprite.originy = cur_node["origin"]["y"];
	newsprite.fwidth = 1;
	while(newsprite.fwidth<newsprite.width) {
		newsprite.fwidth *= 2;
	}
	newsprite.fheight = 1;
	while(newsprite.fheight<newsprite.height) {
		newsprite.fheight *= 2;
	}
	newsprite.twidth = (double)newsprite.width/(double)newsprite.fwidth;
	newsprite.theight = (double)newsprite.height/(double)newsprite.fheight;
	cur_node = newsprite;
	return true;
}
bool wz::parse_int(WZLib_Property* dir, wz::node& cur_node) {
	cur_node = ((WZLib_PrimitiveProperty*)dir)->val.intVal;
	return true;
}
bool wz::parse_convex(WZLib_ConvexProperty* dir, wz::node& cur_node) {
	wz::parse_sub((WZLib_SubProperty*)dir,cur_node);
	return true;
}
bool wz::parse_double(WZLib_Property* dir, wz::node& cur_node) {
	cur_node = ((WZLib_PrimitiveProperty*)dir)->val.dblVal;
	return true;
}
bool wz::parse_extended(WZLib_Property* dir, wz::node& cur_node) {
	return true;
}
bool wz::parse_float(WZLib_Property* dir, wz::node& cur_node) {
	cur_node = ((WZLib_PrimitiveProperty*)dir)->val.dblVal;
	return true;
}
bool wz::parse_mp3(WZLib_SoundProperty* dir, wz::node& cur_node){
	sound newsound;
	newsound = dir;
	cur_node = newsound;
	return true;
}
bool wz::parse_null(WZLib_Property* dir, wz::node& cur_node, int index) {
	cur_node = index;
	return true;
}
bool wz::parse_string(WZLib_Property* dir, wz::node& cur_node) {
	cur_node = ((WZLib_PrimitiveProperty*)dir)->val.strVal;
	return true;
}
bool wz::parse_short(WZLib_Property* dir, wz::node& cur_node) {
	cur_node = ((WZLib_PrimitiveProperty*)dir)->val.intVal;
	return true;
}
bool wz::parse_uol(WZLib_Property* dir, wz::node& cur_node) {
	string* strs;//Array of all the nodes to navigate
	string path = ((WZLib_PrimitiveProperty*)dir)->val.strVal;
	int si = 0;//Amount of nodes to navigate
	strs = new string[10];//Increase this if needed
	for(int i=0;i<path.size();i++) {//Iterate through path chars
		char c = path[i];//We get the char
		if(c==*"/") {//If it’s a forward (back?) slash
			si++;//Increase amount of nodes
			continue;//And skip to next char
		}
		strs[si] += c;//Otherwise we just add the char
	}//And that is over
	wz::node newNode = cur_node.data->parent;//Start by going up
	for(int i=0;i<=si;i++) {//So now we deal with it
		if(strs[i]=="..") {//If it’s a parent node
			newNode = newNode.data->parent;//We go up
		} else {//Otherwise we go down
			newNode = newNode[strs[i]];
		}
	}//And that’s all over as well
	cur_node = newNode;//And here we just assign what we found
	return true;
}
bool wz::parse_vector(WZLib_Property* dir, wz::node& cur_node) {
	cur_node.g("x") = ((WZLib_PrimitiveProperty*)dir)->val.vecVal[0];
	cur_node.g("y") = ((WZLib_PrimitiveProperty*)dir)->val.vecVal[1];
	return true;
}
////////////////////////////////////////////////////////////////
// wz::node_data
////////////////////////////////////////////////////////////////
wz::node_data::node_data() {
	has = 0;
	image = 0;
	loaded = false;
}
////////////////////////////////////////////////////////////////
// wz::node
////////////////////////////////////////////////////////////////
wz::node::node() {
	data = 0;
}
wz::node::~node() {
	
}
wz::node& wz::node::operator [] (string key) {
	if(data) {
		if(data->image &&!data->loaded) {
			cout << "Loading img " << endl;
			WZLib_Image_Parse(data->image);
			data->loaded = true;
			wz::parse_sub(data->image->_sub,*this);
		}
		return data->children[key];
	}
	return empty_node;
}
wz::node& wz::node::g(string key) {
	wz::node& n = data->children[key];
	if(n.data==0) {
		n.data = new node_data;
		n.data->parent = *this;
		n.data->name = key;
	}
	return n;
}
wz::node& wz::node::operator [] (const char* key) {
	return (*this)[string(key)];
}
map <std::string, wz::node>::iterator wz::node::begin() {
	return (data->children).begin();
}
map <std::string, wz::node>::iterator wz::node::end() {
	return (data->children).end();
}
wz::node::operator bool() {
	return data;
}
wz::node::operator double() {
	if (data==0) {
		return 0;
	}
	if (data->has&1) {
		return data->realValue;
	}
	if (data->has&2) {
		data->realValue = toreal(data->stringValue);
		data->has |= 1;
		return data->realValue;
	}
	return 0;
}
wz::node::operator int() {
	if (data==0) {
		return 0;
	}
	if (data->has&1) {
		return (int)data->realValue;
	}
	if (data->has&2) {
		data->realValue = toreal(data->stringValue);
		data->has |= 1;
		return (int)data->realValue;
	}
	return 0;
}
wz::node::operator string() {
	if (data==0) {
		return "";
	}
	if (data->has&2) {
		return data->stringValue;
	}
	if (data->has&1) {
		data->stringValue = tostring(data->realValue);
		data->has |= 2;
		return data->stringValue;
	}
	return "";
}
wz::node::operator Sprite() {
	if (data==0 or data->has&4==0) {
		return Sprite();
	}
	return data->spriteValue;
}
wz::node::operator sound() {
	if (data==0 or data->has&8==0) {
		return sound();
	}
	return data->soundValue;
}
void wz::node::operator = (double value) {
	data->realValue = value;
	data->has = 1;
}
void wz::node::operator = (int value) {
	data->realValue = value;
	data->has = 1;
}
void wz::node::operator = (string value) {
	data->stringValue = value;
	data->has = 2;
}
void wz::node::operator = (Sprite value) {
	data->spriteValue = value;
	data->has = 3;
}
void wz::node::operator = (sound value) {
	data->soundValue = value;
	data->has = 4;
}
void wz::node::operator = (wz::node other) {
	data = other.data;
}

////////////////////////////////////////////////////////////////
// wz::top_node
////////////////////////////////////////////////////////////////
wz::top_node::top_node() {
	
}
wz::top_node::~top_node() {
	
}
wz::node& wz::top_node::operator [] (string key) {
	return children[key];
}
wz::node& wz::top_node::g(string key) {
	wz::node& n = children[key];
	if(n.data==0) {
		n.data = new node_data;
		n.data->name = key;
	}
	return n;
}
map <std::string, wz::node>::iterator wz::top_node::begin() {
	return children.begin();
}
map <std::string, wz::node>::iterator wz::top_node::end() {
	return children.end();
}
////////////////////////////////////////////////////////////////
// Special nodes
////////////////////////////////////////////////////////////////
wz::top_node wz::top;
wz::node wz::empty_node;
