#ifndef __CBREAKOUT_GAME_H
#define __CBREAKOUT_GAME_H

#include "common.h"

class Game {
 public:
   int frames;
   float t;
   Ball *ball;
   Paddle *paddle;
   Brick bricks[60];
   void init();
   void render();
   void onKey(int key, int scancode, int action, int mods);   
};

extern Game game;

#endif
