////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	class ChatLog {
	public:
		void Clear();
		ChatLog& operator<< (u32string) {return *this;}
		ChatLog& operator<< (string) {return *this;}
		ChatLog& operator<< (ChatLog&(*cl)(ChatLog&)) {return cl(*this);}
		deque<u32string> Messages;
		u32string Message;
	};
	extern ChatLog Messenger;
	extern ChatLog MainChat;
	inline ChatLog& cendl(ChatLog& cl) {return cl;}
}