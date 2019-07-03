#include <stdio.h>

#include "common.h"
#include "game.h"
#include "window.h"
#include "reloader.h"
#include <GL/glut.h>

Game game;

int main(int argc, char **argv){
   game.init();
   
   libgame_load();

   glutInit(&argc,argv);   
   GLFWwindow* window = window_setup();
   window_loop( window );
   window_cleanup( window );
   
   libgame_close();
   
   return 0;
}
