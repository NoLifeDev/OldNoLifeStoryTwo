////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	class ChatLog {
	public:
		void Clear();
		ChatLog& operator<< (u32string);
		ChatLog& operator<< (string);
		ChatLog& operator<< (ChatLog&(*)(ChatLog&));
		deque<u32string> Messages;
		u32string Message;
	};
	extern ChatLog Messenger;
	extern ChatLog MainChat;
	ChatLog& endl(ChatLog&);
}