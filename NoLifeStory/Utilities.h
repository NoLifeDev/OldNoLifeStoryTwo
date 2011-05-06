///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////

#include <sys/stat.h>
#define PI 3.1415926535897932384626433832795
#define degtorad 0.01745329251994329576923690768489
#define radtodeg 57.295779513082320876798154814105

template <class T>
inline string tostring (const T& t) {
	stringstream ss;
	ss << t;
	return ss.str();
}

inline string tostring(const int& t) {
	char buffer[13];
	sprintf(buffer, "%i", t);
	return (string)buffer;
}

inline std::string tostring(const int& t, int len) {
	char buffer[13];
	sprintf(buffer, "%i", t);
	string str = buffer;
	while(str.size()<len) {
		str = "0"+str;
	}
	return str;
}

template <class T>
inline double toreal (const T& t) {
	std::stringstream ss;
	ss << t;
	double d;
	ss >> d;
	return d;
}

inline bool file_exists(string name) {
	fstream file(name);
	bool answer = file.is_open();
	file.close();
	return answer;
}

//inline bool file_exists(string strFilename) {
//	struct stat stFileInfo;
//	if (stat(strFilename.c_str(), &stFileInfo) == 0) {
//		return true;
//	} else {
//		return false;
//	}
//}

inline double sqr (double x) {
	return x*x;
}

inline double ldx (double len, double dir) {
	return cos(dir*degtorad)*len;
}

inline double ldy (double len, double dir) {
	return sin(dir*degtorad)*len;
}

inline double pdis (double x1, double y1, double x2, double y2) {
	return sqrt(sqr(x1-x2)+sqr(y1-y2));
}

inline double pdir (double x1, double y1, double x2, double y2) {
	return radtodeg*atan2(y2-y1, x2-x1);
}

inline double angdif (double angle1, double angle2) {
	return fmod(fmod(angle1-angle2, 360)+540, 360)-180;
}

inline double sign (double x) {
	if (x == 0) {
		return 0;
	}
	return x/abs(x);
}

inline double psqdis (double x1, double y1, double x2, double y2) {
	return sqr(x1-x2)+sqr(y1-y2);
}

inline double random (double x) {
	return double(rand())/RAND_MAX*x;
}

#ifdef _WIN32
inline void printRegisters(CONTEXT &ctx) {
	printf("Registers:\n");
	printf("Dr0: 0x%x\n", ctx.Dr0);
	printf("Dr1: 0x%x\n", ctx.Dr1);
	printf("Dr2: 0x%x\n", ctx.Dr2);
	printf("Dr3: 0x%x\n", ctx.Dr3);
	printf("Dr6: 0x%x\n", ctx.Dr6);
	printf("Dr7: 0x%x\n", ctx.Dr7);
	printf("EAX: 0x%x\n", ctx.Eax);
	printf("EBP: 0x%x\n", ctx.Ebp);
	printf("EBX: 0x%x\n", ctx.Ebx);
	printf("ECX: 0x%x\n", ctx.Ecx);
	printf("EDI: 0x%x\n", ctx.Edi);
	printf("EDX: 0x%x\n", ctx.Edx);
	printf("EIP: 0x%x\n", ctx.Eip);
	printf("ESI: 0x%x\n", ctx.Esi);
	printf("ESP: 0x%x\n", ctx.Esp);
	printf("Segment CS: 0x%x\n", ctx.SegCs);
	printf("Segment DS 0x%x\n", ctx.SegDs);
	printf("Segment ES: 0x%x\n", ctx.SegEs);
	printf("Segment FS: 0x%x\n", ctx.SegFs);
	printf("Segment GS: 0x%x\n", ctx.SegGs);
	printf("Segment SS: 0x%x\n", ctx.SegSs);
}
#endif

/**
 * Allocates a block of memory. Best to use page sizes, ie: 4096 bytes.
 * Uses HeapAlloc on windows, malloc in other operating systems.
 */
inline
#ifndef _WIN32
void *
#else
LPVOID
#endif
nlsMalloc(size_t size, bool zeroMemory = false) {
#ifndef _WIN32
	void *z = malloc(size);
#else
	LPVOID z = HeapAlloc(GetProcessHeap(), zeroMemory ? HEAP_ZERO_MEMORY : 0, size);
#endif
	if (!z) {
#ifndef _WIN32
		fprintf(stderr, "Out Of Memory - Exiting\n");
		exit(1);
#else
		WCHAR szMessageBuf[1024];
		CONTEXT ctx;
		ctx.ContextFlags = CONTEXT_ALL;
		GetThreadContext(GetCurrentThread(), &ctx);
		// write an error message to the console
		printRegisters(ctx);
		WCHAR szMessageFmt[] = TEXT("NoLifeStory encountered an out of memory error, in thread 0x%x, process 0x%x\nInstruction pointer was 0x%x, Base pointer was 0x%x\nMore debug information will be logged in the console.");
		wsprintf(szMessageBuf, szMessageFmt, GetCurrentThreadId(), GetCurrentProcessId(), ctx.Eip, ctx.Ebp);
		MessageBoxW(NULL, szMessageBuf, TEXT("Out Of Memory"), MB_OK | MB_ICONERROR);
		ExitProcess(1);
#endif
	}
	return z;
}

/**
 * Frees a block of memory. Uses HeapFree in windows, free in other operating systems.
 */
inline void nlsFree(
#ifndef _WIN32
void *memory
#else
LPVOID memory
#endif
) {
#ifndef _WIN32
	free(memory);
#else
	HeapFree(GetProcessHeap(), 0, memory);
#endif
}

/**
 * Reallocates a block of memory. Uses HeapReAlloc in windows, realloc in other operating systems.
 */
inline
#ifndef _WIN32
void *
#else
LPVOID
#endif
nlsReAlloc(
#ifndef _WIN32
void *memory
#else
LPVOID memory
#endif
, size_t size, bool zeroMemory = false) {
#ifndef _WIN32
	void *z = realloc(memory, size);
#else
	LPVOID z = HeapReAlloc(GetProcessHeap(), zeroMemory ? HEAP_ZERO_MEMORY : 0, memory, size);
#endif
	if (!z) {
#ifndef _WIN32
		fprintf(stderr, "Out Of Memory - Exiting\n");
		exit(1);
#else
		WCHAR szMessageBuf[1024];
		CONTEXT ctx;
		ctx.ContextFlags = CONTEXT_ALL;
		GetThreadContext(GetCurrentThread(), &ctx);
		// write an error message to the console
		printRegisters(ctx);
		WCHAR szMessageFmt[] = TEXT("NoLifeStory encountered an out of memory error, in thread 0x%x, process 0x%x\nInstruction pointer was 0x%x, Base pointer was 0x%x\nMore debug information will be logged in the console.");
		wsprintf(szMessageBuf, szMessageFmt, GetCurrentThreadId(), GetCurrentProcessId(), ctx.Eip, ctx.Ebp);
		MessageBoxW(NULL, szMessageBuf, TEXT("Out Of Memory"), MB_OK | MB_ICONERROR);
		ExitProcess(1);
#endif
	}
	return z;
}