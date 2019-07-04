#include <stdlib.h>
#include <stdio.h>

#include "common.h"
#include "window.h"
#include "game.h"
#include "reloader.h"

static void error_callback(int error, const char* description) {
   printf("error_callback error: %d\n", error);
   fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
   if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
      glfwSetWindowShouldClose(window, GL_TRUE);
      return;
   }
   if (key == GLFW_KEY_TAB ){
      if( action == GLFW_PRESS){
         printf("TAB pressed!\n");
         libgame_reload();
      }
      return;
   }
   if( game.ponkey ) game.ponkey( &game, key, scancode, action, mods );
}

GLFWwindow *window_setup() {
   GLFWwindow* window;   
   glfwSetErrorCallback(error_callback);   
   if (!glfwInit()) exit(EXIT_FAILURE);

   window = glfwCreateWindow(800, 600, "CBreakout", NULL, NULL);
   if (!window){
      glfwTerminate();
      exit(EXIT_FAILURE);
   }
   
   glfwMakeContextCurrent(window);
   glfwSwapInterval(1);
   
   glfwSetKeyCallback(window, key_callback);
   glEnable(GL_DEPTH_TEST);
//   glEnable(GL_CULL_FACE);
   
   return window;
}

void window_loop(GLFWwindow *window) {
   while (!glfwWindowShouldClose(window)){
      float ratio;
      int width, height;
      glfwGetFramebufferSize(window, &width, &height);
      ratio = width / (float) height;
      
      glViewport(0, 0, width, height);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
      glMatrixMode(GL_MODELVIEW);

      glLoadIdentity();
      if( game.prender ) game.prender(&game);
      
      glFlush();
      glfwSwapBuffers(window);
      glfwPollEvents();      
   }
}

void window_cleanup(GLFWwindow *window) {
   glfwDestroyWindow(window);
   glfwTerminate();   
}
