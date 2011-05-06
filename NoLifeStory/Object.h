///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////

class object {
public:
	object();
	~object();
	virtual void draw()=0;
	double x, y;
	depth z;
	bool repeat;
	int movetype;
	double movew, moveh, movep, mover;
};

extern deque <object*> objects;
///////////////////////////////////////////////////////////////
// Define various objects here
///////////////////////////////////////////////////////////////
class tile : public object {
public:
	tile();
	void draw();
	Sprite spr;
};
class portal : public object {
public:
	portal();
	void draw();
	bool close;
	int pt;
	string pn;
	int tm;
	string tn;
	int x, y;
	int hi, vi;
	string script;
	int onlyOnce;
	int uDelay;
	int hideTooltip;
	int frame;
	int ani;
	int delay;
};
extern vector<portal*> portals;
class obj : public object {
public:
	obj();
	void draw();
	Sprite spr;
	bool f;
	wz::node data;
	int frame;
	int delay;
	int flow;
	double rx, ry;
};
class back : public object {
public:
	back();
	void draw();
	Sprite spr;
	bool f;
	int rx, ry, cx, cy, type;
	bool ani;
	wz::node data;
	int frame;
	int delay;
};