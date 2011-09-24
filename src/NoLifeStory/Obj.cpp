////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

set <NLS::Obj*> NLS::Obj::Objs;

void NLS::Obj::Load(Node n) {
	for (auto it = Objs.begin(); it != Objs.end(); it++) {
		delete *it;
	}
	Objs.clear();
	for (uint8_t i = 0; i < 8; i++) {
		Node ln = n[i];
		if (!ln["obj"]) {
			continue;
		}
		for (auto it = ln["obj"].Begin(); it != ln["obj"].End(); it++) {
			Node on = it->second;
			string t1 = on["oS"];
			string t2 = on["l0"];
			string t3 = on["l1"];
			string t4 = on["l2"];
			Node od = WZ::Top["Map"]["Obj"][t1][t2][t3][t4];
			Obj* o = new Obj;
			o->x = on["x"];
			o->y = on["y"];
			o->z = on["z"];
			o->flow = (int)on["flow"];
			o->rx = on["rx"];
			o->ry = on["ry"];
			o->f = (int)on["f"];
			Node d = od[0];
			o->repeat = !(int)d["repeat"];
			o->movetype = d["moveType"];
			o->movew = d["moveW"];
			o->moveh = d["moveH"];
			o->movep = d["moveP"];
			o->mover = d["moveR"];
			o->spr.Set(od);
			o->spr.repeat = o->repeat;
			Map::Layers[i].Objs.push_back(o);
			Objs.insert(o);
		}
		sort(Map::Layers[i].Objs.begin(), Map::Layers[i].Objs.end(), [](Obj* o1, Obj* o2){return o1->z < o2->z;});
	}
}

void NLS::Obj::Draw() {
	spr.Step();
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
	if (flow) {
		ax += (double)Time.tdelta*rx/1000*5;
		//int cx = View.xmax-View.xmin;
		int cx = 800;//For now
		for(int i = (x+ax-View.x)%cx-cx+View.x; i < View.x+800+cx; i += cx) {
			spr.Draw(i, y+ay, f, ang);
		}
	} else {
		spr.Draw(x+ax, y+ay, f, ang);
	}
}