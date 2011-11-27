////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

const double fallSpeed = 670;
const double floatCoefficient = 0.01;
const double floatDrag1 = 100000;
const double floatDrag2 = 10000;
const double flyForce = 120000;
const double flyJumpDec = 0.35;
const double flySpeed = 200;
const double gravityAcc = 2000;
const double jumpSpeed = 555;
const double maxFriction = 2;
const double minFriction = 0.05;
const double slipForce = 60000;
const double slipSpeed = 120;
const double swimForce = 120000;
const double swimSpeed = 140;
const double swimSpeedDec = 0.9;
const double walkDrag = 80000;
const double walkForce = 140000;
const double walkSpeed = 125;
const double wat1 = 0.0008928571428571428;
const double wat2 = 0.35355339;
const double wat3 = 700;
const double wat4 = 162.5;

namespace shoe {
    const double mass = 100.0;
    const double walkAcc = 1.0;
    const double walkSpeed = 1.4;//Max haste?
    const double walkDrag = 1.0;
    const double walkSlant = 0.9;
    const double walkJump = 1.2;//Max haste?
    const double swimAcc = 1.0;
    const double swimSpeedH = 1.0;
    const double swimSpeedV = 1.0;
    const double flyAcc = 0.0;
    const double flySpeed = 0.0;
};

void NLS::Physics::Init() {
	Node n = WZ["Map"]["Physics"];
}

NLS::Physics::Physics() : notAPlayer(false), speedMin(0) {
	Reset(0, 0);
}

NLS::Physics::Physics(double x, double y) : notAPlayer(false), speedMin(0) {
	Reset(x, y);
}

void NLS::Physics::Reset(double x, double y) {
	this->x = x;
	this->y = y;
	r = 0;
	vx = 0;
	vy = 0;
	vr = 0;
	fh = nullptr;
	lr = nullptr;
	layer = 0;
	group = 0;
	freefall = 0;
	djump = nullptr;
}

void NLS::Physics::Update() {
	if (!lr) {
		f = left&&!right?false:right&&!left?true:f;
	}
	bool moving = left^right;
	bool flying = (int)Map::node["info"]["swim"] or shoe::flyAcc > 0;
	if (!lr) {
		auto Check = [&](double y)->void{
			for (auto it = LadderRope::begin(); it != LadderRope::end(); ++it) {
				LadderRope& lr = **it;
				const double d = 5;
				if (x+d > lr.x and x-d < lr.x and y > lr.y1 and y < lr.y2) {
					this->fh = nullptr;
					this->lr = &lr;
					this->x = lr.x;
					this->y = y;
					return;
				}
			}
		};
		if (fh) {
			if (up) {
				Check(y-20);
			}
			if (down and !lr) {
				Check(y+10);
			}
		} else if (up) {
			Check(y);
		}
	}
	if (fh) {
		vr -= fh->force;
		double fs = 1/shoe::mass;
		if (Map::node["info"]["fs"]) {
			fs *= (double)Map::node["info"]["fs"];
		}
		int dir = left&&!right?-1:right&&!left?1:0;
		double slip = abs(fh->y1-fh->y2)/fh->len;
		double maxl = sqr(slip);
		double maxh = fh->walk?shoe::walkAcc*walkForce:0;
		int hd = fh->y1<fh->y2?1:-1;
		double force = dir*maxh;
		double maxf = fh->walk ? shoe::walkSpeed * (walkSpeed - speedMin) : 0;
		if (flying) {
			maxf *= swimSpeedDec;
		}
		force *= fh->y1>fh->y2?1-maxl:1+maxl;
		double drag = shoe::walkDrag;
		drag = drag>maxFriction?maxFriction:drag<minFriction?minFriction:drag;
		if (drag < 1) {
			drag *= 0.5;
		}
		double fslip = drag*walkDrag;
		double drag2 = walkDrag/5;
		if (slip == 0) {
			if (vr < -maxf) {
				vr = min(-maxf, vr+drag2*fs*Time::delta);
			} else if (vr > maxf) {
				vr = max(maxf, vr-drag2*fs*Time::delta);
			}
			if (!moving) {
				if (vr < 0) {
					vr = min(0., vr+fslip*fs*Time::delta);
				} else {
					vr = max(0., vr-fslip*fs*Time::delta);
				}
			} else {
				if (force < 0) {
					if (vr > -maxf) {
						vr = max(-maxf, vr+force*fs*Time::delta);
					}
				} else {
					if (vr < maxf) {
						vr = min(maxf, vr+force*fs*Time::delta);
					}
				}
			}
		} else {
			maxh = maxf;
			maxl = (maxl+1)*maxf;
			if (hd*vr > 0) {
				maxl = maxh;
			}
			if (vr > maxl) {
				vr = max(maxl, vr-drag2*fs*Time::delta);
			} else if (vr < -maxl) {
				vr = min(maxl, vr+drag2*fs*Time::delta);
			}
			if (shoe::walkSlant < slip) {
				fslip = slip*slipForce*hd;
				slip = slip*slipSpeed*hd;
				if (dir*hd <= 0) {
					if (moving) {
						fslip += force;
						slip += maxl;
					}
				} else {
					fslip *= 0.5;
					slip *= 0.5;
				}
				if (hd*dir < 0) {
					if (vr < 0) {
						vr = min(0., vr-drag2*fs*Time::delta);
					} else {
						vr = max(0., vr+drag2*fs*Time::delta);
					}
				}
				if (hd < 0) {
					if (vr > slip) {
						vr = max(slip, vr+fslip*fs*Time::delta);
					}
				} else {
					if (vr < slip) {
						vr = min(slip, vr+fslip*fs*Time::delta);
					}
				}
			} else {
				if (moving) {
					double fmax = hd*force>0?maxh:maxl;
					if (force < 0) {
						if (vr > -maxf) {
							vr = max(-fmax, vr+force*fs*Time::delta);
						}
					} else {
						if (vr < maxf) {
							vr = min(fmax, vr+force*fs*Time::delta);
						}
					}
				} else {
					if (vr < 0) {
						vr = min(0., vr+fslip*fs*Time::delta);
					} else {
						vr = max(0., vr-fslip*fs*Time::delta);
					}
				}
			}
		}
		vr += fh->force;
	} else if (lr) {
		vx = 0;
		vy = 0;
		if (up&&!down) {
			y -= Time::delta*shoe::mass;
		} else if (down&&!up) {
			y += Time::delta*shoe::mass;
		}
		if (y < lr->y1) {
			if (lr->uf) {
				if (notAPlayer) {
					left = right = false;
				}
				else {
					y = lr->y1-5;
					lr = nullptr;
				}
			} else {
				y = lr->y1;
			}
		} else if (y > lr->y2) {
			if (notAPlayer) {
				left = right = false;
			}
			else {
				y = lr->y2+1;
				lr = nullptr;
			}
		}
	} else {
		if (flying) {
			double vmid, vmax;
			if ((int)Map::node["info"]["swim"]) {
				vmid = shoe::swimAcc;
				vmax = shoe::swimSpeedH*swimSpeed;
			} else {
				vmid = shoe::flyAcc;
				vmax = shoe::flySpeed*flySpeed;
			}
			if (vx < -vmax) {
				vx = min(-vmax, vx+floatDrag1/shoe::mass*Time::delta);
			} else if (vx > vmax) {
				vx = max(vmax, vx-floatDrag1/shoe::mass*Time::delta);
			}
			if (moving) {
				if (left) {
					if (vx > -vmax) {
						vx = max(-vmax, vx-floatDrag1/shoe::mass*Time::delta);
					}
				} else {
					if (vx < vmax) {
						vx = min(vmax, vx+floatDrag1/shoe::mass*Time::delta);
					}
				}
			} else {
				if (vx > 0) {
					vx = max(0., vx-floatDrag1/shoe::mass*Time::delta);
				} else {
					vx = min(0., vx+floatDrag1/shoe::mass*Time::delta);
				}
			}
			if (vx < -vmax) {
				vx = min(-vmax, vx+floatDrag1/shoe::mass*Time::delta);
			} else if (vx > vmax) {
				vx = max(vmax, vx-floatDrag1/shoe::mass*Time::delta);
			}
			double stuff = flyForce/shoe::mass*vmid;
			if (up^down) {
				if (up) {
					if (vy < vmax*0.3) {
						vy = min(vmax*0.3, vy+stuff*Time::delta*0.5);
					} else {
						vy = max(vmax*0.3, vy-stuff*Time::delta);
					}
				} else {
					if (vy < vmax*1.5) {
						vy = min(vmax*1.5, vy+stuff*Time::delta);
					} else {
						vy = max(vmax*1.5, vy-stuff*Time::delta*0.5);
					}
				}
			} else if (vy < vmax) {
				vy = min(vmax, vy+stuff*Time::delta);
			}
		} else {
			if (vy > 0.) {
				vy = max(0., vy-floatDrag2/shoe::mass*Time::delta);
			} else {
				vy = min(0., vy+floatDrag2/shoe::mass*Time::delta);
			}
			vy += gravityAcc*Time::delta;
			vy = max(min(vy, fallSpeed), -fallSpeed);
			if (moving) {
				double l = floatDrag2*wat1;
				if (left) {
					if (vx > -l) {
						vx = max(-l, vx-floatDrag2*2/shoe::mass*Time::delta);
					}
				} else {
					if (vx < l) {
						vx = min(l, vx+floatDrag2*2/shoe::mass*Time::delta);
					}
				}
			} else {
				if (vy < fallSpeed) {
					if (vx > 0) {
						vx = max(0., vx-floatDrag2*floatCoefficient/shoe::mass*Time::delta);
					} else {
						vx = min(0., vx+floatDrag2*floatCoefficient/shoe::mass*Time::delta);
					}
				} else {
					if (vx > 0) {
						vx = max(0., vx-floatDrag2/shoe::mass*Time::delta);
					} else {
						vx = min(0., vx+floatDrag2/shoe::mass*Time::delta);
					}
				}
			}
		}
	}
	if (fh) {
		double rp = r;
		r += vr*Time::delta;
		if (r > fh->len) {
			if (fh->next) {
				if (fh->next->walk) {
					r = r-fh->len;
					fh = fh->next;
				} else if (fh->next->y2 > fh->next->y1) {
					x = fh->x2+0.1;
					y = fh->y2+0.1;
					vx = ldx(vr, fh->dir);
					vy = ldy(vr, fh->dir);
					fh = nullptr;
				} else {
					r = fh->len-0.1;
					vr = 0;
				}
			} else {
				x = fh->x2+0.1;
				y = fh->y2+0.1;
				vx = ldx(vr, fh->dir);
				vy = ldy(vr, fh->dir);
				fh = nullptr;
			}
		} else if (r < 0) {
			if (fh->prev) {
				if (fh->prev->walk) {
					fh = fh->prev;
					r = r+fh->len;
				} else if (fh->prev->y2 < fh->prev->y1) {
					x = fh->x1-0.1;
					y = fh->y1-0.1;
					vx = ldx(vr, fh->dir);
					vy = ldy(vr, fh->dir);
					fh = nullptr;
				} else {
					r = 0.1;
					vr = 0;
				}
			} else {
				x = fh->x1-0.1;
				y = fh->y1-0.1;
				vx = ldx(vr, fh->dir);
				vy = ldy(vr, fh->dir);
				fh = nullptr;
			}
		}
	} else if (!lr) {
		double xp = x;
		double yp = y;
		x += vx*Time::delta;
		y += vy*Time::delta;
		double dis = pdis(vx, vy)*Time::delta;
		double dir = pdir(vx, vy);
		for (auto it = Foothold::begin(); it != Foothold::end(); ++it) {
			Foothold& o = **it;
			if (djump == &o) continue;
			if (!o.walk and group != o.group and o.group != 0) continue;
			if (angdif(dir, o.dir) < 0) continue;
			if (angdif(dir, pdir(xp, yp, o.x1, o.y1)) > 0) continue;
			if (angdif(dir, pdir(xp, yp, o.x2, o.y2)) < 0) continue;
			double dt = ldy(pdis(xp, yp, o.x1, o.y1), angdif(o.dir, pdir(o.x1, o.y1, xp, yp)));
			double d = dt/cos(degtorad*angdif(dir, o.dir+90));
			if (d < 0 or d > dis) continue;
			fh = &o;
			dis = d;
		}
		if (fh) {
			lr = nullptr;
			vr = ldx(pdis(vx, vy), angdif(dir, fh->dir));
			x = xp+ldx(dis, dir);
			y = yp+ldy(dis, dir);
			r = pdis(fh->x1, fh->y1, x, y);
			djump = nullptr;
			if (fh->x1 > fh->x2) {
				vx = ldx(vr, fh->dir);
				vy = ldy(vr, fh->dir);
				fh = nullptr;
			} else if (fh->x1 == fh->x2) {
				vx = 0;
				if (fh->y1 < fh->y2) {
					x = fh->x1+0.1;
				} else {
					x = fh->x1-0.1;
				}
				if (vy < 0) {
					y = yp+vy*Time::delta;
				}
				fh = nullptr;
			} else {
				group = fh->group;
				layer = fh->layer;
			}
		}
	}
	if (fh) {
		x = fh->x1+ldx(r, fh->dir);
		y = fh->y1+ldy(r, fh->dir);
		if (x < View::xmin+16) {
			r += ldx(View::xmin+16.1-x, fh->dir);
			x = fh->x1+ldx(r, fh->dir);
			y = fh->y1+ldy(r, fh->dir);
			vr = 0;
		} else if (x > View::xmax-16) {
			r += ldx(View::xmax-16.1-x, fh->dir);
			x = fh->x1+ldx(r, fh->dir);
			y = fh->y1+ldy(r, fh->dir);
			vr = 0;
		}
	} else if (!lr) {
		if (vy < fallSpeed) {
			freefall = 0;
		} else {
			freefall += Time::delta;
		}
		if (y < View::ymin) {
			vy = 0;
			y = View::ymin;
		}
		if (x < View::xmin+16) {
			x = View::xmin+16.1;
			vx = 0;
		} else if (x > View::xmax-16) {
			x = View::xmax-16.1;
			vx = 0;
		}
	}
}

void NLS::Physics::MouseFly() {
	auto p = sf::Mouse::GetPosition(*window);
	Reset(p.x+View::x, p.y+View::y);
}

void NLS::Physics::Jump() {
	bool flying = (int)Map::node["info"]["swim"] or shoe::flyAcc > 0;
	if (fh) {
		if (down and !fh->forbid) {
			vy = -jumpSpeed*wat2;
			vx = 0;
			djump = fh;
			fh = nullptr;
		} else {
			vx = ldx(vr, fh->dir);
			vy = -shoe::walkJump*jumpSpeed;
			if (flying) {
				vy *= 0.7;
			}
			if (left^right) {
				double fmax = shoe::walkSpeed*(walkSpeed - speedMin);
				int dir = left?-1:1;
				fmax *= 1+sqr((fh->y2-fh->y1)/fh->len)*((fh->y2-fh->y1)*dir>0?1:-1);
				if (fmax*0.8 > dir*vx) {
					vx = dir*fmax*0.8;
				}
				if (fmax < dir*vx) {
					vx = dir*fmax;
				}
			}
			fh = nullptr;
		}
	} else if (lr) {
		if (left^right) {
			vy = shoe::walkJump*-jumpSpeed*(flying?0.3:0.5);
			vx = (left?-1:1)*shoe::walkSpeed*wat4;
			lr = nullptr;
		}
	} else if (flying) {
		vy = (int)Map::node["info"]["swim"]?-shoe::swimSpeedV*wat3:-shoe::flySpeed*flySpeed;
	}
}
