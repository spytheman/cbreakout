#include <stdio.h>

#include "common.h"
#include "game.h"
#include "window.h"
#include <GL/glut.h>

Game game;

int main(int argc, char **argv){
   glutInit(&argc,argv);
   GLFWwindow* window = window_setup();
   window_loop( window );
   window_cleanup( window );
   return 0;
}
