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
#ifdef _WIN32
#define NLS_WINDOWS
#include <Windows.h>
#elif defined(UNIX)
#define NLS_UNIX
#elif defined(MAC)
#define NLS_MAC
#else
#error "Unknown platform. Define either _WIN32, UNIX or MAC"
#endif

//SFML
#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

//GLEW
#include <glew.h>

//Zlib
#include <zlib.h>

//Bass
#include <bass.h>

//The entire STL
#include <algorithm>
#include <allocators>
#include <array>
#ifdef VS11
#include <atomic>
#endif
#include <bitset>
#include <cassert>
#include <ccomplex>
#include <cctype>
#include <cerrno>
#include <cfloat>
#ifdef VS11
#include <chrono>
#endif
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <codecvt>
#include <complex>
#ifdef VS11
#include <condition_variable>
#include <csetjmp>
#endif
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
#ifdef VS11
#include <filesystem>
#endif
#include <forward_list>
#include <fstream>
#include <functional>
#ifdef VS11
#include <future>
#endif
#include <hash_map>
#include <hash_set>
#ifdef VS10
#include <initializer_list>
#endif
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
#ifdef VS11
#include <mutex>
#endif
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <random>
#ifdef VS11
#include <ratio>
#endif
#include <regex>
#ifdef VS11
#include <scoped_allocator>
#endif
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <strstream>
#include <system_error>
#ifdef VS11
#include <thread>
#endif
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

//And resources
#include "../resources/Resource.h"