////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

bool NLS::Item::hasSlipPrevention() const {
	return testFlags(Items::Flags::Spikes);
}

bool NLS::Item::hasWarmSupport() const {
	return testFlags(Items::Flags::ColdProtection);
}

bool NLS::Item::hasLock() const {
	return testFlags(Items::Flags::Lock);
}

bool NLS::Item::hasKarma() const {
	return testFlags(Items::Flags::KarmaScissors);
}

bool NLS::Item::hasTradeBlock() const {
	return testFlags(Items::Flags::TradeUnavailable);
}

bool NLS::Item::testFlags(int16_t flags) const {
	return ((m_flags & flags) != 0);
}

void NLS::Item::setPreventSlip(bool prevent) {
	modifyFlags(prevent, NLS::Items::Flags::Spikes);
}

void NLS::Item::setWarmSupport(bool warm) {
	modifyFlags(warm, NLS::Items::Flags::ColdProtection);
}

void NLS::Item::setLock(bool lock) {
	modifyFlags(lock, NLS::Items::Flags::Lock);
}

void NLS::Item::setKarma(bool karma) {
	modifyFlags(karma, NLS::Items::Flags::KarmaScissors);
}

void NLS::Item::setTradeBlock(bool block) {
	modifyFlags(block, NLS::Items::Flags::TradeUnavailable);
}

void NLS::Item::modifyFlags(bool add, int16_t flags) {
	if (add) {
		m_flags |= flags;
	}
	else {
		m_flags &= ~(flags);
	}
}

void NLS::Item::setStr(int16_t strength) {
	m_str = testStat(strength, NLS::Items::MaxStats::Str);
}

void NLS::Item::setDex(int16_t dexterity) {
	m_dex = testStat(dexterity, NLS::Items::MaxStats::Dex);
}

void NLS::Item::setInt(int16_t intelligence) {
	m_int = testStat(intelligence, NLS::Items::MaxStats::Int);
}

void NLS::Item::setLuk(int16_t luck) {
	m_luk = testStat(luck, NLS::Items::MaxStats::Luk);
}

void NLS::Item::setHp(int16_t hp) {
	m_hp = testStat(hp, NLS::Items::MaxStats::Hp);
}

void NLS::Item::setMp(int16_t mp) {
	m_mp = testStat(mp, NLS::Items::MaxStats::Mp);
}

void NLS::Item::setWatk(int16_t watk) {
	m_watk = testStat(watk, NLS::Items::MaxStats::Watk);
}

void NLS::Item::setWdef(int16_t wdef) {
	m_wdef = testStat(wdef, NLS::Items::MaxStats::Wdef);
}

void NLS::Item::setMatk(int16_t matk) {
	m_matk = testStat(matk, NLS::Items::MaxStats::Matk);
}

void NLS::Item::setMdef(int16_t mdef) {
	m_mdef = testStat(mdef, NLS::Items::MaxStats::Mdef);
}

void NLS::Item::setAccuracy(int16_t acc) {
	m_acc = testStat(acc, NLS::Items::MaxStats::Acc);
}

void NLS::Item::setAvoid(int16_t avoid) {
	m_avo = testStat(avoid, NLS::Items::MaxStats::Avoid);
}

void NLS::Item::setHands(int16_t hands) {
	m_hands = testStat(hands, NLS::Items::MaxStats::Hands);
}

void NLS::Item::setJump(int16_t jump) {
	m_jump = testStat(jump, NLS::Items::MaxStats::Jump);
}

void NLS::Item::setSpeed(int16_t speed) {
	m_speed = testStat(speed, NLS::Items::MaxStats::Speed);
}

int16_t NLS::Item::testStat(int16_t stat, int16_t max) {
	int16_t ret = stat;
	if (ret < 0) {
		ret = 0;
	}
	else if (ret > max) {
		ret = max;
	}
	return ret;
}

bool NLS::Item::testPerform(int16_t stat, bool onlyIfExists) {
	if (onlyIfExists && stat == 0) {
		return false;
	}
	return true;
}