#ifndef __CBREAKOUT_GAME_H
#define __CBREAKOUT_GAME_H

#include <stdatomic.h>

struct Game;
struct GameState;

typedef void (*T_GAME_INIT)(Game *);
typedef void (*T_GAME_RENDER)(Game *);
typedef void (*T_GAME_ON_KEY)(Game *, int, int, int, int);
struct GameHandlers {
   T_GAME_INIT   pinit = NULL;
   T_GAME_ON_KEY ponkey = NULL;
   T_GAME_RENDER prender = NULL;
};

struct Game {
   GameState *state;
   atomic_intptr_t handlers = ATOMIC_VAR_INIT(0);
};

extern Game game;

////////////////////////////////////////////////////////////////////////////////////

extern "C" void game_init(Game *g);
extern "C" void game_onkey(Game *g, int key, int scancode, int action, int mods);
extern "C" void game_render(Game *g);


#endif
