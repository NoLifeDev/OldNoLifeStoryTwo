////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	class Npc;
	class Mob;

	class Life : public Physics {
	public:
		static void Load();
		Life() : Physics(), timeToNextAction(0) {}
		void Init();
		virtual void Draw();
		void Update();
		void ChangeState(const string &);
		int cx, cy, rx0, rx1;
		int timeToNextAction;
		int time;
		string id, type, defaultState, currentState, name;
		Node data;
		NameTag nametag;
		AniSprite currentAnimation;
		bool hide;
		bool isNPC;
		static map <uint32_t, Mob*> Mobs;
		static map <uint32_t, Npc*> Npcs;
		static uint32_t NpcStart, MobStart;
	};

	class Npc : public Life {
	public:
		Npc::Npc() : hasMapleTVAnim(false) { isNPC = true; type = "n"; }
		void Draw();
		string function;
		NameTag functiontag;
		ChatBalloon cb;
	private:
		AniSprite mapleTVanim;
		AniSprite mapleTVanimMsg;
		bool hasMapleTVAnim;
	};

	class Mob : public Life {
	public:
		Mob() { isNPC = false; type = "m"; }
		void Draw();
	};
}