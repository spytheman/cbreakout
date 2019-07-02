CC=g++
CPPFLAGS += -g -Wall -I/usr/include/GL -I/usr/local/include
LDLIBS += -lm -lglut -lGLU -lGL -lglfw
OBJECTS=main.o graphics.o ball.o paddle.o brick.o

all: cbreakout

main.o: main.cpp common.h
graphics.o: graphics.cpp common.h
paddle.o: paddle.cpp common.h
ball.o: ball.cpp common.h
brick.o: brick.cpp common.h

cbreakout: $(OBJECTS) common.h
	$(CC) $(CFLAGS) $(OBJECTS) $(LDLIBS) -o cbreakout

pack: cbreakout
	@echo "   `ls -ahs cbreakout`"
	strip cbreakout
	@echo "   `ls -ahs cbreakout`"
	upx -qqq --best cbreakout
	@echo "   `ls -ahs cbreakout`"
	
clean:
	rm -rf cbreakout $(OBJECTS)

release:
	CPPFLAGS=-O2  make clean all
