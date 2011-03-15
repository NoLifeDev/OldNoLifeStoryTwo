///////////////////////////////////////////////////////////////
// Copyright 2010 Peter (Retep998)
// Contributers include:
// David (Jvlaple)
// Anthony Wolfe Vaughn
// Calc0000
// Diamondo25
///////////////////////////////////////////////////////////////
// This file is part of NoLifeStory.
//
// NoLifeStory is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// NoLifeStory is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with NoLifeStory.  If not, see <http://www.gnu.org/licenses/>.
///////////////////////////////////////////////////////////////
#pragma once

//SDL
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_opengl.h"
#include "SDL/SDL_syswm.h"

//WZLib
#include "WZLib/wzlibc.h"

//Timer
#include "Timer/Timer.h"

//STL
#include <algorithm>
#include <allocators>
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
#include <codecvt>
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
#include <initializer_list>
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
#include <typeindeX>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <valarray>
#include <vector>
using namespace std;

//Our own shiz
#include "Resource.h"
#include "Platform.h"
#include "Utilities.h"
#include "Velocity.h"
#include "Sprite.h"
#include "Sound.h"
#include "WZData.h"
#include "Mouse.h"
#include "Interface.h"
#include "Map.h"
#include "View.h"
#include "Graphics.h"
#include "Text.h"
#include "Fonts.h"
#include "OpenGL.h"
#include "Footholds.h"
#include "Depth.h"
#include "Object.h"
#include "Character.h"
#include "Life.h"
#include "Input.h"
#include "Stats.h"
#include "KeyMap.h"
#include "Game.h"