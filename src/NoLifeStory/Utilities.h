////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

#define PI 3.1415926535897932384626433832795
#define degtorad 0.01745329251994329576923690768489
#define radtodeg 57.295779513082320876798154814105

inline u32string u32(const string& str) {
	static char32_t s[1024];
	char32_t* end = sf::Utf8::ToUtf32(str.begin(), str.end(), s);
	return u32string(s, end);
}
inline string u8(const u32string& str) {
	static char s[1024];
	char* end = sf::Utf32::ToUtf8(str.begin(), str.end(), s);
	return string(s, end);
}

inline void pad(string& str, char c, size_t l) {
	if (str.size() >= l) return;
	str.insert(0, l-str.size(), c);
}
inline vector<string> split(const string& str, char c) {
	stringstream ss(str);
	string s;
	vector<string> sp;
	while (getline(ss, s, c)) {
		sp.push_back(s);
	}
	return sp;
}

inline string tostring(const double& t) {
	static char str[32];
	sprintf(str, "%f", t);
	return str;
}

inline string tostring(const int& t) {
	static char str[32];
	sprintf(str, "%i", t);
	return str;
}

inline string tostring(const int& t, const int& n) {
	string s = tostring(t);
	pad(s, '0', n);
	return s;
}

inline double todouble(const string& t) {
	return strtod(t.c_str(), 0);
}

inline int toint(const string& t) {
	return strtol(t.c_str(), 0, 10);
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

inline int pot(int x) {
	x--;
	for (int i = 1; i < 32; i <<= 1) {
		x = x|x>>i;
	}
	return x+1;
}

inline bool is_extendsp_job(int32_t job) {
  return job / 1000 == 3 || job / 100 == 22 || job == 2001;
}

inline string GetClipboardText() {
#ifdef NLS_WINDOWS
	if (OpenClipboard(nullptr)) {
		void* data = GetClipboardData(CF_TEXT);
		char* s = (char*)GlobalLock(data);
		GlobalUnlock(data);
		CloseClipboard();
		return s != 0 ? s : string();
	}
#else
#endif
	return string();
}
inline void SetClipboardText(const string& s) {
#ifdef NLS_WINDOWS
	if (OpenClipboard(nullptr)) {
		EmptyClipboard();
		void* data = GlobalAlloc(GMEM_DDESHARE, s.size()+1);
		char* sdata = (char*)GlobalLock(data);
		strcpy(sdata, s.c_str());
		GlobalUnlock(data);
		SetClipboardData(CF_TEXT, sdata);
		CloseClipboard();
	}
#else
#endif
}
#ifndef NLS_TR2
class path : public string {
public:
	path() : string() {}
	path(const string& s) : string(s) {}
	path(const string&& s) : string(s) {}
	path(const char* s) : string(s) {}
	path(const path& s) : string(s) {}
	path& operator/= (path other) {
		if (length() > 1 and (at(length()-1) == '/' or at(length()-1) == '\\')) {
			erase(length()-1);
		}
		if (other.length() > 0 and (other.at(0) == '/' or other.at(0) == '\\')) {
			other.erase(0,1);
		}
		if (!empty()) {
			*this += '/';
		}
		*this += other;
		return *this;
	}
	path operator/ (path other) {
		path result = *this;
		return result /= other;
	}
};
inline bool exists (const path& name) {
	struct stat info;
	return stat(name.c_str(),&info) == 0;
}
#endif
