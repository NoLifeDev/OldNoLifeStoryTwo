////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	class Npc;
	class Mob;

	class Life {
	public:
		static void Load();
		void Init();
		virtual void Draw();
		void Update();
		void ChangeState(const string &);
		int x, y, cx, cy, rx0, rx1;
		int time;
		string id, type, defaultState, currentState, name;
		Node data;

		AniSprite currentAnimation;
		bool f, hide;
		static vector <Mob *> Mobs;
		static vector <Npc *> Npcs;
	};

	class Npc : public Life {
	public:
		Npc::Npc() : hasMapleTVAnim(false) { }
		void Draw();
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