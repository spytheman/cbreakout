#include "game.h"
#include <GLFW/glfw3.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

Game game;

Game::Game(){
   this->init(); 
}

void Game::init(){
   srand(time(NULL));
   this->ball = new Ball(50,50,10);
   this->paddle = new Paddle(400, 600);         
}

void printGameState(Game *g){
   printf("frames: %5d t:%8.3f |", g->frames, g->t);
   g->ball->print();
   g->paddle->print();
   g->bricks[0].print();
   printf("\n");
}

void showTriangle1(){
   glBegin(GL_TRIANGLES);
   glColor3f(1.f, 0.f, 0.f);    glVertex3f(-0.8f, -0.6f, 0.f);
   glColor3f(0.f, 1.f, 0.f);    glVertex3f( 0.8f, -0.6f, 0.f);
   glColor3f(0.f, 0.f, 1.f);    glVertex3f( 0.f,   0.8f, 0.f);
   glEnd();
}

void showTriangle2(){
   glBegin(GL_TRIANGLES);
   glColor3f(0.5f, 0.f,  0.f);    glVertex3f(-0.5f, -0.4f, 0.3f);
   glColor3f(0.f,  0.5f, 0.f);    glVertex3f( 0.5f, -0.4f, 0.3f);
   glColor3f(0.f,  0.f,  0.5f);   glVertex3f( 0.f,   0.5f, 0.3f);
   glEnd();
}

void Game::render(){
   this->t = (float) glfwGetTime();
   this->frames++;
   if( this->frames % 60 == 0 ) printGameState(this);
   glRotatef( this->t * -50.f, 0.f, 0.f, 1.f);    showTriangle1();
   glRotatef( this->t * 120.f, 2.f, 1.f, 1.f);    showTriangle2();
}

void Game::onKey(int key, int scancode, int action, int mods){
   printf("Game::onKey key:%d scancode:%d action:%d mods:%d\n", key, scancode, action, mods);
}
