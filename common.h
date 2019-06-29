#ifndef __CBREAKOUT_COMMON_H
#define __CBREAKOUT_COMMON_H

class X {
    public:
    int x,y; // center of the object
    int w,h; // half width and half height - distances to the edges
};

class Brick: public X {
   Brick(int x, int y){
      this->x = x;
      this->y = y;
      this->w = 40;
      this->h = 10;
   }
};

class Ball: public X{
   Ball(int x, int y, int r){
      this->x = x;
      this->y = y;
      this->w = r;
      this->h = r;
   }
};

class Paddle: public X{
   Paddle(int x, int y){
      this->x = x;
      this->y = y;
      this->w = 40;
      this->h = 6;
   }
};


#endif
