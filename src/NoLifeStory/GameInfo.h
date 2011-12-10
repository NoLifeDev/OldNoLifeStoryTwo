////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	namespace BuffValueTypes {
		uint32_t GetFlagFromBit(uint8_t bit);
		namespace ValuesInt1 {
			enum BuffValueTypes {
				// Byte 1
				WeaponAttack,
				WeaponDefence,
				MagicAttack,
				MagicDefence,
				Accurancy,
				Avoidability,
				Hands, // Yes, this has a modifier too.
				Speed,

				// Byte 2
				Jump,
				MagicGuard,
				DarkSight,
				Booster,
				PowerGuard,
				HyperBody,
				MobSkillPoison,
				Invincible,

				// Byte 3
				SoulArrow,
				Stun, // Mob Skill: Stun and Dragon Roar
				Poison, // Mob Skill: Poison
				Seal, // Mob Skill: Seal
				Darkness, // Mob Skill: Darkness
				ComboAttack,
				Charges,
				DragonBlood,

				// Byte 4
				HolySymbol,
				UNKNOWN1,
				ShadowPartner,
				PickPocketMesoUP,
				MesoGuard,
				UNKNOWN2,
				Weakness, // Mob Skill: Weakness
				Curse  // Mob Skill: Curse
			};
		}
		namespace ValuesInt2 {
			enum BuffValueTypes {
				// Byte 5
				Slow,
				Morph,
				Recovery,
				MapleWarrior,

				PowerStance,
				SharpEyes,
				ManaReflection,
				Seduce,
				
				// Byte 6
				ShadowStars,
				Infinity,
				HolyShield,
				Hamstring,

				Blind,
				Concentrate,
				Zombify,
				EchoOfHero,
				
				// Byte 7
				Unk1,
				Unk2,
				Unk3,
				CrazySkull,

				Unk4,
				Unk5,
				Unk6,
				Unk7,
				
				// Byte 8
				GmHide,
				Unk8,
				Unk9, 
				Unk10,

				Unk11,
				Unk12,
				Unk13,
				Unk14,
			};
		}
		namespace ValuesInt3 {
			enum BuffValueTypes {
				// Byte 9
				Unk1,
				Unk2,
				Unk3,
				EnergyCharge,

				Dash1,
				Dash2,
				MountMonsterShip,
				SpeedInfusion,

				// Byte 10
				HomingBeaconBullsEye,
				Unk4,
				Unk5,
				Unk6,

				Unk7,
				Unk8,
				Unk9,
				Unk10,

				// Byte 11
				Unk11,
				Unk12,
				Unk13,
				Unk14,

				Unk15,
				Unk16,
				Unk17,
				Unk18,

				// Byte 12
				Unk19,
				Unk20,
				Unk21,
				Unk22,

				Unk23,
				Unk24,
				Unk25,
				Unk26,
			};
		}
	}
	inline uint32_t BuffValueTypes::GetFlagFromBit(uint8_t bit) {
		return (uint32_t)(1 >> bit);
	}
}