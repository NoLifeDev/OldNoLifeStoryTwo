///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////

class Element {
public:
	int x, y, w, h;
	bool hover, active;
	vector<Element> children;
	virtual void Draw(int x, int y);
	virtual bool HandleMouse(int x, int y, Mouse::Action action);
	virtual bool HandleKey(int key);
};