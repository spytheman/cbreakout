#include <stdio.h>

#include "common.h"
#include "window.h"
#include <GL/glut.h>

int main(int argc, char **argv){
   glutInit(&argc,argv);
   GLFWwindow* window = window_setup();
   window_loop( window );
   window_cleanup( window );
   return 0;
}
