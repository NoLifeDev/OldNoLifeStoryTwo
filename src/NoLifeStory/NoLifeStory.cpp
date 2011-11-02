////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

#ifdef NLS_MSVC
int main(int argc, wchar_t **argv) {
#else
int main(int argc, char **argv) {
#endif
	NLS::Init(vector<ustring>(argv, argv+argc));
	while (NLS::Loop()) {}
	NLS::Unload();
	return 0;
}
