#include <dlfcn.h>
#include "reloader.h"

static void *_libgame;

void libgame_load(){
   _libgame = dlopen("./libgame.so", RTLD_LAZY | RTLD_GLOBAL);
}

void libgame_close(){
   dlclose(_libgame);
}
