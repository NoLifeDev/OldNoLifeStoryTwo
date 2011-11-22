////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	namespace UI {
		class ChatLog : public Element {
		public:
			void Clear();
			void Draw(int x, int y);
			int GetWidth();
			int GetHeight();
			ChatLog& operator<< (u32string);
			ChatLog& operator<< (string);
			ChatLog& operator<< (ChatLog&(*)(ChatLog&));
		private:
			int Width;
			int Height;
			ChatLog(const ChatLog&);
			deque<u32string> Messages;
			ScrollBar Scroll;
			u32string Message;
		};
		extern ChatLog Messenger;
		extern ChatLog MainChat;
	}
	UI::ChatLog& endl(UI::ChatLog&);
}