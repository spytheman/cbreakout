#ifndef __CBREAKOUT_WINDOW_H
#define __CBREAKOUT_WINDOW_H

#include <GLFW/glfw3.h>

GLFWwindow *window_setup();
void window_loop(GLFWwindow *window);
void window_cleanup(GLFWwindow *window);

#endif
