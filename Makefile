
CC=clang-7
CXX=clang++-7

CPPFLAGS += -O1 -pedantic -g -Wall -Wextra -Werror \
     -I/usr/include/GL \
     -I/usr/local/include \
     -fPIE -fPIC

##CPPFLAGS += -fsanitize=thread -fsanitize=undefined -fsanitize=vptr

LDLIBS += -lpthread -lstdc++ -lubsan -lglut -lGL -lglfw -ldl -pie 
OBJECTS=main.o window.o reloader.o

refresh: libgame.so
	pkill -SIGUSR1 cbreakout || true
	@echo "The game should be refreshed :-)"

all: cbreakout libgame.so

main.o: main.cpp common.h window.h game.h reloader.h
window.o: window.cpp window.h common.h game.h 
game.o: game.cpp common.h game.h
reloader.o: reloader.cpp reloader.h
libgame.so: game.cpp common.h game.h
	$(CC) $(CPPFLAGS) -shared  -rdynamic -o libgame.so game.cpp

cbreakout: $(OBJECTS) common.h libgame.so
	$(CC) $(CPPFLAGS) $(OBJECTS) $(LDLIBS) -o cbreakout

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
