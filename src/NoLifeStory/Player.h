////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
namespace NLS {
	class Player : public Physics {//Base for all players
	public:
		Player();
		void Draw();
		uint8_t level;
		string name;
		string guildname;
		NameTag nametag;
		NameTag guildtag;
		string state;
		int frame, delay;
		string emote;
		int emoted, emotef, emotee;
		int skin, hair, face;
		int cap, medal, forehead, ring1;
		int ring2, eyeacc, earacc, mantle;
		int clothes, pendant, weapon, shield;
		int gloves, pants, belt, ring3;
		int ring4, shoes, petmp, tamingmob;
		int saddle, mobequip, petacc, pethp;
	};
}
