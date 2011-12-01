////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

// This stuff is mad. 8 bytes for 64 buffs
namespace NLS {
	namespace BuffValueTypes { 
		enum BuffValueTypesLong1 {
			// Byte 1
			WeaponAttack =      0x00000001,
			WeaponDefence =     0x00000002,
			MagicAttack =       0x00000004,
			MagicDefence =      0x00000008,
			Accurancy =         0x00000010,
			Avoidability =      0x00000020,
			Hands =             0x00000040, // Yes, this has a modifier too.
			Speed =             0x00000080,

			// Byte 2
			Jump =              0x00000100,
			MagicGuard =        0x00000200,
			DarkSight =         0x00000400,
			Booster =           0x00000800,
			PowerGuard =        0x00001000,
			HyperBody =         0x00002000,
			MobSkillPoison =    0x00004000,
			Invincible =        0x00008000,

			// Byte 3
			SoulArrow =         0x00010000,
			Stun =              0x00020000, // Mob Skill: Stun and Dragon Roar
			Poison =            0x00040000, // Mob Skill: Poison
			Seal =              0x00080000, // Mob Skill: Seal
			Darkness =          0x00100000, // Mob Skill: Darkness
			ComboAttack =       0x00200000,
			Charges =           0x00400000,
			DragonBlood =       0x00800000,

			// Byte 4
			HolySymbol =        0x01000000,
			UNKNOWN1 =          0x02000000,
			ShadowPartner =     0x04000000,
			PickPocketMesoUP =  0x08000000,
			MesoGuard =         0x10000000,
			UNKNOWN2 =          0x20000000,
			Weakness =          0x40000000, // Mob Skill: Weakness
			Curse =             0x80000000  // Mob Skill: Curse
		};
	}
}