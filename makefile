CC=g++
CPPFLAGS=-DUNIX -std=c++0x --debug
LDFLAGS=-lz -lSDL -lSDL_ttf -lSDL_mixer -lGL
OBJECTFILES=Character.o AES.o BitTools.o Decoder.o Endian.o Footholds.o Game.o Graphics.o Input.o KeyMap.o Life.o LoginHandler.o MapleEncryption.o MemoryPool.o Mouse.o Network.o NoLifeStory.o Objects.o OpenGL.o PacketCrypto.o Packets.o Sound.o Stats.o WZData.o

all: NoLifeStory
clean:
	rm -f *.o;
rebuild: clean all

NoLifeStory: wzlibc.o $(OBJECTFILES)
wzlibc.o:
	cp -n ./WZLib/wzlibc.o .

Character.o: Character.cpp
AES.o: AES.cpp
BitTools.o: BitTools.cpp
Decoder.o: Decoder.cpp
Endian.o: Endian.cpp
Footholds.o: Footholds.cpp
Game.o: Game.cpp
Graphics.o: Graphics.cpp
Input.o: Input.cpp
KeyMap.o: KeyMap.cpp
Life.o: Life.cpp
LoginHandler.o: LoginHandler.cpp
MapleEncryption.o: MapleEncryption.cpp
MemoryPool.o: MemoryPool.cpp
Mouse.o: Mouse.cpp
Network.o: Network.cpp
NoLifeStory.o: NoLifeStory.cpp
Objects.o: Objects.cpp
OpenGL.o: OpenGL.cpp
PacketCrypto.o: PacketCrypto.cpp
Packets.o: Packets.cpp
Sound.o: Sound.cpp
Stats.o: Stats.cpp
WZData.o: WZData.cpp