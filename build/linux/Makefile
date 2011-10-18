CE = g++
SBP = ../../src/NoLifeStory
CF = -O3 -std=gnu++0x -I../../include -Wno-deprecated -D_GLIBCXX_USE_NANOSLEEP
LF = lib/libbass64.so -lsfml-graphics -lsfml-window -lsfml-network -lsfml-system
EO = NLS
OBJS = obj/AniSprite.o obj/Back.o obj/Client.o obj/CommandFunctions.o obj/Config.o obj/Console.o obj/Foothold.o obj/Functions.o obj/Graphics.o obj/Map.o obj/Network.o obj/NoLifeStory.o obj/Obj.o obj/Physics.o obj/Player.o obj/Portal.o obj/Reactor.o obj/Sound.o obj/Sprite.o obj/ThisPlayer.o obj/Tile.o obj/Time.o obj/Utilities.o obj/View.o obj/WZ.o 

target: $(OBJS)
	$(CE) $(OBJS) -o $(EO) $(LF)

obj/AniSprite.o: $(SBP)/AniSprite.cpp
	$(CE) -c $(CF) $(SBP)/AniSprite.cpp -o obj/AniSprite.o

obj/Back.o: $(SBP)/Back.cpp
	$(CE) -c $(CF) $(SBP)/Back.cpp -o obj/Back.o

obj/Client.o: $(SBP)/Client.cpp
	$(CE) -c $(CF) $(SBP)/Client.cpp -o obj/Client.o

obj/CommandFunctions.o: $(SBP)/CommandFunctions.cpp
	$(CE) -c $(CF) $(SBP)/CommandFunctions.cpp -o obj/CommandFunctions.o

obj/Config.o: $(SBP)/Config.cpp
	$(CE) -c $(CF) $(SBP)/Config.cpp -o obj/Config.o

obj/Console.o: $(SBP)/Console.cpp
	$(CE) -c $(CF) $(SBP)/Console.cpp -o obj/Console.o

obj/Foothold.o: $(SBP)/Foothold.cpp
	$(CE) -c $(CF) $(SBP)/Foothold.cpp -o obj/Foothold.o

obj/Functions.o: $(SBP)/Functions.cpp
	$(CE) -c $(CF) $(SBP)/Functions.cpp -o obj/Functions.o

obj/Graphics.o: $(SBP)/Graphics.cpp
	$(CE) -c $(CF) $(SBP)/Graphics.cpp -o obj/Graphics.o

obj/Map.o: $(SBP)/Map.cpp
	$(CE) -c $(CF) $(SBP)/Map.cpp -o obj/Map.o

obj/Network.o: $(SBP)/Network.cpp
	$(CE) -c $(CF) $(SBP)/Network.cpp -o obj/Network.o

obj/NoLifeStory.o: $(SBP)/NoLifeStory.cpp
	$(CE) -c $(CF) $(SBP)/NoLifeStory.cpp -o obj/NoLifeStory.o

obj/Obj.o: $(SBP)/Obj.cpp
	$(CE) -c $(CF) $(SBP)/Obj.cpp -o obj/Obj.o

obj/Physics.o: $(SBP)/Physics.cpp
	$(CE) -c $(CF) $(SBP)/Physics.cpp -o obj/Physics.o

obj/Player.o: $(SBP)/Player.cpp
	$(CE) -c $(CF) $(SBP)/Player.cpp -o obj/Player.o

obj/Portal.o: $(SBP)/Portal.cpp
	$(CE) -c $(CF) $(SBP)/Portal.cpp -o obj/Portal.o

obj/Reactor.o: $(SBP)/Reactor.cpp
	$(CE) -c $(CF) $(SBP)/Reactor.cpp -o obj/Reactor.o

obj/Sound.o: $(SBP)/Sound.cpp
	$(CE) -c $(CF) $(SBP)/Sound.cpp -o obj/Sound.o

obj/Sprite.o: $(SBP)/Sprite.cpp
	$(CE) -c $(CF) $(SBP)/Sprite.cpp -o obj/Sprite.o

obj/ThisPlayer.o: $(SBP)/ThisPlayer.cpp
	$(CE) -c $(CF) $(SBP)/ThisPlayer.cpp -o obj/ThisPlayer.o

obj/Tile.o: $(SBP)/Tile.cpp
	$(CE) -c $(CF) $(SBP)/Tile.cpp -o obj/Tile.o

obj/Time.o: $(SBP)/Time.cpp
	$(CE) -c $(CF) $(SBP)/Time.cpp -o obj/Time.o

obj/Utilities.o: $(SBP)/Utilities.cpp
	$(CE) -c $(CF) $(SBP)/Utilities.cpp -o obj/Utilities.o

obj/View.o: $(SBP)/View.cpp
	$(CE) -c $(CF) $(SBP)/View.cpp -o obj/View.o

obj/WZ.o: $(SBP)/WZ.cpp
	$(CE) -c $(CF) $(SBP)/WZ.cpp -o obj/WZ.o

