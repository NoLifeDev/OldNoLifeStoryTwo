////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
namespace NLS {
	class NameTag {
	public:
		enum Style {
			Normal,
			Life
		};
		void Set(const string&, Style);
		void Draw(int x, int y);
	private:
		Text t;
		Style s;
	};
}