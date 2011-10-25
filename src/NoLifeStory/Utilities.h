////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

#define PI 3.1415926535897932384626433832795
#define degtorad 0.01745329251994329576923690768489
#define radtodeg 57.295779513082320876798154814105

#ifdef NLS_WINDOWS //Assuming *nix
#define nstring wstring
#define uchar wchar_t
#define ustringstream wstringstream
#define ucout wcout
#define ucerr wcerr
#define U(x) L##x
#else
#define nstring string
#define uchar char
#define ustringstream stringstream
#define U(x) x
#define ucout cout
#define ucerr cerr
#endif

class ustring : public nstring {
public:
	ustring() : nstring() {}
	ustring(const ustring& s) : nstring(s) {}
	ustring(ustring&& s) : nstring(s) {}
	ustring(const nstring& s) : nstring(s) {}
	ustring(nstring&& s) : nstring(s) {}
	ustring(const uchar* s) : nstring(s) {}
#ifdef NLS_WINDOWS
	ustring(const char* s) {
		string ss = s;
		assign(ss.begin(), ss.end());
	}
	ustring(const string& s) : wstring(s.begin(), s.end()) {}
	bool operator== (const char* s) {
		return *this == ustring(s);
	}
	bool operator!= (const char* s) {
		return *this != ustring(s);
	}
#else
	ustring(const wchar_t* s) {
		wstring ss = s;
		assign(ss.begin(), ss.end());
	}
#endif
	operator nstring&() {
		return *(nstring*)this;
	}
	ustring& pad(uchar c, size_t l) {
		insert(0, l-size(), c);
		return *this;
	}
	vector<ustring> split(uchar c) const {
		ustringstream ss(*this);
		ustring s;
		vector<ustring> sp;
		while (getline(ss, s, c)) {
			sp.push_back(s);
		}
		return sp;
	}
	ustring operator/ (ustring& other) {
		ustring result = *this;
		return result /= other;
	}
	ustring& operator/= (ustring other) {
		if (length() > 1 and (at(length()-1) == '/' or at(length()-1) == '\\')) {
			erase(length()-1);
		}
		if (other.length() > 0 and (other.at(0) == '/' or other.at(0) == '\\')) {
			other.erase(0,1);
		}
		*this += '/';
		*this += other;
		return *this;
	}
};

inline ustring tostring(const double& t) {
	static uchar str[32];
#ifdef NLS_WINDOWS
	swprintf(str, 32, U("%f"), t);
#else
	sprintf(str, 32, U("%f"), t);
#endif
	return str;
}

inline ustring tostring(const int& t) {
	static uchar str[32];
#ifdef NLS_WINDOWS
	swprintf(str, 32, U("%i"), t);
#else
	sprintf(str, 32, U("%i"), t);
#endif
	return str;
}

inline double todouble(const ustring& t) {
#ifdef NLS_WINDOWS
	return wcstod(t.c_str(), 0);
#else
	return cstod(t.c_str(), 0);
#endif
}

inline int toint(const ustring& t) {
#ifdef NLS_WINDOWS
	return wcstol(t.c_str(), 0, 10);
#else
	return cstol(t.c_str(), 0, 10);
#endif
}

inline double sqr(const double& x) {
	return x*x;
}

inline double pdis(const double& x, const double& y) {
	return sqrt(sqr(x)+sqr(y));
}

inline double pdis(const double& x1, const double& y1, const double& x2, const double& y2) {
	return pdis(x2-x1, y2-y1);
}

inline double pdir(const double& x, const double& y) {
	return radtodeg*atan2(y, x);
}

inline double pdir(const double& x1, const double& y1, const double& x2, const double& y2) {
	return pdir(x2-x1, y2-y1);
}

inline double ldx (const double& len, const double& dir) {
	return cos(dir*degtorad)*len;
}

inline double ldy (const double& len, const double& dir) {
	return sin(dir*degtorad)*len;
}

inline double angdif (const double& angle1, const double& angle2) {
	return fmod(fmod(angle1-angle2, 360)+540, 360)-180;
}

inline double sign (const double& x) {
	return x>0?1:x<0?-1:0;
}

#ifndef NLS_TR2
typedef ustring upath;
inline bool exists (const upath& name) {
	ifstream file(name);
	bool check = file.is_open();
	file.close();
	return check;
}
#else
typedef wpath upath;
#endif