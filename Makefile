
CC=clang-7
CXX=clang++-7

CPPFLAGS += -O1 -pedantic -g -Wall -Wextra -Werror \
     -I/usr/include/GL \
     -I/usr/local/include \
     -fPIE -fPIC

##CPPFLAGS += -fsanitize=thread -fsanitize=undefined -fsanitize=vptr

LDLIBS += -lpthread -lstdc++ -lubsan -lglut -lGL -lglfw -ldl -pie 
OBJECTS=main.o game.o window.o reloader.o
##################################################################################

refresh: libgame.so
	pkill -SIGUSR1 cbreakout || true
	@echo "The game should be refreshed :-)"

all: cbreakout libgame.so

libgame.so: game.cpp game.h
	$(CC) $(CPPFLAGS) -shared  -rdynamic -o libgame.so game.cpp

cbreakout: $(OBJECTS) libgame.so
	$(CC) $(CPPFLAGS) $(OBJECTS) $(LDLIBS) -o cbreakout

main.o: main.cpp window.h
window.o: window.cpp window.h game.h reloader.h
reloader.o: reloader.cpp reloader.h game.h
game.o: game.cpp game.h

pack: cbreakout
	@echo "   `ls -ahs cbreakout`"
	strip cbreakout
	@echo "   `ls -ahs cbreakout`"
	upx -qqq --best cbreakout
	@echo "   `ls -ahs cbreakout`"

clean:
	rm -rf cbreakout *.o libgame.so

release:
	CPPFLAGS=-O2  make clean all

stats:
	wc *.cpp *.h |sort -n
