////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

#define PI 3.1415926535897932384626433832795
#define degtorad 0.01745329251994329576923690768489
#define radtodeg 57.295779513082320876798154814105

class ustring : public wstring {
public:
	ustring() : wstring() {}
	ustring(const ustring& s) : wstring(s) {}
	ustring(ustring&& s) : wstring(s) {}
	ustring(const wstring& s) : wstring(s) {}
	ustring(wstring&& s) : wstring(s) {}
	ustring(const wchar_t* s) : wstring(s) {}
	ustring(const char* s) {
		string ss = s;
		assign(ss.begin(), ss.end());
	}
	ustring(const string& s) : wstring(s.begin(), s.end()) {}
	operator wstring&() {
		return *(wstring*)this;
	}
	bool operator== (const char* s) {
		return *this == ustring(s);
	}
	bool operator!= (const char* s) {
		return *this != ustring(s);
	}
	ustring& pad(wchar_t c, size_t l) {
		insert(0, l-size(), c);
		return *this;
	}
	vector<ustring> split(wchar_t c) const {
		wstringstream ss(*this);
		ustring s;
		vector<ustring> sp;
		while (getline(ss, s, c)) {
			sp.push_back(s);
		}
		return sp;
	}
	ustring operator/ (ustring& other) {
		ustring result;
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
	static wchar_t str[32];
	swprintf(str, 2, L"%f", t);
	return str;
}

inline ustring tostring(const int& t) {
	static wchar_t str[32];
	swprintf(str, 2, L"%i", t);
	return str;
}

inline double todouble(const ustring& t) {
	return wcstod(t.c_str(), 0);
}

inline int toint(const ustring& t) {
	return wcstol(t.c_str(), 0, 10);
}

inline double sqr(const double& x) {
	return x*x;
}

inline double pdis(const double& x1, const double& y1, const double& x2, const double& y2) {
	return sqrt(sqr(x1-x2)+sqr(y1-y2));
}

inline double pdir(const double& x1, const double& y1, const double& x2, const double& y2) {
	return radtodeg*atan2(y2-y1, x2-x1);
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
typedef ustring path;
inline bool exists (const path& name) {
	wifstream file(name);
	bool check = file.is_open();
	file.close();
	return check;
}
#endif