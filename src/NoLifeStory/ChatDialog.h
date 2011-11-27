////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	class ChatDialog {
	public:
		ChatDialog();
		void Draw();

	private:
		NLS::Sprite imgTop, imgMiddle, imgBottom;
		NLS::AniSprite npcImg;
		bool npcChat;
		string text, npcName;
		int32_t x, y;
		int32_t npcId;
	};
}