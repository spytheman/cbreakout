CC=g++
CFLAGS=-g
LDFLAGS=-lm
OBJECTS=main.o graphics.o ball.o paddle.o brick.o

all: cbreakout

main.o: main.cpp common.h
graphics.o: graphics.cpp common.h
paddle.o: paddle.cpp common.h
ball.o: ball.cpp common.h
brick.o: brick.cpp common.h

cbreakout: $(OBJECTS) common.h
	$(CC) $(CFLAGS) $(OBJECTS) -o cbreakout $(LDFLAGS)

clean:
	rm -rf cbreakout $(OBJECTS)
