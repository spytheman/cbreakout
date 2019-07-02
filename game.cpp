#include "game.h"
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

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

void showCube(){
   
   //Multi-colored side - FRONT
   glBegin(GL_POLYGON);
   glColor3f( 1.0, 0.0, 0.0 );     glVertex3f(  0.5, -0.5, -0.5 );      // P1 is red
   glColor3f( 0.0, 1.0, 0.0 );     glVertex3f(  0.5,  0.5, -0.5 );      // P2 is green
   glColor3f( 0.0, 0.0, 1.0 );     glVertex3f( -0.5,  0.5, -0.5 );      // P3 is blue
   glColor3f( 1.0, 0.0, 1.0 );     glVertex3f( -0.5, -0.5, -0.5 );      // P4 is purple
   glEnd();   
   
   
   // White side - BACK
   glBegin(GL_POLYGON);
   glColor3f(   1.0,  1.0, 1.0 );
   glVertex3f(  0.5, -0.5, 0.5 );
   glVertex3f(  0.5,  0.5, 0.5 );
   glVertex3f( -0.5,  0.5, 0.5 );
   glVertex3f( -0.5, -0.5, 0.5 );
   glEnd();
     
   // Purple side - RIGHT
   glBegin(GL_POLYGON);
   glColor3f(  1.0,  0.0,  1.0 );
   glVertex3f( 0.5, -0.5, -0.5 );
   glVertex3f( 0.5,  0.5, -0.5 );
   glVertex3f( 0.5,  0.5,  0.5 );
   glVertex3f( 0.5, -0.5,  0.5 );
   glEnd();
     
   // Green side - LEFT
   glBegin(GL_POLYGON);
   glColor3f(   0.0,  1.0,  0.0 );
   glVertex3f( -0.5, -0.5,  0.5 );
   glVertex3f( -0.5,  0.5,  0.5 );
   glVertex3f( -0.5,  0.5, -0.5 );
   glVertex3f( -0.5, -0.5, -0.5 );
   glEnd();
     
   // Blue side - TOP
   glBegin(GL_POLYGON);
   glColor3f(   0.0,  0.0,  1.0 );
   glVertex3f(  0.5,  0.5,  0.5 );
   glVertex3f(  0.5,  0.5, -0.5 );
   glVertex3f( -0.5,  0.5, -0.5 );
   glVertex3f( -0.5,  0.5,  0.5 );
   glEnd();
     
   // Red side - BOTTOM
   glBegin(GL_POLYGON);
   glColor3f(   1.0,  0.0,  0.0 );
   glVertex3f(  0.5, -0.5, -0.5 );
   glVertex3f(  0.5, -0.5,  0.5 );
   glVertex3f( -0.5, -0.5,  0.5 );
   glVertex3f( -0.5, -0.5, -0.5 );
   glEnd();   
}

void Game::render(){
   this->t = (float) glfwGetTime();
   this->frames++;
   if( this->frames % 60 == 0 ) printGameState(this);
   glLoadIdentity(); glRotatef( this->t * -50.f, 0.f, 0.f, 1.f);    showTriangle1();
   glLoadIdentity(); glRotatef( this->t * 120.f, 2.f, 1.f, 1.f);    showTriangle2();
   glLoadIdentity(); glTranslatef(  0.0,  0.0,    0.5*cos(this->t) ); glRotatef( this->t *  70.f, 0.5f, 0.5f, 1.f);   glScalef( 0.5, 0.5, 0.5 );  showCube();
   glLoadIdentity(); glTranslatef(  0.5,  0.5*cos(this->t),    0.5 ); glRotatef( this->t * -70.f, 0.5f, 0.5f, 1.f);   glScalef( 0.5, 0.5, 0.5 );  showCube();
   glLoadIdentity(); glTranslatef( -0.5 * sin(this->t), -0.5, -0.5 ); glRotatef( this->t * 150.f, 0.5f, 0.5f, 1.f);   glScalef( 0.5, 0.5, 0.5 );  showCube();
   
   glLoadIdentity(); glTranslatef( -0.5 * sin(this->t), -0.5, -0.5 ); glRotatef( this->t * 25.f, 0.5f, 0.5f, 1.f);   glScalef( 0.5, 0.5, 0.5 );  glutWireTeapot(1.0);
}

void Game::onKey(int key, int scancode, int action, int mods){
   printf("Game::onKey key:%d scancode:%d action:%d mods:%d\n", key, scancode, action, mods);
}
