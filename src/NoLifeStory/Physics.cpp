////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

const double walkForce = 140000;
const double walkSpeed = 125;
const double walkDrag = 80000;
const double slipForce = 60000;
const double slipSpeed = 120;
const double floatDrag1 = 100000;
const double floatDrag2 = 10000;
const double floatCoefficient = 0.01;
const double swimForce = 120000;
const double swimSpeed = 140;
const double flyForce = 120000;
const double flySpeed = 200;
const double gravityAcc = 2000;
const double fallSpeed = 670;
const double jumpSpeed = 555;
const double maxFriction = 2;
const double minFriction = 0.05;
const double swimSpeedDec = 0.9;
const double flyJumpDec = 0.35;
const double wat1 = 0.0008928571428571428;
const double wat2 = 0.35355339;
const double wat3 = 700;

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

NLS::Physics::Physics() {
	Reset(0, 0);
}

NLS::Physics::Physics(double x, double y) {
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
	f = left&&!right?false:right&&!left?true:f;
	bool moving = left^right;
	if (fh) {
		int dir = left&&!right?-1:right&&!left?1:0;
		double slip = abs(fh->y1-fh->y2)/fh->len;
		double maxl = sqr(slip);
		double maxh = fh->walk?(fh->force==0?shoe::walkAcc:1)*walkForce:0;
		int hd = fh->y1>fh->y2?1:-1;
		double force = dir*maxh;
		double maxf = fh->walk?shoe::walkSpeed*walkSpeed:0;
		if ((double)Map::node["info"]["fly"] < 0) {
			maxf *= swimSpeedDec;
		}
		if (fh->force) {
			if (moving) {
				double m = dir==sign(fh->force)?2*abs(fh->force):0.2/abs(fh->force);
				force *= m;
				maxf *= m;
			} else {
				force = fh->force*maxh;
			}
		}
		force *= fh->y1>fh->y2?1-maxl:1+maxl;
		double drag = fh->force==0?shoe::walkDrag:1;
		drag = drag>maxFriction?maxFriction:drag<minFriction?minFriction:drag;
		if (drag < 1) {
			drag *= 0.5;
		}
		double fslip = drag*walkDrag;
		double drag2 = walkDrag/5;
		if (slip == 0) {
			if (vr < -maxf) {
				vr = min(-maxf, vr+drag2/shoe::mass*Time.delta);
			} else if (vr > maxf) {
				vr = max(maxf, vr-drag2/shoe::mass*Time.delta);
			}
			if (!moving and fh->force == 0) {
				if (vr < 0) {
					vr = min(0, vr+fslip/shoe::mass*Time.delta);
				} else {
					vr = max(0, vr-fslip/shoe::mass*Time.delta);
				}
			} else {
				if (force < 0) {
					if (vr > -maxf) {
						vr = max(-maxf, vr+force/shoe::mass*Time.delta);
					}
				} else {
					if (vr < maxf) {
						vr = min(maxf, vr+force/shoe::mass*Time.delta);
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
				vr = max(maxl, vr-drag2/shoe::mass*Time.delta);
			} else if (vr < -maxl) {
				vr = min(maxl, vr+drag2/shoe::mass*Time.delta);
			}
			if (shoe::walkSlant < slip) {
				fslip = slip*slipForce*-hd;
				slip = slip*slipSpeed;
				if (dir*hd <= 0) {
					if (moving or fh->force != 0) {
						fslip += force;
						slip += maxl;
					}
				} else {
					fslip *= 0.5;
					slip *= 0.5;
				}
				if (hd*vr > 0) {
					if (vr < 0) {
						vr = min(0, vr-drag2/shoe::mass*Time.delta);
					} else {
						vr = max(0, vr+drag2/shoe::mass*Time.delta);
					}
				}
				if (fslip < 0) {
					if (vr > -slip) {
						vr = max(-slip, vr-fslip/shoe::mass*Time.delta);
					}
				} else {
					if (vr < slip) {
						vr = min(slip, vr+fslip/shoe::mass*Time.delta);
					}
				}
			} else {
				if (moving or fh->force != 0) {
					double fmax = hd*force>0?maxh:maxl;
					if (force < 0) {
						if (vr > -maxf) {
							vr = max(-fmax, vr+force/shoe::mass*Time.delta);
						}
					} else {
						if (vr < maxf) {
							vr = min(fmax, vr+force/shoe::mass*Time.delta);
						}
					}
				} else {
					if (vr < 0) {
						vr = min(0, vr+fslip/shoe::mass*Time.delta);
					} else {
						vr = max(0, vr-fslip/shoe::mass*Time.delta);
					}
				}
			}
		}
	} else {
		if (false) {
			//Underwater or flying...
		} else {
			if (vy > 0.) {
				vy = max(0., vy-floatDrag2/shoe::mass*Time.delta);
			} else {
				vy = min(0., vy+floatDrag2/shoe::mass*Time.delta);
			}
			vy += gravityAcc*Time.delta;
			vy = max(min(vy, fallSpeed), -fallSpeed);
			if (moving) {
				double l = floatDrag2*wat1;
				if (left) {
					if (vx > -l) {
						vx = max(-l, vx-floatDrag2*2/shoe::mass*Time.delta);
					}
				} else {
					if (vx < l) {
						vx = min(l, vx+floatDrag2*2/shoe::mass*Time.delta);
					}
				}
			} else {
				if (vy < fallSpeed) {
					if (vx > 0) {
						vx = max(0., vx-floatDrag2*floatCoefficient/shoe::mass*Time.delta);
					} else {
						vx = min(0., vx+floatDrag2*floatCoefficient/shoe::mass*Time.delta);
					}
				} else {
					if (vx > 0) {
						vx = max(0., vx-floatDrag2/shoe::mass*Time.delta);
					} else {
						vx = min(0., vx+floatDrag2/shoe::mass*Time.delta);
					}
				}
			}
		}
	}
	if (fh) {
		double rp = r;
		r += vr*Time.delta;
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
		x += vx*Time.delta;
		y += vy*Time.delta;
		double dis = pdis(vx, vy)*Time.delta;
		double dir = pdir(vx, vy);
		for (auto it = footholds.begin(); it != footholds.end(); it++) {
			Foothold& o = **it;
			if (djump == &o) continue;
			if (!o.walk && group != o.group) continue;
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
			vr = pdis(vx, vy)*sqr((fh->y2-fh->y1)/fh->len)*sign(fh->y2-fh->y1);
			x = xp+ldx(dis, dir);
			y = yp+ldy(dis, dir);
			r = pdis(fh->x1, fh->y1, x, y);
			djump = nullptr;
			if (fh->x1 > fh->x2) {
				fh = nullptr;
			} else if (fh->x1 == fh->x2) {
				vx = 0;
				if (fh->y1 < fh->y2) {
					x = fh->x1+0.1;
				} else {
					x = fh->x1-0.1;
				}
				y = yp+vy*Time.delta;
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
	} else if (lr) {
		//x = lr->x;
		//Something with y
	} else {
		if (vy < fallSpeed) {
			freefall = 0;
		} else {
			freefall += Time.delta;
		}
		if (y >= View.ymax and vy > 0) {
			vy = 0;
			y = View.ymax;
		}
	}
}

void NLS::Physics::MouseFly() {
	auto p = sf::Mouse::GetPosition(*window);
	Reset(p.x+View.x, p.y+View.y);
}

void NLS::Physics::Jump() {
	bool flying = (double)Map::node["info"]["fly"] < 0 or shoe::flyAcc > 0;
	if (fh) {//If we're on the ground
		if (down and !fh->forbid) {//If we can downjump
			vy = -jumpSpeed*wat2;
			vx = 0;
			djump = fh;
			fh = nullptr;
		} else {//Normal jump
			vx = ldx(vr, fh->dir);
			vy = -shoe::walkJump*jumpSpeed;
			if (flying) {
				vy *= 0.7;
			}
			if (left^right) {
				double fmax = shoe::walkSpeed*walkSpeed;
				int dir = left&&!right?-1:right&&!left?1:0;
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
	} else if (lr) {//If we're on a ladder
		if (left&&!right) {

		} else if (right&&!left) {

		}
	} else if (flying) {//Swimming or flying

	} else {
		//Nope, can't jump
	}
}