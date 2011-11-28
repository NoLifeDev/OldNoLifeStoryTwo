////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

NLS::ChatDialog::ChatDialog() {
	auto data = WZ["UI"]["UIWindow"]["UtilDlgEx"];
	imgTop = data["t"];
	imgMiddle = data["c"];
	imgBottom = data["s"];
	x = 800/2 - (imgTop.data->width / 2);
	y = 100;
	npcId = 9030000;
	npcImg.Set(WZ["Npc"][tostring(npcId)]["stand"]);
	npcName = WZ["String"]["Npc"][tostring(npcId)]["name"];
}

void NLS::ChatDialog::Draw() {
	npcImg.Step();
	imgTop.Draw(x, y);
	int32_t lines = 7;
	for (int32_t i = 0; i < lines; i++) {
		imgMiddle.Draw(x, y + imgTop.data->height + (i * imgMiddle.data->height));
	}
	imgBottom.Draw(x, y + imgTop.data->height + (lines * imgMiddle.data->height));
	npcImg.Draw(x + 70, y + imgTop.data->height + ((lines * imgMiddle.data->height) / 2) + 40, true);
	NLS::Sprite sprite = WZ["UI"]["UIWindow"]["UtilDlgEx"]["notice"];
	sprite.Draw(x + 170, y + imgTop.data->height);
}