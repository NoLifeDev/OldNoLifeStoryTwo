///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////

enum LifeType {
	NPC, Mob
};

class life: public object {
public:
	life();
	virtual void draw();
	virtual void GetNewState() = 0;
	foothold* ground;
	double x, y, rx0, rx1;
	bool repeat;
	bool f;
	string id;
	string state;
	int frame;
	int ldelay;
	int delay;
	int mobtime;
	bool hidename;
	string name;
	Text* tname;
	wz::node img;
	double bt, bb, bl, br;
	vector<string> usableStates;
	LifeType type;
};
class mob: public life {
public:
	mob();
	void init();
	void draw();
	void GetNewState();
	//TODO proper mob spawning.
	int acc;
	int bodyAttack;
	int category;
	int eva;
	int exp;
	int fs;
	int level;
	int maxHP;
	int maxMP;
	int MADamage ,MMDamage, PADamage, PDDamage;
	int pushed;
	int speed;
	int summonType;
	int undead;
	int zigzag;
	bool boss;
	int hittime;
};
class npc: public life {
public:
	npc();
	void draw();
	void GetNewState();
};
extern vector <life*> lifes;
extern vector <mob*> mobs;
extern vector <npc*> npcs;