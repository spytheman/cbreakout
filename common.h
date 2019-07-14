#ifndef __CBREAKOUT_COMMON_H
#define __CBREAKOUT_COMMON_H

class X {
 public:
    int x,y; // center of the object
    int w,h; // half width and half height - distances to the edges
    int dx;
    int dy;
    char *name;
    X();
    void setName(char *s);
    void print();
};

class Brick: public X { 
 public: 
    Brick();
    Brick(int x, int y);
};

class Ball: public X{
 public:
    Ball(int x, int y, int r);
};

class Paddle: public X{
 public:
    Paddle(int x, int y);
};

#endif
