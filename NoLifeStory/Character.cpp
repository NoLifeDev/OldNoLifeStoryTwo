///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////
#include "Global.h"

this_player* current;
struct part{
	Sprite spr;
	int z;
	double x;
	double y;
};
struct coord{
	string name;
	double x;
	double y;
};
character::character() {
	state = "stand1";
	emote = "default";
	frame = 0;
	delay = 0;
}

class partless{
public:
	bool operator ()(part a, part b) {
		return a.z<b.z;
	}
};
void character::draw() {
	delay += delta;
	wz::node data = wz::top["Character"]["00002000"][state];
	wz::node zmap = wz::top["Base"]["zmap"];
	queue<wz::node> parts;
	map<string, coord> maps;
	priority_queue<part, vector<part > ,partless> sparts;
	if (!data[tostring(frame)]) {
		frame = 0;
	}
	int d = data[tostring(frame)]["delay"];
	if (delay > d) {
		frame += 1;
		delay = 0;
		if (!data[tostring(frame)]) {
			frame = 0;
		}
	}
	data = data[tostring(frame)];
	getequips(parts);
	maps["navel"].name = "navel";
	if (f) {
		maps["navel"].x = x-(double)data["body"]["map"]["navel"]["x"];
	} else {
		maps["navel"].x = x+(double)data["body"]["map"]["navel"]["x"];
	}
	maps["navel"].y = y+(double)data["body"]["map"]["navel"]["y"];

	int face = data["face"];
	while(!parts.empty()) {
		wz::node node = parts.front();
		parts.pop();
		if (!node) {
			continue;
		}
		for(auto i=node.begin();i!=node.end();i++) {
			string name = i->first;
			wz::node& nnode = i->second;
			if (!nnode || nnode.data->spriteValue.data == 0) {
				continue;
			}
			if (stats.equips.cap and name == "hairOverHead" or name == "backHair") {
				continue;
			}
			double px = x;
			double py = y;
			part npart;
			npart.spr = nnode;
			npart.z = zmap[nnode["z"]];
			for(auto j=nnode["map"].end();j!=nnode["map"].begin();) {
				j--;
				string name2 = j->first;
				wz::node nnode2 = j->second;
				if (maps[name2].name == "") {
					maps[name2].name = name2;
					if (f) {
						maps[name2].x = px-(double)nnode2["x"];
					} else {
						maps[name2].x = px+(double)nnode2["x"];
					}
					maps[name2].y = py+(double)nnode2["y"];
				} else {
					if (f) {
						px = maps[name2].x+(double)nnode2["x"];
					} else {
						px = maps[name2].x-(double)nnode2["x"];
					}
					py = maps[name2].y-(double)nnode2["y"];
				}
			}
			npart.x = px;
			npart.y = py;
			sparts.push(npart);
		}
	}

	while (!sparts.empty()) {
		part npart = sparts.top();
		sparts.pop();
		npart.spr.Draw(npart.x, npart.y, true, f);
	}
	
	DrawNameTag(stats.tname, x, y, stats.nameTag);
	DrawGuildName(stats.tguild, x, y, stats.guildMedalBackground, stats.guildMedalBackgroundColor, stats.guildMedalForeground, stats.guildMedalForegroundColor);
}

this_player::this_player() {
	x = 0;
	y = 0;
	f = false;
	ground = 0;
	onladder = 0;
	downjump = false;
	pdelay = 0;
	plo = 0;
	plb = 0;
	porange = 0;
	pblue = 0;
}

void this_player::checkPortal(bool up, int dir) {
	for(auto i = portals.begin();i!=portals.end();i++) {
		auto other = *i;
		switch(other->pt) {
		case 1:
			if (pdelay > 500 && up && x<other->x+20 && x > other->x-20 && y<other->y+20 && y > other->y-20) {
				pdelay = 0;
				if (Map::currentmap == tostring(other->tm)) {
					for(auto j = portals.begin();j!=portals.end();j++) {
						auto link = *j;
						if (other->tn == link->pn) {
							pdelay = 0;
							x = link->x;
							y = link->y-8;
							ground = 0;
							break;
						}
					}
				} else {
					Map::Load(tostring(other->tm), other->tn);
				}
			}
			break;
		case 2:
			if (pdelay > 500 && up && x<other->x+20 && x > other->x-20 && y<other->y+20 && y > other->y-20) {
				pdelay = 0;
				Map::Load(tostring(other->tm), other->tn);
			}
			break;
		case 3:
			if (x<other->x+50 && x > other->x-50 && y<other->y+50 && y > other->y-50) {
				if (Map::currentmap == tostring(other->tm)) {
					for(auto j = portals.begin();j!=portals.end();j++) {
						auto link = *j;
						if (other->tn == link->pn) {
							pdelay = 0;
							x = link->x;
							y = link->y-8;
							ground = 0;
							break;
						}
					}
				} else {
					Map::Load(tostring(other->tm), other->tn);
				}
			}
			break;
		case 10:
			other->close = false;
			if (x<other->x+100 && x > other->x-100 && y<other->y+100 && y > other->y-100) {
				other->close = true;
				if (pdelay > 500 && up && x<other->x+20 && x > other->x-20 && y<other->y+20 && y > other->y-20) {
					for(auto j = portals.begin();j!=portals.end();j++) {
						auto link = *j;
						if (other->tn == link->pn) {
							pdelay = 0;
							x = link->x;
							y = link->y-8;
							ground = 0;
							break;
						}
					}
				}
			}
			break;
		case 12:
			if (vel.ycomp() > 0 && x<other->x+40 && x > other->x-40 && y<other->y+10 && y > other->y-10) {
				vel.xcomp(300*dir);
				vel.ycomp(-2200);
			}
			break;
		case 13:
			if (x<other->x+40 && x > other->x-40 && y<other->y+10 && y > other->y-10) {
				vel.xcomp(other->hi*dir);
				vel.ycomp(-other->vi);
			}
			break;
		}
		
	}
}

void this_player::draw() {
	current = this;
	resort = false;
	pdelay += delta;
	//Setup control stuff
	bool left, right, up, down, jump;
	left = Input::Key[SDLK_LEFT];
	right = Input::Key[SDLK_RIGHT];
	up = Input::Key[SDLK_UP];
	down = Input::Key[SDLK_DOWN];
	jump = Input::Key[SDLK_LALT] || Input::Key[SDLK_RALT];
	//Direction facing
	if (!onladder) {
		if (left) {
			f = false;
		}
		if (right) {
			f = true;
		}
	}
	//Check for ladders
	//Friction and movement and stuff
	double xprev = x;
	double yprev = y;
	if (!onladder) {
		if (ground) {
			if (ground->walk) {
				vel.limit(ground->dir);
				double force = walkSpeed*(right-left)+ground->force;
				double s1 = vel.getd(ground->dir) - force;
				double fs = 0.01;
				double nspd;
				if (force) {
					nspd = max(abs(s1)-(fs*double(delta)*walkForce/1000), (double)0)*sign(s1)+force;
				} else {
					nspd = max(abs(s1)-(fs*double(delta)*walkDrag/1000), (double)0)*sign(s1)+force;
				}
				vel.set(nspd, ground->dir);
				if (jump) {
					if (down && !ground->forbid) {
						bool has = false;
						for (auto i = footholds.begin(); i != footholds.end(); i++) {
							if ((*i)!=ground && (*i)->x1 <= x && (*i)->x2 >= x && (*i)->y1 > y && (*i)->y2 > y && (*i)->y1<y+600 && (*i)->y2<y+600) {
								has = true;
							}
						}
						// Just to be sure there is a foothold underneath the character.
						if (has) {
							vel.ycomp(-jumpSpeed/2);
							vel.xcomp(0);
							downjump = ground;
							ground = 0;
						}
					} else {
						vel.ycomp(-jumpSpeed);
						ground = 0;
					}
				}
			} else {
				vel.limit(ground->dir);
				vel.add(gravityAcc*double(delta)/1000, 90);
				if (angdif(vel.direction(), ground->dir) > 0) {
					ground = 0;
				} else if (right && ground->dir > 0) {
					ground = 0;
				} else if (left && ground->dir<0) {
					ground = 0;
				} else if (abs(angdif(ground->dir, 180))<89) {
					ground = 0;
				}
			}
		} else {
			vel.add(gravityAcc*double(delta)/1000, 90);
			double force = walkSpeed*(right-left);
			double drag = floatDrag1;
			if (force && sign(vel.xcomp()) == sign(force) && abs(vel.xcomp())<abs(force)) {
				drag = floatDrag2;
			}
			drag /= 1000000;
			vel.xcomp(max(abs(vel.xcomp()-force)-(double(delta)*drag), (double)0)*sign(vel.xcomp()-force)+force);
			vel.ycomp(min(fallSpeed, vel.ycomp()));
		}
		//Move the player
		x += vel.xcomp()*double(delta)/1000;
		y += vel.ycomp()*double(delta)/1000;
		//Check for end of foothold bounds
		if (ground) {
			if (psqdis(x, y, ground->x1, ground->y1) > ground->len*ground->len) {
				if (ground->next) {
					if (ground->walk) {
						if (ground->next->walk) {
							ground = ground->next;
							x = ground->x1;
							y = ground->y1;
							x += ldx(1, ground->dir);
						} else if (angdif(ground->dir, ground->next->dir)<0) {
							ground = 0;
						} else {
							x = ground->x2-0.1;
							y = ground->y2;
						}
					} else {
						if (angdif(ground->dir, ground->next->dir)<0) {
							ground = 0;
						} else {
							ground = ground->next;
							x = ground->x1;
							y = ground->y1;
							x += ldx(1, ground->dir);
						}
					}
				} else {
					ground = 0;
				}
			} else if (psqdis(x, y, ground->x2, ground->y2) > ground->len*ground->len) {
				if (ground->prev) {
					if (ground->walk) {
						if (ground->prev->walk) {
							ground = ground->prev;
							x = ground->x2;
							y = ground->y2;
							x -= ldx(1, ground->dir);
						} else if (angdif(ground->dir, ground->prev->dir) > 0) {
							ground = 0;
						} else {
							x = ground->x1+0.1;
							y = ground->y1;
						}
					} else {
						if (angdif(ground->dir, ground->prev->dir) > 0) {
							ground = 0;
						} else {
							ground = ground->prev;
							x = ground->x2;
							y = ground->y2;
							x -= ldx(1, ground->dir);
						}
					}
				} else {
					ground = 0;
				}
			}
		}
		//Check for collisions
		if (!ground && !onladder) {
			double dis = vel.speed()*double(delta)/1000;
			//Iterate through all footholds
			for (auto i = footholds.begin(); i != footholds.end(); i++) {
				auto other = *i;
				if (!other->walk && group!=other->group) {continue;}
				double a1 = angdif(vel.direction(), other->dir);
				if (a1 <= 0) {continue;}
				double a2 = angdif(vel.direction(), pdir(x, y, other->x1, other->y1));
				if (a2 >= 0) {continue;}
				double a3 = angdif(vel.direction(), pdir(x, y, other->x2, other->y2));
				if (a3 <= 0) {continue;}
				double d1 = pdis(xprev, yprev, other->x1, other->y1);
				double a4 = angdif(other->dir+90, pdir(xprev, yprev, other->x1, other->y1));
				double d2 = ldx(d1, a4);
				if (d2<0) {continue;}
				if (d2 <= dis) {
					if (downjump && downjump->group == other->group) {
						downjump = 0;
						continue;
					}
					ground = other;
					dis = d2;
				}
			}
			//Deal with the foothold of interest
			if (ground) {
				//double a5 = angdif(ground->dir+90, vel.direction());
				//double d3 = dis/ldx(1, a5);
				x = xprev+ldx(dis, vel.direction());
				y = yprev+ldy(dis, vel.direction());
				vel.limit(ground->dir);
				if (ground->walk) {
					x = max(min(x, ground->x2-0.1), ground->x1+0.1);
				}
				group = ground->group;
				if (z[1] != ground->layer) {
					z[1] = ground->layer;
					resort = true;
				}
			}
		}
	}
	else {
		vel.set(0, 0);
		x = onladder->x;
		vel.ycomp(120*(down-up));
		if (!(up ^ down)) {
			delay -= delta;
		}
		if (up && y <= onladder->y1) {
			if (onladder->uf) {
				onladder = 0;
			} else {
				y = onladder->y1;
				vel.set(0, 0);
				if (up ^ down) {
					delay -= delta;
				}
			}
		}
		if (onladder && y > onladder->y2) {
			onladder = 0;
		}
		if ((left ^ right) && jump) {
			onladder = 0;
			vel.xcomp(right*125-left*125);
			vel.ycomp(-jumpSpeed/2);
			x += right*10-left*10;
		}
		x += vel.xcomp()*double(delta)/1000;
		y += vel.ycomp()*double(delta)/1000;
	}
	if ((up || down) && !onladder) {
		for (auto i = ladders.begin(); i != ladders.end(); i++) {
			ladder *_ladder = *i;//if(other.y > y1) if (other.y<y2+5)
			if ((x > _ladder->x - 8 && x < _ladder->x + 8) &&
				((up && y > _ladder->y1 && y<_ladder->y2+5) ||
				(down && y > _ladder->y1-5 && y<_ladder->y1+5))) {
				this->onladder = _ladder;
				this->ground = 0;
				this->x = _ladder->x;
				this->vel.set(0, 0);
				this->z[1] = _ladder->page;
				resort = true;
				if (up) {
					this->y = min(max(y, _ladder->y1+1), _ladder->y2);
				} else {
					this->y = _ladder->y1+1;
				}
				break;
			}
		}
	}
	//Mouse fly
	if (Input::Key[SDLK_f]) {
		x = Mouse::x + view.x;
		y = Mouse::y + view.y;
		vel.set(0, 0);
		ground = 0;
		onladder = 0;
	}
	this_player::checkPortal(up, (int)f*2-1);
	if (Input::Key[SDLK_d]) {
			Game::DevPortals = !Game::DevPortals;
	}
	//Final bounds check
	double ox = x;
	x = max(min(x, view.xmax-25), view.xmin+25);
	if (ground && ox!=x) {
		y = yprev+vel.ycomp()*sqr(((ox-xprev)/vel.xcomp()));
	}
	y = max(y, view.ymin);
	if (y > view.ymax) {
		x = 0;
		y = 0;
	}
	//Set the view
	view.tx = x-400;
	view.ty = y-350;
	//Set the state
	state = "jump";
	if (ground && ground->walk) {
		state = "stand1";
		if (left ^ right) {
			state = "walk1";
		}
		else if (down) {
			state = "prone";
		}
	}
	else if (onladder) {
		if (onladder->l) {
			state = "ladder";
		} else {
			state = "rope";
		}
	}
	if (mindfuck) {
		if (random(1) > 0.995) {
			x = random(view.xmax-view.xmin)+view.xmin;
			y = random(view.ymax-view.ymin)+view.ymin;
			ground = 0;
			onladder = 0;
		}
	}
	if (emote != "default") {
		emodelay += delta;
		emoend += delta;
		double d = wz::top["Character"]["Face"][tostring(stats.face, 8)][emote][tostring(emoframe)]["delay"];
		if (emodelay >= d) {
			emoframe++;
			emodelay = 0;
			if (!wz::top["Character"]["Face"][tostring(stats.face, 8)][emote][tostring(emoframe)]) {
				emoframe = 0;
			}
		}
		if (emoend >= emotime) {
			emote = "default";
		}
	}
	//emotes
#define setemote(emo)\
	emote = emo;\
	emodelay = 0;\
	emoframe = 0;\
	emoend = 0;
	if (Input::Key[SDLK_F1]) {
		setemote("hit");
	} else if (Input::Key[SDLK_F2]) {
		setemote("smile");
	} else if (Input::Key[SDLK_F3]) {
		setemote("troubled");
	} else if (Input::Key[SDLK_F4]) {
		setemote("cry");
	} else if (Input::Key[SDLK_F5]) {
		setemote("angry");
	} else if (Input::Key[SDLK_F6]) {
		setemote("bewildered");
	} else if (Input::Key[SDLK_F7]) {
		setemote("stunned");
	} else if (Input::Key[SDLK_F8]) {
		setemote("vomit");
	} else if (Input::Key[SDLK_F9]) {
		setemote("oops");
	} else if (Input::Key[SDLK_F10]) {
		setemote("cheers");
	} else if (Input::Key[SDLK_F11]) {
		setemote("chu");
	} else if (Input::Key[SDLK_F12]) {
		setemote("wink");
	} else if (Input::Key[SDLK_1]) {
		setemote("pain");
	} else if (Input::Key[SDLK_2]) {
		setemote("glitter");
	} else if (Input::Key[SDLK_3]) {
		setemote("despair");
	} else if (Input::Key[SDLK_4]) {
		setemote("love");
	} else if (Input::Key[SDLK_5]) {
		setemote("shine");
	} else if (Input::Key[SDLK_6]) {
		setemote("blaze");
	} else if (Input::Key[SDLK_7]) {
		setemote("hum");
	} else if (Input::Key[SDLK_8]) {
		setemote("bowing");
	} else if (Input::Key[SDLK_9]) {
		setemote("hot");
	} else if (Input::Key[SDLK_0]) {
		setemote("dam");
	} else if (Input::Key[SDLK_MINUS]) {
		setemote("qBlue");
	}
	//And we be done
	player::draw();
}

void this_player::getequips (queue<wz::node>& parts) {
	parts.push(wz::top["Character"]["0000" + tostring(stats.skin)][state][tostring(frame)]);
	parts.push(wz::top["Character"]["0001" + tostring(stats.skin)][state][tostring(frame)]);
	parts.push(wz::top["Character"]["Hair"][tostring(stats.hair, 8)][state][tostring(frame)]);
	if (int(wz::top["Character"]["0000" + tostring(stats.skin)][state][tostring(frame)]["face"])) {
		if (emote == "default") {
			parts.push(wz::top["Character"]["Face"][tostring(stats.face, 8)][emote]);
		} else {
			parts.push(wz::top["Character"]["Face"][tostring(stats.face, 8)][emote][tostring(emoframe)]);
		}
	}
	if(stats.equips.clothes<1050000){
		parts.push(wz::top["Character"]["Coat"][tostring(stats.equips.clothes, 8)][state][tostring(frame)]);
	} else {
		parts.push(wz::top["Character"]["Longcoat"][tostring(stats.equips.clothes, 8)][state][tostring(frame)]);
	}
	parts.push(wz::top["Character"]["Pants"][tostring(stats.equips.pants, 8)][state][tostring(frame)]);
	parts.push(wz::top["Character"]["Cap"][tostring(stats.equips.cap, 8)][state][tostring(frame)]);
	parts.push(wz::top["Character"]["Shoes"][tostring(stats.equips.shoes, 8)][state][tostring(frame)]);
}