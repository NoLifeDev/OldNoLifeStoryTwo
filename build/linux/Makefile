#compiler executable
CC = g++
#source dir path prefix
PP = ../../src/NoLifeStory
#additional compiler flags
CF = --std=gnu++0x
#search paths for includes
SI = -I../../include
#search paths for libs
SL = 
#libs to link against
LL = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network

#compile command macro to save time
C = $(CC) -c $(SI) $(CF)

#objects

OBJS = AniSprite.o Back.o Client.o CommandFunctions.o Config.o\
Console.o Foothold.o Functions.o Graphics.o Map.o Network.o\
NoLifeStory.o Obj.o Physics.o Player.o Portal.o Reactor.o Sound.o\
Sprite.o ThisPlayer.o Tile.o Time.o Utilities.o View.o WZ.o

#targets

NoLifeStory: $(OBJS)
	$(CC) lib/libbass64.so $(OBJS) -o NoLifeStory $(LL)

AniSprite.o:
	$(C) $(PP)/AniSprite.cpp

Back.o:
	$(C) $(PP)/Back.cpp
	
Client.o:
	$(C) $(PP)/Client.cpp
	
CommandFunctions.o:
	$(C) $(PP)/CommandFunctions.cpp
	
Config.o:
	$(C) $(PP)/Config.cpp
	
Console.o:
	$(C) $(PP)/Console.cpp
	
Graphics.o:
	$(C) $(PP)/Graphics.cpp
	
Map.o:
	$(C) $(PP)/Map.cpp
	
Network.o:
	$(C) $(PP)/Network.cpp
	
Obj.o:
	$(C) $(PP)/Obj.cpp
	
Physics.o:
	$(C) $(PP)/Physics.cpp
	
Player.o:
	$(C) $(PP)/Player.cpp
	
Portal.o:
	$(C) $(PP)/Portal.cpp

Reactor.o:
	$(C) $(PP)/Reactor.cpp
	
Sound.o:
	$(C) $(PP)/Sound.cpp
	
Sprite.o:
	$(C) $(PP)/Sprite.cpp
	
ThisPlayer.o:
	$(C) $(PP)/ThisPlayer.cpp
	
Tile.o:
	$(C) $(PP)/Tile.cpp
	
Time.o:
	$(C) $(PP)/Time.cpp
	
Utilities.o:
	$(C) $(PP)/Utilities.cpp

View.o:
	$(C) $(PP)/View.cpp
	
WZ.o:
	$(C) $(PP)/WZ.cpp
	
Foothold.o:
	$(C) $(PP)/Foothold.cpp

Functions.o:
	$(C) $(PP)/Functions.cpp

NoLifeStory.o:
	$(C) $(PP)/NoLifeStory.cpp

clean:
	rm *.o
