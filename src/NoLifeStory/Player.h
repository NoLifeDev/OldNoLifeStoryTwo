////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
namespace NLS {
	class Player : public Physics {//Base for all players
	public:
		Player();
		void Draw();
		uint32_t charid;
		uint8_t level, gender;
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
		void ChangeEmote(int id);
		void SetItemBySlot(int8_t slotid, int32_t itemid);

		
		struct Stats {
			uint16_t Job, Str, Dex, Int, Luk, AP;
			uint32_t HP, MaxHP, MP, MaxMP, EXP, GachaEXP;
			int32_t Fame;
			array<int16_t, 4> SP;
			// Changes:
			// Since Evan and newer jobs they split the amount of SP per job.
			// V.98 afaik has higher fame cap (short -> int)
		} stats;

		class Inventory {
		public:
			int32_t mesos;
			array<Item *, 50> shownEquips;
			array<Item *, 50> hiddenEquips;
			map<Item *, int32_t> specialEquips; // Anything not in the shown/hidden equips list, such as Android equips and such
			array<map<int16_t, Item *>, 5> inventoryItems;
			array<int8_t, 5> inventorySlots;
		} inventory;

		static string GetEmoteNameByID(int id);
		static int GetEmoteIDByName(string name);
		static void Init();
	};
}
