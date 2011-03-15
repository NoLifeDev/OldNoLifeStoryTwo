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
	sprintf(buffer,"%i",t);
	return (string)buffer;
}
inline std::string tostring(const int& t, int len) {
	char buffer[13];
	sprintf(buffer,"%i",t);
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

inline bool file_exists(string strFilename) {
	struct stat stFileInfo;
	if (stat(strFilename.c_str(),&stFileInfo) == 0) {
		return true;
	} else {
		return false;
	}
}

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
	return radtodeg*atan2(y2-y1,x2-x1);
}
inline double angdif (double angle1, double angle2) {
	return fmod(fmod(angle1-angle2,360)+540,360)-180;
}
inline double sign (double x) {
	if(x==0) {
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

inline void* nlsMalloc(size_t size, bool zeroMemory = false) {
	void *z = malloc(size);
	if (!z) {
		fprintf(stderr, "Out Of Memory - Exiting\n");
		exit(1);
	}
	return z;
}

inline void nlsFree(void *memory) {
	free(memory);
}


inline void* nlsReAlloc(void *memory, size_t size, bool zeroMemory = false) {
	void *z = realloc(memory, size);
	if (!z) {
		fprintf(stderr, "Out Of Memory - Exiting\n");
		exit(1);
	}
	return z;
}