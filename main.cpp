#include <stdio.h>
#include <GL/glut.h>
#include "window.h"
#include "reloader.h"

int main(int argc, char **argv){
   reloader_init();
   
   glutInit(&argc,argv);   
   GLFWwindow* window = window_setup();
   window_loop( window );
   window_cleanup( window );
   
   reloader_cleanup();
   return 0;
}
