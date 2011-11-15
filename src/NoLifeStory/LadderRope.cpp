////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

set<NLS::LadderRope*> NLS::LadderRope::All;

void NLS::LadderRope::Load(Node n) {
	for_each(begin(), end(), [](LadderRope* lr){delete lr;});
	All.clear();
	n = n["ladderRope"];
	if (!n) return;
	for_each(n.begin(), n.end(), [](pair<string, Node> p){
		Node& n = p.second;
		LadderRope* lr = new LadderRope;
		lr->x = n["x"];
		lr->y1 = n["y1"];
		lr->y2 = n["y2"];
		lr->l = (int)n["l"];
		lr->uf = (int)n["uf"];
		lr->page = n["page"];
		All.insert(lr);
	});
}

void NLS::LadderRope::Draw() {
	glColor4f(1, 1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBegin(GL_LINES);
	for_each(begin(), end(), [](LadderRope* lr){
		glVertex2f(lr->x, lr->y1);
		glVertex2f(lr->x, lr->y2);
	});
	glEnd();
}