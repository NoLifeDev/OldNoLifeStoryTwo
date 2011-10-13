//////////////////////////////////////////////////////////////////////////
// Copyright 2011 Peter Atechian (Retep998)                             //
// All code in this version of NLS (aside from the libraries),          //
// was written by Retep998.                                             //
// Contributers to previous versions include (in no particular order):  //
// Calc0000                                                             //
// Erwin Oeg1ma (Diamondo25)                                            //
// David (Jvlaple)                                                      //
// Andy Turner (Inumedia)                                               //
// Cedric Van Goethem (Csharp)                                          //
// Anthony Wolfe Vaughn                                                 //
// Nate Bender                                                          //
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
//TODO - Implement some serious compiler detection.
#ifdef _WIN32
#define NLS_WINDOWS
#include <Windows.h>
#ifdef _MSC_VER
#if _MSC_VER == 1700
#define NLS_CPP11
#endif
#endif
#elif defined(UNIX)
#define NLS_UNIX
//Similar to linux?
#elif defined(__linux)
#define NLS_LINUX
//Check for versions of gcc
#define NLS_GCC
#define NLS_CPP11
#elif defined(MAC)
#define NLS_MAC
//Idk really what to do
#else
#error "Unknown platform. Define either _WIN32, __linux, UNIX or MAC"
#endif
#ifndef NLS_CPP11
#error What is wrong with you? Upgrade your compiler!
#endif

//SFML
#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

//GLEW
#ifdef NLS_LINUX
#include <GL/glew.h>
#else
#include <glew.h>
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
#include <filesystem>
#include <future>
#include <mutex>
#include <ratio>
#include <thread>
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
#include <hash_map>
#include <hash_set>
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
#include <strstream>
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
using namespace std::tr1;
using namespace std::tr2;
using namespace std::tr2::sys;

//And resources
#ifdef NLS_WINDOWS
#include "../resources/Resource.h"
#endif
