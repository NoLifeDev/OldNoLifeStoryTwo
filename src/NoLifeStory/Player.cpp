////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

NLS::Player::Player() : Physics() {
	state = "stand1";
	frame = 0;
	delay = 0;
	emote = "default";
	emoted = 0;
	emotef = 0;
	skin = 2000;
	face = 20000;
	hair = 30000;
}

void NLS::Player::Draw() {
	Physics::Update();
	glBindTexture(GL_TEXTURE_2D, 0);
	glColor4f(1, 0, 0, 1);
	glBegin(GL_LINE_LOOP);
	glVertex2i(x-16,y-48);
	glVertex2i(x+16,y-48);
	glVertex2i(x+16,y);
	glVertex2i(x-16,y);
	glEnd();
	delay += Time.delta*1000;
	if (emote != "default") {
		emoted += Time.delta*1000;
		emotee += Time.delta*1000;
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
		if (rand()%5000 < Time.delta*1000) {
			emote = "blink";
			emotee = 0;
		}
	}
	Node zmap = WZ["zmap"];
	zmap[""];
	vector<Node> parts;
	parts.push_back(WZ["Character"]["0000"+tostring(skin, 4)][state][frame]);
	parts.push_back(WZ["Character"]["0001"+tostring(skin, 4)][state][frame]);
	parts.push_back(WZ["Character"]["Hair"][tostring(hair, 8)][state][frame]);
	if ((int)WZ["Character"]["0000"+tostring(skin, 4)][state][frame]["face"]) {
		if (emote == "default") {
			parts.push_back(WZ["Character"]["Face"][tostring(face, 8)][emote]);
		} else {
			parts.push_back(WZ["Character"]["Face"][tostring(face, 8)][emote][emotef]);
		}
	}
	struct part {
		Sprite spr;
		int z;
		double x;
		double y;
	};
	vector<part> sparts;
	map<string, sf::Vector2<double>> maps;
	Node base = WZ["Character"]["0000"+tostring(skin, 4)][state][frame];
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
			if (!nn) {
				continue;
			}
			Sprite s = nn;
			if (!s.data) {
				continue;
			}
			if (cap and (name == "hairOverHead" or name == "backHair")) {
				continue;
			}
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
}