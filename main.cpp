#include <stdio.h>

#include "common.h"
#include "game.h"
#include "window.h"
#include "reloader.h"
#include <GL/glut.h>

Game game;

int main(int argc, char **argv){
   libgame_load();
   if( game.pinit ) game.pinit( &game );
   
   glutInit(&argc,argv);   
   GLFWwindow* window = window_setup();
   window_loop( window );
   window_cleanup( window );
   
   libgame_close();
   
   return 0;
}
