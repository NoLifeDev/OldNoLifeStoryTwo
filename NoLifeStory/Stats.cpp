///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////
#include "Global.h"

CharacterStats::CharacterStats() {
	name = "Retep998";
	nameTag = 0;
	tname = new Text(name, 12);

	guildName = "NoLifeGuild";
	guildMedalBackground = 1000;
	guildMedalBackgroundColor = 2;
	guildMedalForeground = 3000;
	guildMedalForegroundColor = 2;
	tguild = new Text(guildName, 12);

	skin = 2005;
	face = 20300;
	hair = 30024;
	equips.cap = 1002824;
	equips.medal = 0;
	equips.forehead = 0;
	equips.ring1 = 0;
	equips.ring2 = 0;
	equips.eyeacc = 0;
	equips.earacc = 0;
	equips.mantle = 0;
	equips.clothes = 1052170;
	equips.pendant = 0;
	equips.weapon = 1322013;
	equips.shield = 0;
	equips.gloves = 0;
	equips.pants = 0;
	equips.belt = 0;
	equips.ring3 = 0;
	equips.ring4 = 0;
	equips.shoes = 1072369;
	equips.petmp = 0;
	equips.tamingmob = 0;
	equips.saddle = 0;
	equips.mobequip = 0;
	equips.petacc = 0;
	equips.pethp = 0;
}