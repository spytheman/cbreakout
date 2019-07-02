#include <stdio.h>

#include "common.h"
#include "window.h"

int main(int argc, char **argv){
   printf("main()\n");
   GLFWwindow* window = window_setup();
   window_loop( window );
   window_cleanup( window );
   return 0;
}
