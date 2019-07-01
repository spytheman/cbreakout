#ifndef __CBREAKOUT_COMMON_H
#define __CBREAKOUT_COMMON_H

#include <stdio.h>

class X {
 public:
    X(){
        this->setName("X");
        this->x = 0;
        this->y = 0;
        this->w = 0;
        this->h = 0;
    }
    const char *name;
    int x,y; // center of the object
    int w,h; // half width and half height - distances to the edges
    void setName(const char *s){ this->name=s; }
    void print(){
        printf("%10s: %3d, %3d | %3d, %3d \n", this->name, this->x, this->y, this->w, this->h);
    }
};

class Brick: public X { 
 public: 
    Brick(){
        this->setName( "Brick" );
        this->x = 0;
        this->y = 0;
        this->w = 40;
        this->h = 10;
    }
    Brick(int x, int y){
        this->setName( "Brick" );
        this->x = x;
        this->y = y;
        this->w = 40;
        this->h = 10;
    }
};

class Ball: public X{
 public:
    Ball(int x, int y, int r){
        this->setName( "Ball" );
        this->x = x;
        this->y = y;
        this->w = r;
        this->h = r;
    }
};

class Paddle: public X{
 public:
    Paddle(int x, int y){ 
        this->setName( "Paddle" );
        this->x = x;
        this->y = y;
        this->w = 40;
        this->h = 6;
    }
};


#endif
