#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <stdatomic.h>
#include "reloader.h"
#include "game.h"

static void *_libgame = NULL;
Game game;

////////////////////////////////////////////////////////////////////////////
static atomic_int _shouldReload = ATOMIC_VAR_INIT(0);
void sighandler(int);
void sighandler(int signum) {
   printf("Caught signal %d... Shared library should reload.\n", signum);
   atomic_store( &_shouldReload, 1);
}

void *_reloader_thread_proc(void *x){
    if(0)printf("_reloader_thread_proc: start, x: %p\n", x);
    while(true){
        if( 2 == _shouldReload ) break;
        if( 1 == _shouldReload ){
            //printf("_reloader_thread_proc: _shouldReload=%d\n", _shouldReload);
            atomic_store( &_shouldReload, 0);
            libgame_reload();
        }
        usleep(100000);
    }
    //printf("_reloader_thread_proc: returning ...\n");
    return NULL;
}

static pthread_t _reloader_thread;
void reloader_init(){
   signal(SIGUSR1, sighandler);
   pthread_create(&_reloader_thread, NULL, _reloader_thread_proc, NULL);

   libgame_load();
   reinterpret_cast<GameHandlers *>( game.handlers )->pinit( &game );   
}
void reloader_cleanup(){
    libgame_close();
    void *result;
    int jres;
    atomic_store( &_shouldReload, 2);
    jres = pthread_join(_reloader_thread, &result);
    //printf("reloader_cleanup pthread_join jres: %d result: %p\n", jres, result);
}
////////////////////////////////////////////////////////////////////////////

int cmdrun(const char *command){
   printf("# cmdrun: %s", command);
   int res = system(command);
   printf(" | %d\n", res);
   return res;
}
void libgame_load(){
   printf("libgame_load\n");
   char olibfilename[] = "./libgame.so";
   //cmdrun("make libgame.so");
   printf("dlopening %s...\n", olibfilename);
   _libgame = dlopen( olibfilename , RTLD_NOW );
   printf("  >>>  _libgame=%p\n", _libgame );
   ////////////////////////////////////////////////////////////////////// 
   if( _libgame ){
      GameHandlers * newgamehandlers = (GameHandlers *) malloc(sizeof(GameHandlers));
      newgamehandlers->pinit   = (T_GAME_INIT)   dlsym( _libgame, "game_init");   if(!newgamehandlers->pinit)   printf("Cannot load symbol game_init: %s\n",   dlerror());
      newgamehandlers->prender = (T_GAME_RENDER) dlsym( _libgame, "game_render"); if(!newgamehandlers->prender) printf("Cannot load symbol game_render: %s\n", dlerror());
      newgamehandlers->ponkey  = (T_GAME_ON_KEY) dlsym( _libgame, "game_onkey");  if(!newgamehandlers->ponkey)  printf("Cannot load symbol game_onkey: %s\n",  dlerror());
      printf("  >>>  dlsym results: game.pinit=%p | game.ponkey=%p | game.prender=%p\n", (void*)newgamehandlers->pinit, (void*)newgamehandlers->ponkey, (void*)newgamehandlers->prender);
      atomic_store( &game.handlers, reinterpret_cast<intptr_t>(newgamehandlers) );
   }
}

void libgame_close(){
   printf("libgame_close\n");
   if( game.handlers ) {
       //GameHandlers * oldgamehandlers = reinterpret_cast<GameHandlers *>( game.handlers );
       atomic_store( &game.handlers, 0);
       //free( oldgamehandlers );
   }
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
