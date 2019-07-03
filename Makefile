CC=g++
CPPFLAGS += -g -Wall -I/usr/include/GL -I/usr/local/include
LDLIBS += -lglut -lGL -lglfw -ldl
OBJECTS=main.o window.o game.o reloader.o

all: cbreakout libgame.so

main.o: main.cpp common.h window.h game.h reloader.h
window.o: window.cpp window.h common.h game.h 
game.o: game.cpp common.h game.h
reloader.o: reloader.cpp reloader.h
libgame.so: game.cpp common.h game.h
	$(CC) -shared -o libgame.so -fPIC game.cpp

cbreakout: $(OBJECTS) common.h
	$(CC) $(CFLAGS) $(OBJECTS) $(LDLIBS) -o cbreakout

pack: cbreakout
	@echo "   `ls -ahs cbreakout`"
	strip cbreakout
	@echo "   `ls -ahs cbreakout`"
	upx -qqq --best cbreakout
	@echo "   `ls -ahs cbreakout`"
	
clean:
	rm -rf cbreakout *.o

release:
	CPPFLAGS=-O2  make clean all
