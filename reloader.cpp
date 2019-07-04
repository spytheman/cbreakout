#include <stddef.h>
#include <stdio.h>
#include <dlfcn.h>
#include "reloader.h"

static void *_libgame = NULL;

void libgame_load(){
    _libgame = dlopen("./libgame.so", RTLD_NOW | RTLD_GLOBAL);
}

void libgame_close(){
   dlclose(_libgame);
}

void libgame_reload(){
   printf("libgame_reload ...\n");
   if( _libgame != NULL ){
      libgame_close();
   }
   libgame_load();
   printf("  _libgame = %p\n", _libgame );
}
