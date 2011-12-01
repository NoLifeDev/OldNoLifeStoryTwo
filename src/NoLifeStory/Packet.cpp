////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

map<uint16_t, function<void(NLS::Packet&)>> NLS::Packet::Handlers;


void NLS::Packet::Send() {
	uint16_t a = (Network::SendIV[3]<<8)+Network::SendIV[2];
	a ^= Network::Version;
	uint16_t b = a^(data.size()-4);
	data[0] = a%0x100;
	data[1] = a/0x100;
	data[2] = b%0x100;
	data[3] = b/0x100;
	cout << "Sent Packet: " << ToString() << endl;
	Encrypt();
	Network::Socket.Send((char*)data.data(), data.size());
}

#pragma region Encryption Stuff
#ifndef _WIN32
unsigned int _rotl8(uint8_t value, int shift)
{
	return (value<<shift)|(value>>(8-shift));
}

unsigned int _rotr8(uint8_t value, int shift)
{
	return (value>>shift)|(value<<(8-shift));
}
#endif //_WIN32

void NextIV(uint8_t *oldiv);

void NLS::Packet::Encrypt() {
	int32_t j;
	uint8_t a, c;
	uint8_t* buf = data.data()+4;
	size_t size = data.size()-4;
	
	for (uint8_t i = 0; i < 3; i++) {
		a = 0;
		for (j = size; j > 0; j--) {
			c = buf[size-j];
			c = _rotl8(c, 3);
			c += j;
			c ^= a;
			a = c;
			c = _rotr8(c, j);
			c = ~c;
			c += 0x48;
			buf[size-j] = c;
		}
		a = 0;
		for (j = size; j > 0; j--) {
			c = buf[j-1];
			c = _rotl8(c, 4);
			c += j;
			c ^= a;
			a = c;
			c ^= 0x13;
			c = _rotr8(c, 3);
			buf[j-1] = c;
		}
	}
	
	Crypto::TransformData(NLS::Network::SendIV, buf, size);
	NextIV(NLS::Network::SendIV);
}

void NLS::Packet::Decrypt() {
	uint8_t* buf = data.data(); // NO HEADERS HERE!!!
	size_t size = data.size();
	Crypto::TransformData(NLS::Network::RecvIV, buf, size);
	NextIV(NLS::Network::RecvIV);
	int32_t j;
	uint8_t a, b, c;
	for (uint8_t i = 0; i < 3; i++) {
		a = 0;
		b = 0;
		for (j = size; j > 0; j--) {
			c = buf[j-1];
			c = _rotl8(c, 3);
			c ^= 0x13;
			a = c;
			c ^= b;
			c -= j;
			c = _rotr8(c, 4);
			b = a;
			buf[j-1] = c;
		}
		a = 0;
		b = 0;
		for (j = size; j > 0; j--) {
			c = buf[size-j];
			c -= 0x48;
			c = ~c;
			c = _rotl8(c, j);
			a = c;
			c ^= b;
			c -= j;
			c = _rotr8(c, 3);
			b = a;
			buf[size-j] = c;
		}
	}
}

void NextIV(uint8_t *oldiv) {
	uint8_t newIV[4] = {0xF2, 0x53, 0x50, 0xC6};
	for (auto i = 0; i < 4; i++) {
		uint8_t input = oldiv[i];
		uint8_t tableInput = ShuffleKey[input];
		newIV[0] += ShuffleKey[newIV[1]]-input;
		newIV[1] -= newIV[2]^tableInput;
		newIV[2] ^= ShuffleKey[newIV[3]]+input;
		newIV[3] -= newIV[0]-tableInput;
		uint32_t& merged = *(uint32_t*)newIV;
		merged = merged<<3|merged>>0x1D;
	}
	for (auto i = 0; i < 4; i++) {
		oldiv[i] = newIV[i];
	}
}

#pragma endregion

#pragma region Packet Handlers

void NLS::Handle::Init() {
	uint8_t locale = Network::Locale;
	uint16_t version = Network::Version;
	uint16_t subversion = toint(Network::Patch);

	if (locale == NLS::Locales::Global) {
		if (version == 75) {
			Packet::Handlers[0x11] = &NLS::Handle::Ping;
			Packet::Handlers[0x72] = &NLS::Handle::ChangeMap;
			Packet::Handlers[0x91] = &NLS::Handle::PlayerSpawn;
			Packet::Handlers[0x92] = &NLS::Handle::PlayerDespawn;
			Packet::Handlers[0xA7] = &NLS::Handle::PlayerMove;
		}
	}

	cout << "[INFO] " << Packet::Handlers.size() << " handlers added for this MapleStory version." << endl;
}

void NLS::Handle::Ping(Packet &p) {
	Send::Pong();
}

void NLS::Handle::ChangeMap(Packet &p) {
	int32_t channel = p.Read<int32_t>();
	uint8_t portalCount = p.Read<uint8_t>();
	ThisPlayer->currentPortal = portalCount;
	bool channelConnect = p.Read<bool>();
	// Special stuff begin
	int16_t topMsgs = p.Read<int16_t>();
	if (topMsgs > 0) {
		p.Read<string>(); // Title
		for (auto i = 0; i < topMsgs; i++) {
			p.Read<string>(); // Lines
		}
	}
	// Special stuff end

	if (channelConnect) {
		// RNG's
		p.Read<uint32_t>();
		p.Read<uint32_t>();
		p.Read<uint32_t>();

		// Flag. Just ignore and load everything xd
		p.Read<uint64_t>(); // Most likely FF FF FF FF FF FF FF FF for every flag.

		ThisPlayer->charid = p.Read<uint32_t>();
		ThisPlayer->name = p.ReadStringLen(13);
		ThisPlayer->gender = p.Read<int8_t>();
		ThisPlayer->skin = p.Read<int8_t>();
		ThisPlayer->face = p.Read<int32_t>();
		ThisPlayer->hair = p.Read<int32_t>();

		p.Read<int64_t>(); // Pet ID's
		p.Read<int64_t>();
		p.Read<int64_t>();

		ThisPlayer->level = p.Read<uint8_t>();
		p.Read<int16_t>(); // job
		p.Read<int16_t>(); // Strength
		p.Read<int16_t>(); // Dex
		p.Read<int16_t>(); // Int
		p.Read<int16_t>(); // Luk
		p.Read<int16_t>(); // HP
		p.Read<int16_t>(); // MaxHP
		p.Read<int16_t>(); // MP
		p.Read<int16_t>(); // MaxMP
		p.Read<int16_t>(); // AP
		p.Read<int16_t>(); // SP
		p.Read<int32_t>(); // EXP
		p.Read<int16_t>(); // Fame

		p.Read<int32_t>(); // GachaEXP
		int32_t mapid = p.Read<int32_t>();
		int8_t mappos = p.Read<int8_t>();

		ThisPlayer->nametag.Set(ThisPlayer->name);
		Map::nextmap = tostring(mapid);
		Map::nextportalID = mappos;
		GoTest = true;
	}
}

void NLS::Handle::PlayerSpawn(Packet &p) {
	// Spawn player
	uint32_t id = p.Read<uint32_t>();
	// TODO: Should check if player in list... oh w/e
	Player *player = new Player;
	player->charid = id;
	player->name = p.Read<string>();
	player->guildname = p.Read<string>();
	
	p.Read<int16_t>(); // Guild Emblem BG
	p.Read<int8_t>(); // Guild Emblem BG Color
	p.Read<int16_t>(); // Guild Emblem
	p.Read<int8_t>(); // Guild Emblem Color


	// OK THIS IS MADNESS. BRB GUYS

	// ok.. there we go. Started 1-12-2011

	p.Read<int32_t>();
	p.Read<int32_t>();

	// oh my gah

	uint64_t buffFlags = p.Read<uint64_t>();
	// gets WvsBeta
	{
		using namespace NLS::BuffValueTypes;
		if (buffFlags & Speed) {
			p.Read<int8_t>(); // Value
		}
		if (buffFlags & ComboAttack) {
			p.Read<int8_t>(); // Value
		}
		if (buffFlags & Charges) {
			p.Read<int32_t>(); // SkillID
		}
		if (buffFlags & Stun) {
			p.Read<int32_t>(); // SkillID
		}
		if (buffFlags & Darkness) {
			p.Read<int32_t>(); // SkillID
		}
		if (buffFlags & Seal) {
			p.Read<int32_t>(); // SkillID
		}
		if (buffFlags & Weakness) {
			p.Read<int32_t>(); // SkillID
		}
		if (buffFlags & Curse) {
			p.Read<int32_t>(); // SkillID
		}
		if (buffFlags & Poison) {
			p.Read<int16_t>(); // 'value'?
			p.Read<int32_t>(); // SkillID
		}
		if (buffFlags & ShadowPartner) {
			
		}
		if (buffFlags & DarkSight) {
			
		}
		if (buffFlags & SoulArrow) {
			
		}
	}
	// Ok.. could be worse. Need to handle more types on different versions (V.88 has 2 longs)
	
	p.Read<int32_t>();
	p.Read<int32_t>();
	p.Read<int16_t>();
	p.Read<int32_t>(); // Static value?
	
	p.Read<int16_t>();
	p.Read<int8_t>();
	p.Read<int32_t>();
	p.Read<int32_t>();
	p.Read<int32_t>(); // Static value?
	
	p.Read<int16_t>();
	p.Read<int8_t>();
	p.Read<int32_t>();
	p.Read<int32_t>();
	p.Read<int32_t>(); // Static value?
	
	p.Read<int16_t>();
	p.Read<int8_t>();
	p.Read<int32_t>(); // Mount ID
	p.Read<int32_t>(); // Mount Skill
	p.Read<int32_t>(); // Static value?

	p.Read<int8_t>();
	p.Read<int32_t>();
	p.Read<int32_t>();
	p.Read<int32_t>(); // Static value?
	
	p.Read<int32_t>();
	p.Read<int32_t>();
	p.Read<int32_t>();
	p.Read<int32_t>();
	p.Read<int32_t>(); // Static value?

	p.Read<int8_t>();
	p.Read<int32_t>();
	p.Read<int32_t>();
	p.Read<int32_t>();
	p.Read<int32_t>(); // Static value?
	
	p.Read<int16_t>();
	p.Read<int8_t>();

	
	// PLAYER INFO. FINALLY
	{
		p.Read<int16_t>(); // Player Job
		player->gender = p.Read<int8_t>();
		player->skin = p.Read<int8_t>();
		player->face = p.Read<int32_t>();
		p.Read<int8_t>(); // Actually slot 0 for hair!!!
		player->hair = p.Read<int32_t>();
		// Shown
		while (true) {
			int8_t slot = p.Read<int8_t>();
			if (slot == -1) break;
			int32_t itemid = p.Read<int32_t>(); // ItemID
			player->SetItemBySlot(slot, itemid);
		}
		// Hidden
		while (true) {
			int8_t slot = p.Read<int8_t>();
			if (slot == -1) break;
			p.Read<int32_t>(); // ItemID
		}
		p.Read<int32_t>(); // Special Cash Weapon

		p.Read<int32_t>(); // Pet IDs
		p.Read<int32_t>();
		p.Read<int32_t>();
	}

	p.Read<int32_t>();
	p.Read<int32_t>(); // Item Effect
	p.Read<int32_t>(); // Chair
	player->x = p.Read<int16_t>();
	player->y = p.Read<int16_t>();
	player->state = player->StanceToString(p.Read<int8_t>());
	int16_t foothold = p.Read<int16_t>();
	for (set<Foothold*>::iterator iter = Foothold::begin(); iter != Foothold::end(); iter++) {
		if ((*iter)->id == foothold) {
			player->fh = (*iter);
		}
	}

	// More to come...

	player->guildtag.Set(player->guildname);
	player->nametag.Set(player->name);
	Map::Players[id] = player;
}

void NLS::Handle::PlayerDespawn(Packet &p) {
	// Spawn player
	uint32_t id = p.Read<uint32_t>();
	Player *player = Map::Players.find(id) != Map::Players.end() ? Map::Players[id] : nullptr;
	if (player == nullptr) return;
	Map::Players.erase(id);
	delete player;
	// TODO: delete other stuff too
}

void NLS::Handle::PlayerMove(Packet &p) {
	uint32_t id = p.Read<uint32_t>();
	Player *player = Map::Players.find(id) != Map::Players.end() ? Map::Players[id] : nullptr;
	if (player == nullptr) return;
	DecodeMovement(p, player);
}

void NLS::Handle::DecodeMovement(Packet &p, Physics*player) {
	p.Read<int32_t>(); // Unknown, should be X and Y...?

	uint8_t actions = p.Read<uint8_t>();
	for (auto i = 0; i < actions; i++) {
		uint8_t type = p.Read<uint8_t>();
		Movement move(type);
		if (move.type == 0 || move.type == 5) {
			move.x = p.Read<int16_t>();
			move.y = p.Read<int16_t>();
			move.vx = p.Read<int16_t>();
			move.vy = p.Read<int16_t>();
			move.fh = p.Read<int16_t>();
			move.stance = p.Read<int8_t>();
			move.t = p.Read<int16_t>();
		}
		else if (move.type == 1 || move.type == 2 || move.type == 6 || move.type == 13) {
			move.vx = p.Read<int16_t>();
			move.vy = p.Read<int16_t>();
			move.stance = p.Read<int8_t>();
			move.fh = p.Read<int16_t>();
		}
		else if (move.type == 15) {
			move.x = p.Read<int16_t>();
			move.y = p.Read<int16_t>();
			move.vx = p.Read<int16_t>();
			move.vy = p.Read<int16_t>();
			p.Read<int16_t>(); // TODO find out
			move.fh = p.Read<int16_t>();
			move.stance = p.Read<int8_t>();
			move.t = p.Read<int16_t>();
		}
		else if (move.type == 11) {
			move.x = p.Read<int16_t>();
			move.y = p.Read<int16_t>();
			move.fh = p.Read<int16_t>();
			move.stance = p.Read<int8_t>();
			move.t = p.Read<int16_t>(); // Not sure
		}
		else if (move.type == 10) {
			p.Read<int8_t>(); // TODO find out
			continue;
		}
		else if (move.type == 16) {
			move.x = p.Read<int16_t>();
			move.y = p.Read<int16_t>();
			move.fh = p.Read<int16_t>();
			move.stance = p.Read<int8_t>(); // I guess
		}
		else if (move.type == 17) {
			move.x = p.Read<int16_t>();
			move.y = p.Read<int16_t>();
			move.fh = p.Read<int16_t>();
			move.stance = p.Read<int8_t>();
			p.Read<int32_t>();
			move.t = p.Read<int16_t>();
		}
		else if (move.type == 12) {
			move.x = p.Read<int16_t>();
			move.y = p.Read<int16_t>();
			move.fh = p.Read<int16_t>();
			move.t = p.Read<int16_t>(); // NOT SURE
		}
		else if (move.type == 14) { // NOT SURE
			move.x = p.Read<int16_t>();
			move.y = p.Read<int16_t>();
			move.vx = p.Read<int16_t>();
			move.vy = p.Read<int16_t>();
			move.t = p.Read<int16_t>();
		}
		else if (move.type == 3 || move.type == 4 || (move.type >= 7 && move.type <= 9)) { // NOT SURE
			move.x = p.Read<int16_t>();
			move.y = p.Read<int16_t>();
			move.vx = p.Read<int16_t>();
			move.vy = p.Read<int16_t>();
			move.stance = p.Read<int8_t>();
		}
		player->moves.push_back(move);
	}
}

void NLS::Send::Pong() {
	Packet packet(0x19);
	packet.Send();
}

void NLS::Send::Pang() {
	// Loading special character for local testserver.
	NLS::Packet packet(0x14);
	packet.Write<int32_t>(3); // Special Character!
	packet.Send();
	//NLS::Packet packet(0x18);
	//packet.Send();
}

void NLS::Send::Handshake() {
	if (Network::Locale == 0x08 && Network::Version <= 100) return; // GMS V.100 and lower didn't have this.
	if (Network::Locale == 0x07 && Network::Version <= 111) return; // MSEA V.111 and lower didn't have this. |NOTSURE|

	uint16_t subversion = atoi(Network::Patch.c_str());
	uint16_t header = 0;
	if (Network::Locale == 0x08) {
		if (Network::Version >= 101) header = 0x14;
	}
	else if (Network::Locale == 0x09) {
		if (Network::Version >= 112) header = 0x01; // No shit!
	}

	NLS::Packet packet(header);
	packet.Write<uint8_t>(Network::Locale);
	packet.Write<uint16_t>(Network::Version);
	packet.Write<uint16_t>(subversion);
	packet.Send();
}

void NLS::Send::PlayerMove() {
	NLS::Packet p(0x28);
	p.Write<int8_t>(ThisPlayer->currentPortal);
	p.Write<int32_t>(0); // Move X and Y??
	p.Write<int16_t>(ThisPlayer->x);
	p.Write<int16_t>(ThisPlayer->y);
	p.Write<int8_t>(ThisPlayer->moves.size());

	for (auto i = 0; i < ThisPlayer->moves.size(); i++) {
		Movement move = ThisPlayer->moves[i];
		p.Write<int8_t>(move.type);
		if (move.type == 0 || move.type == 5) {
			p.Write<int16_t>(move.x);
			p.Write<int16_t>(move.y);
			p.Write<int16_t>(move.vx);
			p.Write<int16_t>(move.vy);
			p.Write<int16_t>(move.fh);
			p.Write<int8_t>(move.stance);
			p.Write<int16_t>(move.t);
		}
		else if (move.type == 1 || move.type == 2 || move.type == 6 || move.type == 13) {
			p.Write<int16_t>(move.x);
			p.Write<int16_t>(move.y);
			p.Write<int8_t>(move.stance);
			p.Write<int16_t>(move.fh);
		}
		else if (move.type == 15) {
			p.Write<int16_t>(move.x);
			p.Write<int16_t>(move.y);
			p.Write<int16_t>(move.vx);
			p.Write<int16_t>(move.vy);
			p.Write<int16_t>(0); // TODO find out
			p.Write<int16_t>(move.fh);
			p.Write<int8_t>(move.stance);
			p.Write<int16_t>(move.t);
		}
		else if (move.type == 11) {
			p.Write<int16_t>(move.x);
			p.Write<int16_t>(move.y);
			p.Write<int16_t>(move.fh);
			p.Write<int8_t>(move.stance);
			p.Write<int16_t>(move.t); // Not sure
		}
		else if (move.type == 10) {
			p.Write<int8_t>(0); // TODO find out
		}
		else if (move.type == 16) {
			p.Write<int16_t>(move.x);
			p.Write<int16_t>(move.y);
			p.Write<int16_t>(move.fh);
			p.Write<int8_t>(move.stance); // I guess
		}
		else if (move.type == 17) {
			p.Write<int16_t>(move.x);
			p.Write<int16_t>(move.y);
			p.Write<int16_t>(move.fh);
			p.Write<int8_t>(move.stance);
			p.Write<int32_t>(0);
			p.Write<int16_t>(move.t);
		}
		else if (move.type == 12) {
			p.Write<int16_t>(move.x);
			p.Write<int16_t>(move.y);
			p.Write<int16_t>(move.fh);
			p.Write<int16_t>(move.t); // NOT SURE
		}
		else if (move.type == 14) { // NOT SURE
			p.Write<int16_t>(move.x);
			p.Write<int16_t>(move.y);
			p.Write<int16_t>(move.vx);
			p.Write<int16_t>(move.vy);
			p.Write<int16_t>(move.t);
		}
		else if (move.type == 3 || move.type == 4 || (move.type >= 7 && move.type <= 9)) { // NOT SURE
			p.Write<int16_t>(move.x);
			p.Write<int16_t>(move.y);
			p.Write<int16_t>(move.vx);
			p.Write<int16_t>(move.vy);
			p.Write<int8_t>(move.stance);
		}
	}
	p.Write<int64_t>(0);
	p.Write<int64_t>(0);
	p.Write<int64_t>(0);
	p.Send();
	ThisPlayer->moves.clear();
}
#pragma endregion
