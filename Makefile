CFLAGS=-g
LDFLAGS=-lm
OBJECTS=main.o graphics.o ball.o paddle.o brick.o

all: cbreakout

cbreakout: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o cbreakout $(LDFLAGS)

clean:
	rm -rf cbreakout $(OBJECTS)
