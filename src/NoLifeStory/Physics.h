////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
namespace NLS {
	class Physics {
	public:
		double x, y, r;
		double vx, vy, vr;
		Foothold* fh;
		LadderRope* lr;
		int layer, group;
		int freefall;
		bool left, right, up, down;
		bool f;
		int movementState;
		Foothold* djump;
		Physics();
		Physics(double x, double y);
		void Update();
		void Reset(double x, double y);
		void Jump();
		void MouseFly();
		static void Init();
	};

	namespace PlayerMovementState {
		enum PlayerMovementState {
			Airstrike,
			Alert,
			Alert2,
			Alert3,
			Alert4,
			Alert5,
			Alert6,
			Alert7,
			Alert8,
			ArcherDoubleJump,
			ArrowEruption,
			ArrowRain,
			Assassination,
			AssassinationS,
			Assaulter,
			Avenger,
			Awakening,
			Backspin,
			Backstep,
			Bamboo,
			Battlecharge,
			Blade,
			BladeFury,
			Blast,
			Blaze,
			BlessOfGaia,
			Blizzard,
			BloodyStorm,
			BluntSmash,
			BombExplosion,
			Brandish1,
			Brandish2,
			BraveSlash1,
			BraveSlash2,
			BraveSlash3,
			BraveSlash4,
			BreathePrepare,
			Burster1,
			Burster2,
			Cannon,
			CannonBooster,
			CannonJump,
			CannonSlam,
			CannonSmash,
			CannonSpike,
			Capture,
			ChainAttack,
			ChainLightning,
			ChainPull,
			ChargeBlow,
			ClawCut,
			CombatStep,
			ComboFenrir,
			ComboJudgement,
			ComboSmash,
			ComboTempest,
			CoolingEffect,
			CounterCannon,
			Create0,
			Create1,
			Create2,
			Create2_f,
			Create2_s,
			Create3,
			Create3_f,
			Create3_s,
			Create4,
			Create4_f,
			Create4_s,
			CrossPiercing,
			Cyclone,
			CycloneAfter,
			CyclonePre,
			DarkChain,
			DarkFog,
			DarkImpale,
			DarkLightning,
			DarkSight,
			DarkSping,
			DarkThrust,
		};
	}
}
