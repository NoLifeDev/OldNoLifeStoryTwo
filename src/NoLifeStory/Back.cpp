////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

set <NLS::Back*> NLS::Back::Backs;

void NLS::Back::Load(Node n) {
	for (auto it = Backs.begin(); it != Backs.end(); it++) {
		delete *it;
	}
	Backs.clear();
	n = n["back"];
	for (auto it = n.Begin(); it != n.End(); it++) {
		Node bn = it->second;
		string type1 = bn["bS"];
		string type2 = bn["no"];
		Back* b = new Back;
		b->x = bn["x"];
		b->y = bn["y"];
		b->z = toint(it->first);
		b->f = (int)bn["f"];
		b->ani = (int)bn["ani"];
		b->cx = bn["cx"];
		b->cy = bn["cy"];
		b->rx = bn["rx"];
		b->ry = bn["ry"];
		b->type = bn["type"];
		Node bd = WZ::Top["Map"]["Back"][type1];
		if (!bd) {
			C("ERROR") << "Failed to find background type " << type1 << endl;
			delete b;
			continue;
		}
		if (b->ani) {
			bd = bd["ani"][type2];
			b->aspr.Set(bd);
			bd = bd[0];
			if (b->cx == 0) {
				b->cx = Sprite(bd).data->width;
			}
			if (b->cy == 0) {
				b->cy = Sprite(bd).data->height;
			}
		} else {
			bd = bd["back"][type2];
			b->spr = bd;
			if (b->cx == 0) {
				b->cx = Sprite(bd).data->width;
			}
			if (b->cy == 0) {
				b->cy = Sprite(bd).data->height;
			}
		}
		b->movetype = bd["moveType"];
		b->movew = bd["moveW"];
		b->moveh = bd["moveH"];
		b->movep = bd["moveP"];
		b->mover = bd["moveR"];
		if ((int)bn["front"]) {
			Map::Foregrounds.push_back(b);
		} else {
			Map::Backgrounds.push_back(b);
		}
		Backs.insert(b);
	}
	sort(Map::Backgrounds.begin(), Map::Backgrounds.end(), [](Back* b1, Back* b2){return b1->z < b2->z;});
	sort(Map::Foregrounds.begin(), Map::Foregrounds.end(), [](Back* b1, Back* b2){return b1->z < b2->z;});
}

void NLS::Back::Draw() {
	int ogx, ogy;
	if (ani) {
		aspr.Step();
		ogx = Sprite(aspr.f).data->originx;
		ogy = Sprite(aspr.f).data->originy;
	} else {
		ogx = spr.data->originx;
		ogy = spr.data->originy;
	}
	int ax = 0;
	int ay = 0;
	double ang = 0;
	switch(movetype) {
	case 1:
		if (movep) {
			ax = movew*sin((double)Time.tdelta*2*PI/movep);
		} else {
			ax = movew*sin((double)Time.tdelta/1000);
		}
		break;
	case 2:
		if (movep) {
			ay = moveh*sin((double)Time.tdelta*2*PI/movep);
		} else {
			ay = moveh*sin((double)Time.tdelta/1000);
		}
		break;
	case 3:
		ang = (double)Time.tdelta/mover*radtodeg;
		break;
	};
	int ox = (100+rx)*(View.x+400)/100;
	int oy = (100+ry)*(View.y+300)/100;
	int orx = ogx-ogx%cx;
	int ory = ogy-ogy%cy;
	auto draw = [&](int x, int y, bool flipped, float rotation) {
		if (ani) {
			aspr.Draw(x, y, flipped, rotation);
		} else {
			spr.Draw(x, y, flipped, 1, rotation);
		}
	};
	//TODO - Look into drawing a single tiled primitive when cx/cy = width/height
	auto drawhorz = [&]() {
		for(int i = (x+ax-View.x+ox+orx)%cx-cx+View.x-ox; i+ox < View.x+800+cx+orx; i += cx) {
			draw(i+ox, y+oy+ay, f, ang);
		}
	};
	auto drawvert = [&]() {
		for(int j = (y+ay-View.y+oy+ory)%cy-cy+View.y-oy; j+oy < View.y+600+cy+ory; j += cy) {
			draw(x+ox+ax, j+oy, f, ang);
		}
	};
	auto drawboth = [&]() {
		for(int i = (x+ax-View.x+ox+orx)%cx-cx+View.x-ox; i+ox < View.x+800+cx+orx; i += cx) {
			for(int j = (y+ay-View.y+oy+ory)%cy-cy+View.y-oy; j+oy < View.y+600+cy+ory; j += cy) {
				draw(i+ox, j+oy, f, ang);
			}
		}
	};
	switch(type) {
	case 0:
		draw(x+ox+ax, y+oy+ay, f, ang);
		break;
	case 1:
		drawhorz();
		break;
	case 2:
		drawvert();
		break;
	case 3:
		drawboth();
		break;
	case 4:
		ax += Time.tdelta*rx/200;
		drawhorz();
		break;
	case 5:
		ay += Time.tdelta*ry/200;
		drawvert();
		break;
	case 6:
		ax += Time.tdelta*rx/200;
		drawboth();
		break;
	case 7:
		ay += Time.tdelta*ry/200;
		drawboth();
		break;
	default:
		C("WZ") << "Unknown background type " << type << endl;
		throw(273);
		break;
	}

}