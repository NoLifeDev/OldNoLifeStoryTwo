///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////

class velocity{
public:
	velocity();
	double xcomp();
	double xcomp(double xc);
	double ycomp();
	double ycomp(double yc);
	double speed();
	double speed(double spd);
	double direction();
	double direction(double dir);
	void add(double spd, double dir);
	void set(double spd, double dir);
	void limit(double dir);
	double getd(double dir);
private:
	double x,y;
};