///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////

const double walkForce = 140000;
const double walkSpeed = 125;
const double walkDrag = 80000;
const double slipForce = 60000;
const double slipSpeed = 120;
const double floatDrag1 = 100000;
const double floatDrag2 = 10000;
const double floatCoefficient = 0.01;
const double swimForce = 120000;
const double swimSpeed = 140;
const double flyForce = 120000;
const double flySpeed = 200;
const double gravityAcc = 2000;
const double fallSpeed = 670;
const double jumpSpeed = 555;
const double maxFriction = 2;
const double minFriction = 0.05;
const double swimSpeedDec = 0.9;
const double flyJumpDec = 0.35;

class character : public object { //This is the base for all characters. It handles drawing
public:
	character();
	void draw();
	virtual void getequips(queue<wz::node>& parts)=0;
	bool f;
	string state;
	double delay;
	string skin;
	int frame;
};
class player : public character { //Ingame characters. Basics of physics here

};
class this_player : public player { //Player control and access to the player data here
public:
	this_player();
	void checkPortal(bool up, int dir);
	void draw();
	void getequips(queue<wz::node>& parts);
	velocity vel;
	foothold* ground;
	ladder* onladder;
	int group;
	foothold* downjump;
	foothold* porange;
	foothold* pblue;
	double plo, plb;
	int pdelay;
};
class other_player : public player { //Loading player data from server and interpolating movement
	other_player();
};
class login_character : public character { //Barely nothing added here. Just stand there

};