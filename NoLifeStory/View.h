///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////


class view_class{
public:
	int x, y;
	double vx, vy, tx, ty;
	double xmin, xmax, ymin, ymax;
	view_class();
	void step();
};
extern view_class view;