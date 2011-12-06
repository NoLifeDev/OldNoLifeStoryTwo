////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	class MapleRNG {
	public:
		MapleRNG() {
			uint32_t seed = 1170746341 * rand() - 755606699;
			reset(seed, seed, seed);
		}
		void reset(uint32_t, uint32_t, uint32_t);
		uint32_t next();

	private:
		uint32_t m_seed1;
		uint32_t m_seed2;
		uint32_t m_seed3;
	};
	inline void MapleRNG::reset(uint32_t seed1, uint32_t seed2, uint32_t seed3) {
		m_seed1 = seed1 | 0x100000;
		m_seed2 = seed2 | 0x1000;
		m_seed3 = seed3 | 0x10;
	}
	inline uint32_t MapleRNG::next() {
		m_seed1 = ((m_seed1 & 0xFFFFFFFE) << 12) ^ (((m_seed1 << 13) ^ m_seed1) >> 19);
		m_seed2 = ((m_seed2 & 0xFFFFFFF8) << 4) ^ (((m_seed2 << 2) ^ m_seed2) >> 25);
		m_seed3 = ((m_seed3 & 0xFFFFFFF0) << 17) ^ (((m_seed3 << 3) ^ m_seed3) >> 11);

		return (m_seed1 ^ m_seed2 ^ m_seed3);
	}
}