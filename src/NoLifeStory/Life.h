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
		static vector <Mob*> Mobs;
		static vector <Npc*> Npcs;
	};

	class Npc : public Life {
	public:
		Npc::Npc() : hasMapleTVAnim(false) { }
		void Draw();
		string function;
		NameTag functiontag;
	private:
		AniSprite mapleTVanim;
		AniSprite mapleTVanimMsg;
		bool hasMapleTVAnim;
	};

	class Mob : public Life {
	public:
		void Draw();
	};
}