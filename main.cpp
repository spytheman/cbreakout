#include <stdio.h>

#include "common.h"
#include "game.h"
#include "window.h"
#include "reloader.h"
#include <GL/glut.h>
#include <signal.h>

Game game;

void sighandler(int);
void sighandler(int signum) {
   printf("Caught signal %d...\n", signum);
   libgame_reload();   
}

int main(int argc, char **argv){
   libgame_load();
   if( game.pinit ) game.pinit( &game );
   signal(SIGUSR1, sighandler);
   
   glutInit(&argc,argv);   
   GLFWwindow* window = window_setup();
   window_loop( window );
   window_cleanup( window );
   
   libgame_close();
   
   return 0;
}
