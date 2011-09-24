////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	class Console {
	public:
		Console();
		~Console();
		void Loop();
		void HandleCommand(const string& command);
		void Push(const string& str);
		void Toggle();
	private:
		sf::RenderWindow* window;
		string str;
		int32_t pos;
		vector <string> strs;
		sf::Font* font;
		bool shutdown;
#ifdef VS11
		thread* t;
		mutex m;
#else
		sf::Thread* t;
		sf::Mutex m;
#endif
		bool toggle, show;
		ofstream file;
	};
	extern Console* console;
	class Stream {
	public:
		template <class T>
		Stream& operator << (T v) {
			line << v;
			return *this;
		}
		Stream& operator << (ostream&(ostream&)) {
			string s = line.str();
			if (!s.empty()) {
				console->Push(s);
				line.str("");
			}
			return *this;
		}
	private:
		stringstream line;
	};
	inline Stream& C(const string& type) {
		static Stream s;
		s << endl;
		s << type << ": ";
		return s;
	}
};