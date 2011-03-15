///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////

#ifdef _WIN32
#define NLS_WINDOWS
#elif defined(UNIX)
#define NLS_UNIX
#elif defined(MAC)
#define NLS_MAC
#else
#error "Unknown platform. Define either _WIN32, UNIX or MAC"
#endif