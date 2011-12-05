////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
namespace NLS {
	class Item {
	public:

		bool hasWarmSupport() const;
		bool hasSlipPrevention() const;
		bool hasLock() const;
		bool hasKarma() const;
		bool hasTradeBlock() const;

		void setStr(int16_t strength);
		void setDex(int16_t dexterity);
		void setInt(int16_t intelligence);
		void setLuk(int16_t luck);
		void setHp(int16_t hp);
		void setMp(int16_t mp);
		void setWatk(int16_t watk);
		void setWdef(int16_t wdef);
		void setMatk(int16_t matk);
		void setMdef(int16_t mdef);
		void setAccuracy(int16_t acc);
		void setAvoid(int16_t avoid);
		void setHands(int16_t hands);
		void setJump(int16_t jump);
		void setSpeed(int16_t speed);
		void setPreventSlip(bool prevent);
		void setWarmSupport(bool warm);
		void setLock(bool lock);
		void setKarma(bool karma);
		void setTradeBlock(bool block);
		void changeAmount(int16_t mod) { m_amount += mod; }
		void incHammers() { m_hammers++; }
		void incSlots() { m_slots++; }
		void decSlots() { m_slots--; }
		void incScrolls() { m_scrolls++; }

		int8_t m_slots;
		int8_t m_scrolls;
		int16_t m_str;
		int16_t m_dex;
		int16_t m_int;
		int16_t m_luk;
		int16_t m_hp;
		int16_t m_mp;
		int16_t m_watk;
		int16_t m_matk;
		int16_t m_wdef;
		int16_t m_mdef;
		int16_t m_acc;
		int16_t m_avo;
		int16_t m_hands;
		int16_t m_jump;
		int16_t m_speed;
		int16_t m_flags;
		int16_t m_amount;
		int32_t m_id;
		int32_t m_hammers;
		int32_t m_petId;
		int64_t m_cashId;
		int64_t m_expiration;
		string m_name;
	private:
		bool testPerform(int16_t stat, bool onlyIfExists);
		int16_t testStat(int16_t stat, int16_t max);
		void modifyFlags(bool add, int16_t flags);
		bool testFlags(int16_t flags) const;
	};

	namespace Items {
		const int64_t NoExpiration = 150842304000000000LL;
		const int32_t MaxHammers = 2;
		const int32_t WeatherTime = 30;

		namespace PacketTypes {
			enum PacketTypeID {
				Equip = 1,
				Item = 2,
				Pet = 3
			};
		}

		namespace Types {
			enum ItemTypes {
				ArmorHelm = 100,
				ArmorFace = 101,
				ArmorEye = 102,
				ArmorEarring = 103,
				ArmorTop = 104,
				ArmorOverall = 105,
				ArmorBottom = 106,
				ArmorShoe = 107,
				ArmorGlove = 108,
				ArmorShield = 109,
				ArmorCape = 110,
				ArmorRing = 111,
				ArmorPendant = 112,
				Medal = 114,
				Weapon1hSword = 130,
				Weapon1hAxe = 131,
				Weapon1hMace = 132,
				WeaponDagger = 133,
				WeaponWand = 137,
				WeaponStaff = 138,
				Weapon2hSword = 140,
				Weapon2hAxe = 141,
				Weapon2hMace = 142,
				WeaponSpear = 143,
				WeaponPolearm = 144,
				WeaponBow = 145,
				WeaponCrossbow = 146,
				WeaponClaw = 147,
				WeaponKnuckle = 148,
				WeaponGun = 149,
				Mount = 190,
				ItemArrow = 206,
				ItemStar = 207,
				ItemBullet = 233,
				ItemMonsterCard = 238,
				Pet = 500,
				MerchantShop = 503,
				WeatherCash = 512,
				PersonalShop = 514,
				CashPetFood = 524
			};
		}

		namespace ScrollTypes {
			enum ScrollTypes {
				Helm = 0,
				Face = 100,
				Eye = 200,
				Earring = 300,
				Topwear = 400,
				Overall = 500,
				Bottomwear = 600,
				Shoes = 700,
				Gloves = 800,
				Shield = 900,
				Cape = 1000,
				Ring = 1100,
				Pendant = 1200,
				OneHandedSword = 3000,
				OneHandedAxe = 3100,
				OneHandedMace = 3200,
				Dagger = 3300,
				Wand = 3700,
				Staff = 3800,
				TwoHandedSword = 4000,
				TwoHandedAxe = 4100,
				TwoHandedMace = 4200,
				Spear = 4300,
				Polearm = 4400,
				Bow = 4500,
				Crossbow = 4600,
				Claw = 4700,
				Knuckle = 4800,
				Gun = 4900,
				PetEquip = 8000,
				CleanSlate = 9000,
				Chaos = 9100
			};
		}

		namespace Flags {
			enum ItemFlags {
				Lock = 0x01,
				Spikes = 0x02,
				ColdProtection = 0x04,
				TradeUnavailable = 0x08,
				KarmaScissors = 0x10
			};
		}

		namespace StatVariance {
			const uint16_t Str = 2;
			const uint16_t Dex = 2;
			const uint16_t Int = 2;
			const uint16_t Luk = 2;
			const uint16_t Hp = 10;
			const uint16_t Mp = 10;
			const uint16_t Watk = 10;
			const uint16_t Wdef = 10;
			const uint16_t Matk = 10;
			const uint16_t Mdef = 10;
			const uint16_t Acc = 2;
			const uint16_t Avoid = 2;
			const uint16_t Hands = 4;
			const uint16_t Speed = 4;
			const uint16_t Jump = 2;
			const uint16_t RandScroll = 5;
		}

		namespace MaxStats {
			const int16_t Str = SHRT_MAX;
			const int16_t Dex = SHRT_MAX;
			const int16_t Int = SHRT_MAX;
			const int16_t Luk = SHRT_MAX;
			const int16_t Hp = SHRT_MAX;
			const int16_t Mp = SHRT_MAX;
			const int16_t Watk = 1999;
			const int16_t Wdef = 255;
			const int16_t Matk = 1999;
			const int16_t Mdef = 255;
			const int16_t Acc = 103;
			const int16_t Avoid = 103;
			const int16_t Hands = SHRT_MAX;
			const int16_t Speed = 40;
			const int16_t Jump = 23;
		}

		enum {
			// Equip
			GmHat = 1002140,
			GmTop = 1042003,
			GmBottom = 1062007,
			GmWeapon = 1322013,
			BattleshipMount = 1932000,

			// Use
			ShoeSpikes = 2040727,
			CapeColdProtection = 2041058,
			SpecialTeleportRock = 2320000,
			WhiteScroll = 2340000,

			// Etc.
			LudibriumMedal = 4031172,
			BeginnersShoppingGuide = 4031180,
			GoldenBell = 4031191,
			RedRibbon = 4031192,
			BeginnersGuidebook = 4161001,

			// Cash
			TeleportRock = 5040000,
			TeleportCoke = 5040001,
			VipRock = 5041000,
			ApReset = 5050000,
			FirstJobSpReset = 5050001,
			SecondJobSpReset = 5050002,
			ThirdJobSpReset = 5050003,
			FourthJobSpReset = 5050004,
			ItemNameTag = 5060000,
			ItemLock = 5060001,
			Megaphone = 5071000,
			SuperMegaphone = 5072000,
			ItemMegaphone = 5076000,
			ArtMegaphone = 5077000,
			MapleTvMessenger = 5075000,
			MapleTvStarMessenger = 5075001,
			MapleTvHeartMessenger = 5075002,
			Megassenger = 5075003,
			StarMegassenger = 5075004,
			HeartMegassenger = 5075005,
			KoreanKite = 5080000,
			HeartBalloon = 5080001,
			GraduationBanner = 5080002,
			AdmissionBanner = 5080003,
			CongratulatorySong = 5100000,
			SnowySnow = 5120000,
			SafetyCharm = 5130000,
			PetNameTag = 5170000,
			BronzeSackOfMesos = 5200000,
			SilverSackOfMesos = 5200001,
			GoldSackOfMesos = 5200002,
			FungusScroll = 5300000,
			OinkerDelight = 5300001,
			ZetaNightmare = 5300002,
			Chalkboard = 5370000,
			Chalkboard2 = 5370001,
			DiabloMessenger = 5390000,
			Cloud9Messenger = 5390001,
			LoveholicMessenger = 5390002,
			WheelOfDestiny = 5510000,
			ScissorsOfKarma = 5520000,
			ViciousHammer = 5570000
		};
	}
}