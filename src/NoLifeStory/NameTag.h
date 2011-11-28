////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
namespace NLS {
	class NameTag {
	public:
		void Set(const string&);
		void Draw(int x, int y);
	private:
		Text t;
	};
}