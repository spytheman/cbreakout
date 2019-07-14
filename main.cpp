#include <stdio.h>

#include "common.h"
#include "game.h"
#include "window.h"
#include "reloader.h"
#include <GL/glut.h>

Game game;

int main(int argc, char **argv){
   libgame_load();
   reinterpret_cast<GameHandlers *>( game.handlers )->pinit( &game );
   reloader_init();
   
   glutInit(&argc,argv);   
   GLFWwindow* window = window_setup();
   window_loop( window );
   window_cleanup( window );

   reloader_cleanup();
   libgame_close();
   
   return 0;
}
