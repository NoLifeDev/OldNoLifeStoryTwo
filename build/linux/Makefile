#compiler executable
CC = g++
#source dir path prefix
PP = ../../src/NoLifeStory
#additional compiler flags
CF = --std=gnu++0x -Wno-deprecated
#search paths for includes
SI = -I../../include
#search paths for libs
SL = 
#libs to link against
LL = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network

#compile command macro to save time
C = $(CC) -c $(SI) $(CF) -o $@

#objects

OBJS = obj/AniSprite.o obj/Back.o obj/Client.o obj/CommandFunctions.o obj/Config.o\
obj/Console.o obj/Foothold.o obj/Functions.o obj/Graphics.o obj/Map.o obj/Network.o\
obj/NoLifeStory.o obj/Obj.o obj/Physics.o obj/Player.o obj/Portal.o obj/Reactor.o obj/Sound.o\
obj/Sprite.o obj/ThisPlayer.o obj/Tile.o obj/Time.o obj/Utilities.o obj/View.o obj/WZ.o

#targets

NoLifeStory: $(OBJS)
	$(CC) lib/libbass.so $(OBJS) -o NoLifeStory $(LL)
	
NLS64: $(OBJS)
	$(CC) lib/libbass64.so $(OBJS) -o NoLifeStory $(LL)

obj/AniSprite.o:
	$(C) $(PP)/AniSprite.cpp

obj/Back.o:
	$(C) $(PP)/Back.cpp
	
obj/Client.o:
	$(C) $(PP)/Client.cpp
	
obj/CommandFunctions.o:
	$(C) $(PP)/CommandFunctions.cpp
	
obj/Config.o:
	$(C) $(PP)/Config.cpp
	
obj/Console.o:
	$(C) $(PP)/Console.cpp
	
obj/Graphics.o:
	$(C) $(PP)/Graphics.cpp
	
obj/Map.o:
	$(C) $(PP)/Map.cpp
	
obj/Network.o:
	$(C) $(PP)/Network.cpp
	
obj/Obj.o:
	$(C) $(PP)/Obj.cpp
	
obj/Physics.o:
	$(C) $(PP)/Physics.cpp
	
obj/Player.o:
	$(C) $(PP)/Player.cpp
	
obj/Portal.o:
	$(C) $(PP)/Portal.cpp

obj/Reactor.o:
	$(C) $(PP)/Reactor.cpp
	
obj/Sound.o:
	$(C) $(PP)/Sound.cpp
	
obj/Sprite.o:
	$(C) $(PP)/Sprite.cpp
	
obj/ThisPlayer.o:
	$(C) $(PP)/ThisPlayer.cpp
	
obj/Tile.o:
	$(C) $(PP)/Tile.cpp
	
obj/Time.o:
	$(C) $(PP)/Time.cpp
	
obj/Utilities.o:
	$(C) $(PP)/Utilities.cpp

obj/View.o:
	$(C) $(PP)/View.cpp
	
obj/WZ.o:
	$(C) $(PP)/WZ.cpp
	
obj/Foothold.o:
	$(C) $(PP)/Foothold.cpp

obj/Functions.o:
	$(C) $(PP)/Functions.cpp

obj/NoLifeStory.o:
	$(C) $(PP)/NoLifeStory.cpp

clean:
	rm obj/*
