#include <stddef.h>
#include <stdio.h>
#include <dlfcn.h>
#include "reloader.h"
#include "game.h"

static void *_libgame = NULL;

void libgame_load(){
   printf("libgame_load\n");
   _libgame = dlopen("./libgame.so", RTLD_NOW );
   printf("  >>>  _libgame=%p\n", _libgame );
   if( _libgame ){             
      game.pinit   = (T_GAME_INIT)   dlsym( _libgame, "game_init");   if(!game.pinit)   printf("Cannot load symbol game_init: %s\n",   dlerror());
      game.prender = (T_GAME_RENDER) dlsym( _libgame, "game_render"); if(!game.prender) printf("Cannot load symbol game_render: %s\n", dlerror());
      game.ponkey  = (T_GAME_ON_KEY) dlsym( _libgame, "game_onkey");  if(!game.ponkey)  printf("Cannot load symbol game_onkey: %s\n",  dlerror());
      printf("  >>>  dlsym results: game.pinit=%p | game.ponkey=%p | game.prender=%p\n", (void*)game.pinit, (void*)game.ponkey, (void*)game.prender);
   }
}

void libgame_close(){
   printf("libgame_close\n");
   game.pinit = NULL;
   game.ponkey = NULL;
   game.prender = NULL;
   dlclose(_libgame);
   _libgame = NULL;
}

void libgame_reload(){
   printf("libgame_reload\n");
   if( _libgame != NULL ){
      libgame_close();
   }
   libgame_load();
}
