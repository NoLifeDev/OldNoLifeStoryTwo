CE = g++
SBP = ../../src/NoLifeStory
CF = -g -I../../include -std=gnu++0x -fshort-wchar
LF = lib/libbass64.so -lsfml-graphics -lsfml-window -lsfml-network -lsfml-system -lz
EO = NLS
OBJS = obj/AES.o obj/AniSprite.o obj/Back.o obj/Client.o obj/Config.o obj/Foothold.o obj/Graphics.o obj/KeyMap.o obj/Keys.o obj/LadderRope.o obj/Map.o obj/Network.o obj/NoLifeStory.o obj/Obj.o obj/Physics.o obj/Player.o obj/Portal.o obj/Reactor.o obj/Sound.o obj/Sprite.o obj/Text.o obj/ThisPlayer.o obj/Tile.o obj/Time.o obj/UI.o obj/Utilities.o obj/View.o obj/WZ.o 

target: $(OBJS)
	$(CE) $(OBJS) -o $(EO) $(LF)

obj/AniSprite.o: $(SBP)/AniSprite.cpp $(SBP)/Global.h 
	$(CE) -c $(CF) $(SBP)/AniSprite.cpp -o obj/AniSprite.o

obj/Back.o: $(SBP)/Back.cpp $(SBP)/Global.h 
	$(CE) -c $(CF) $(SBP)/Back.cpp -o obj/Back.o

obj/Client.o: $(SBP)/Client.cpp $(SBP)/Global.h 
	$(CE) -c $(CF) $(SBP)/Client.cpp -o obj/Client.o

obj/Config.o: $(SBP)/Config.cpp $(SBP)/Global.h 
	$(CE) -c $(CF) $(SBP)/Config.cpp -o obj/Config.o

obj/Foothold.o: $(SBP)/Foothold.cpp $(SBP)/Global.h 
	$(CE) -c $(CF) $(SBP)/Foothold.cpp -o obj/Foothold.o

obj/Graphics.o: $(SBP)/Graphics.cpp $(SBP)/Global.h 
	$(CE) -c $(CF) $(SBP)/Graphics.cpp -o obj/Graphics.o

obj/KeyMap.o: $(SBP)/KeyMap.cpp $(SBP)/Global.h 
	$(CE) -c $(CF) $(SBP)/KeyMap.cpp -o obj/KeyMap.o

obj/Keys.o: $(SBP)/Keys.cpp $(SBP)/Global.h 
	$(CE) -c $(CF) $(SBP)/Keys.cpp -o obj/Keys.o

obj/LadderRope.o: $(SBP)/LadderRope.cpp $(SBP)/Global.h 
	$(CE) -c $(CF) $(SBP)/LadderRope.cpp -o obj/LadderRope.o

obj/Map.o: $(SBP)/Map.cpp $(SBP)/Global.h 
	$(CE) -c $(CF) $(SBP)/Map.cpp -o obj/Map.o

obj/Network.o: $(SBP)/Network.cpp $(SBP)/Global.h 
	$(CE) -c $(CF) $(SBP)/Network.cpp -o obj/Network.o

obj/NoLifeStory.o: $(SBP)/NoLifeStory.cpp $(SBP)/Global.h 
	$(CE) -c $(CF) $(SBP)/NoLifeStory.cpp -o obj/NoLifeStory.o

obj/Obj.o: $(SBP)/Obj.cpp $(SBP)/Global.h 
	$(CE) -c $(CF) $(SBP)/Obj.cpp -o obj/Obj.o

obj/Physics.o: $(SBP)/Physics.cpp $(SBP)/Global.h 
	$(CE) -c $(CF) $(SBP)/Physics.cpp -o obj/Physics.o

obj/Player.o: $(SBP)/Player.cpp $(SBP)/Global.h 
	$(CE) -c $(CF) $(SBP)/Player.cpp -o obj/Player.o

obj/Portal.o: $(SBP)/Portal.cpp $(SBP)/Global.h 
	$(CE) -c $(CF) $(SBP)/Portal.cpp -o obj/Portal.o

obj/Reactor.o: $(SBP)/Reactor.cpp $(SBP)/Global.h 
	$(CE) -c $(CF) $(SBP)/Reactor.cpp -o obj/Reactor.o

obj/Sound.o: $(SBP)/Sound.cpp $(SBP)/Global.h 
	$(CE) -c $(CF) $(SBP)/Sound.cpp -o obj/Sound.o

obj/Sprite.o: $(SBP)/Sprite.cpp $(SBP)/Global.h 
	$(CE) -c $(CF) $(SBP)/Sprite.cpp -o obj/Sprite.o

obj/Text.o: $(SBP)/Text.cpp $(SBP)/Global.h 
	$(CE) -c $(CF) $(SBP)/Text.cpp -o obj/Text.o

obj/ThisPlayer.o: $(SBP)/ThisPlayer.cpp $(SBP)/Global.h 
	$(CE) -c $(CF) $(SBP)/ThisPlayer.cpp -o obj/ThisPlayer.o

obj/Tile.o: $(SBP)/Tile.cpp $(SBP)/Global.h 
	$(CE) -c $(CF) $(SBP)/Tile.cpp -o obj/Tile.o

obj/Time.o: $(SBP)/Time.cpp $(SBP)/Global.h 
	$(CE) -c $(CF) $(SBP)/Time.cpp -o obj/Time.o

obj/UI.o: $(SBP)/UI.cpp $(SBP)/Global.h 
	$(CE) -c $(CF) $(SBP)/UI.cpp -o obj/UI.o

obj/Utilities.o: $(SBP)/Utilities.cpp $(SBP)/Global.h 
	$(CE) -c $(CF) $(SBP)/Utilities.cpp -o obj/Utilities.o

obj/View.o: $(SBP)/View.cpp $(SBP)/Global.h 
	$(CE) -c $(CF) $(SBP)/View.cpp -o obj/View.o

obj/WZ.o: $(SBP)/WZ.cpp $(SBP)/Global.h 
	$(CE) -c $(CF) $(SBP)/WZ.cpp -o obj/WZ.o

obj/AES.o: ../../src/AES.cpp
	$(CE) -c $(CF) ../../src/AES.cpp -o obj/AES.o

clean:
	rm -rf NLS obj
