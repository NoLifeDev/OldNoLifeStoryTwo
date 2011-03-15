///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////

const int maxDepth = 8;

class depth {
public:
	enum depth_layers {
		back,
		layer,
		front,
		ui
	};
	enum depth_objects {
		obj,
		tile,
		life,
		player,
		portal
	};
	unsigned int size;
	int& operator [](unsigned int index);
	void operator =(int value);
	depth();
private:
	int z[maxDepth];
};