///////////////////////////////////////////////////////////////
// Copyright 2010 Peter (Retep998)
// Contributers include David (Jvlaple), Anthony Wolfe Vaughn, Calc0000
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

#ifndef STATS_H
#define STATS_H

namespace stats {
	void init();
	extern string name;
	extern int nametag;
	extern int skin;
	extern int face;
	extern int hair;
	namespace equips {
		extern int cap;
		extern int medal;
		extern int forehead;
		extern int ring1;
		extern int ring2;
		extern int eyeacc;
		extern int earacc;
		extern int mantle;
		extern int clothes;
		extern int pendant;
		extern int weapon;
		extern int shield;
		extern int gloves;
		extern int pants;
		extern int belt;
		extern int ring3;
		extern int ring4;
		extern int shoes;
		extern int petmp;
		extern int tamingmob;
		extern int saddle;
		extern int mobequip;
		extern int petacc;
		extern int pethp;
	};
};

#endif