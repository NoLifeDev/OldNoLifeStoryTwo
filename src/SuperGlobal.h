//////////////////////////////////////////////////////////////////////////
// Copyright 2011 Peter Atechian (Retep998)                             //
// Almost all code in this version of NLS (aside from the libraries),   //
// was written by Retep998.                                             //
// Contributers to this and previous versions (in no particular order): //
// Joe Witterschlenbagen (Calc0000)                                     //
// Erwin Oegema (Diamondo25)                                            //
// David (Jvlaple)                                                      //
// Andy Turner (Inumedia)                                               //
// Cedric Van Goethem (Csharp)                                          //
// Martyn Cleroux (IWannaWin)                                           //
// Anthony Wolfe Vaughn                                                 //
// Nate Bender                                                          //
// Mika Attila (SolvedSnake)                                            //
// Thanks goes to the creators of maplelib and maplelib2:               //
// Snow                                                                 //
// jonyleeson                                                           //
// haha01haha01                                                         //
// HaHa                                                                 //
// Other thanks goes to:                                                //
// Koolk                                                                //
// Spudgy                                                               //
//////////////////////////////////////////////////////////////////////////
// This file is part of NoLifeStory.                                    //
//                                                                      //
// NoLifeStory is free software: you can redistribute it and/or modify  //
// it under the terms of the GNU General Public License as published by //
// the Free Software Foundation, either version 3 of the License, or    //
// (at your option) any later version.                                  //
//                                                                      //
// NoLifeStory is distributed in the hope that it will be useful,       //
// but WITHOUT ANY WARRANTY; without even the implied warranty of       //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        //
// GNU General Public License for more details.                         //
//                                                                      //
// You should have received a copy of the GNU General Public License    //
// along with NoLifeStory.  If not, see <http://www.gnu.org/licenses/>. //
//////////////////////////////////////////////////////////////////////////
#ifdef _WIN32
#define NLS_WINDOWS
#include <Windows.h>
#elif defined(UNIX)
#define NLS_UNIX
#define NLS_NIX
#elif defined(__linux)
#define NLS_LINUX
#define NLS_NIX
#elif defined(MAC)
#define NLS_MAC
#define NLS_NIX
#else
#error "Unknown platform. Please specify your platform using preprocessor definitions."
#endif

#ifdef _MSC_VER
#define NLS_MSVC
#if _MSC_VER >= 1700
#define NLS_CPP11
#define NLS_TR2
#define NLS_TR1
#elif _MSC_VER >= 1600
#define NLS_TR1
#else
#error "Upgrade your visual studio to VS10 or VS11"
#endif
#elif defined(__GNUC__)
#if __GNUC__ < 4
#error "Please upgrade your gcc"
#elif __GNUC__ == 4
#if __GNUC_MINOR__ < 6
#error "Please upgrade your gcc"
#endif
#endif
#define NLS_GCC
#ifdef _GLIBCXX_HAS_GTHREADS
#define NLS_CPP11
#endif
#ifdef __MINGW32__
#define NLS_MINGW
#endif
#else
#error "Unknown compiler"
#endif

//SFML
#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

//GLEW
#ifdef NLS_WINDOWS
#include <glew.h>
#else
#include <GL/glew.h>
#endif

//Zlib
#include <zlib.h>

//Bass
#include <bass.h>

//The entire STL
#ifdef NLS_CPP11
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <csetjmp>
#include <future>
#include <mutex>
#include <ratio>
#include <thread>
#endif
#ifdef NLS_TR2
#include <filesystem>
#endif
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <ccomplex>
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <complex>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cwchar>
#include <cwctype>
#include <deque>
#include <exception>
#include <forward_list>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <random>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <valarray>
#include <vector>
using namespace std;
#ifdef NLS_TR1
using namespace std::tr1;
#endif
#ifdef NLS_TR2
using namespace std::tr2;
using namespace std::tr2::sys;
#endif

//Some other headers
#ifndef NLS_TR2
#include <sys/stat.h>
#endif

//Do some type checks
#ifdef SFML_ENDIAN_BIG
#error "Why are you using big endian???"
#endif
static_assert(sizeof(char) == 1, "Unsupported char size");
static_assert(sizeof(wchar_t) == 2, "Unsupported wchar_t size");

//And resources
#ifdef NLS_WINDOWS
#include "../resources/Resource.h"
#endif

//And AES
#include "AES.h"