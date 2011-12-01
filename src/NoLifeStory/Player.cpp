////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

NLS::Player::Player() : Physics() {
	state = "jump";
	frame = 0;
	delay = 0;
	emote = "default";
	emoted = 0;
	emotef = 0;
	skin = 1;
	face = 20000;
	hair = 30000;
	level = 8;
	name = "NotYourself";
	nametag.Set(name);
	guildname = "";
	guildtag.Set(guildname);
	left = right = up = down = false;
	for (int8_t i = 0; i < 20; i++) {
		SetItemBySlot(i, 0);
	}
}

void NLS::Player::SetItemBySlot(int8_t slotid, int32_t itemid) {
	slotid = abs(slotid);
	switch (slotid) {
	case 1: cap = itemid; break;
	case 2: forehead = itemid; break;
	case 3: eyeacc = itemid; break;
	case 4: earacc = itemid; break;
	case 5: clothes = itemid; break;
	case 6: pants = itemid; break;
	case 7: shoes = itemid; break;
	case 8: gloves = itemid; break;
	case 9: mantle = itemid; break;
	case 10: shield = itemid; break;
	case 11: weapon = itemid; break;
	}
}

void NLS::Player::Draw() {
	Physics::Update();
	if (y > View::ymax+1000) Map::Load("999999999", "sp");
	if (emote != "default") {
		emoted += Time::delta*1000;
		emotee += Time::delta*1000;
		int d = WZ["Character"]["Face"][tostring(face, 8)][emote][emotef]["delay"];
		if (emoted > d) {
			emotef++;
			emoted = 0;
			if (!WZ["Character"]["Face"][tostring(face, 8)][emote][emotef]) {
				emotef = 0;
				if (emote == "blink") {
					emote = "default";
				}
			}
		}
		if (emotee > 4000) {
			emote = "default";
			emotee = 0;
		}
	} else {
		if (rand()%5000 < Time::delta*1000) {
			emote = "blink";
			emotee = 0;
		}
	}
	if (!lr or (up^down)) {
		delay += Time::delta*1000;
	}
	if (fh) {
		if (left^right) {
			state = "walk1";
		} else if (down) {
			state = "prone";
		} else {
			state = "stand1";
		}
	} else if (lr) {
		if (lr->l) {
			state = "ladder";
		} else {
			state = "rope";
		}
	} else if ((int)Map::node["info"]["swim"]) {
		state = "fly";
	} else {
		state = "jump";
	}

	auto skinData = WZ["Character"]["00002"+tostring(skin, 3)];
	auto headData = WZ["Character"]["00012"+tostring(skin, 3)];

	int d = skinData[state][frame]["delay"];
	static bool weird = false;
	if (delay > d) {
		delay = 0;
		if (weird and state == "stand1") {
			frame--;
			weird = false;
		} else {
			frame++;
			weird = false;
		}
	}
	if (!skinData[state][frame]) {
		if (state == "stand1") {
			frame = 1;
			weird = true;
		} else {
			frame = 0;
		}
	}
	Node zmap = WZ["zmap"];
	vector<Node> parts;
	parts.push_back(skinData[state][frame]);
	parts.push_back(headData[state][frame]);
	parts.push_back(WZ["Character"]["Hair"][tostring(hair, 8)][state][frame]);
	if ((int)skinData[state][frame]["face"]) {
		if (emote == "default") {
			parts.push_back(WZ["Character"]["Face"][tostring(face, 8)][emote]);
		} else {
			parts.push_back(WZ["Character"]["Face"][tostring(face, 8)][emote][emotef]);
		}
	}
	GetEquips(parts);

	struct part {
		Sprite spr;
		int z;
		double x;
		double y;
	};
	vector<part> sparts;
	map<string, sf::Vector2<double>> maps;
	Node base = skinData[state][frame];
	if (f) {
		maps["navel"].x = x-(double)base["body"]["map"]["navel"]["x"];
	} else {
		maps["navel"].x = x+(double)base["body"]["map"]["navel"]["x"];
	}
	maps["navel"].y = y+(double)base["body"]["map"]["navel"]["y"];
	for (auto it = parts.begin(); it != parts.end(); ++it) {
		Node n = *it;
		if (!n) {
			continue;
		}
		if (n["action"]) {
			n = n[".."][".."][n["action"]][n["frame"]];
		}
		for (auto it = n.begin(); it != n.end(); ++it) {
			string name = it->first;
			Node nn = it->second;
			if (!nn) continue;
			Sprite s = nn;
			if (!s.data) continue;
			if (cap and (name == "hairOverHead" or name == "backHair")) continue;
			part np;
			np.spr = s;
			np.z = zmap[nn["z"]];
			np.x = x;
			np.y = y;
			for (auto it = nn["map"].rbegin(); it != nn["map"].rend(); ++it) {
				string mname = it->first;
				Node mn = it->second;
				if (maps.find(mname) == maps.end()) {
					if (f) {
						maps[mname].x = np.x-(double)mn["x"];
					} else {
						maps[mname].x = np.x+(double)mn["x"];
					}
					maps[mname].y = np.y+(double)mn["y"];
				} else {
					if (f) {
						np.x = maps[mname].x+(double)mn["x"];
					} else {
						np.x = maps[mname].x-(double)mn["x"];
					}
					np.y = maps[mname].y-(double)mn["y"];
				}
			}
			sparts.push_back(np);
		}
	}
	sort(sparts.begin(), sparts.end(), [&](const part& a, const part& b){return a.z>b.z;});
	for (auto it = sparts.begin(); it != sparts.end(); it++) {
		it->spr.Draw(it->x, it->y, f);
	}
	nametag.Draw(x, y);
	guildtag.Draw(x, y+15);
}

void NLS::Player::GetEquips(vector<Node>& parts) {
	if (clothes > 0) {
		if (clothes < 1050000){
			parts.push_back(WZ["Character"]["Coat"][tostring(clothes, 8)][state][tostring(frame)]);
		}
		else {
			parts.push_back(WZ["Character"]["Longcoat"][tostring(clothes, 8)][state][tostring(frame)]);
		}
	}
	if (pants > 0) parts.push_back(WZ["Character"]["Pants"][tostring(pants, 8)][state][tostring(frame)]);
	if (cap > 0) parts.push_back(WZ["Character"]["Cap"][tostring(cap, 8)][state][tostring(frame)]);
	if (shoes > 0) parts.push_back(WZ["Character"]["Shoes"][tostring(shoes, 8)][state][tostring(frame)]);
}
