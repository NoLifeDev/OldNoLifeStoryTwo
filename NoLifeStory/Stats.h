///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////

struct CharacterStats {
	CharacterStats();
	Text* tname;
	Text* tguild;
	string name;
	short nameTag;

	string guildName;
	short guildMedalForeground;
	short guildMedalForegroundColor;
	short guildMedalBackground;
	short guildMedalBackgroundColor;

	int skin;
	int face;
	int hair;

	struct CharacterEquips {
		int cap;
		int medal;
		int forehead;
		int ring1;
		int ring2;
		int eyeacc;
		int earacc;
		int mantle;
		int clothes;
		int pendant;
		int weapon;
		int shield;
		int gloves;
		int pants;
		int belt;
		int ring3;
		int ring4;
		int shoes;
		int petmp;
		int tamingmob;
		int saddle;
		int mobequip;
		int petacc;
		int pethp;
	} equips;
};