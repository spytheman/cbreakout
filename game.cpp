#include "game.h"
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define ICLAMP(x, xmin, xmax )  x = ( x < xmin ) ? xmin : ( ( x > xmax ) ? xmax :  x )

void game_init(Game *g){
   srand(time(NULL));
   g->ball = new Ball(-40, 100, 1);
   g->paddle = new Paddle(0, -100);         
}

void game_printstate(Game *g){
   printf("Frames: %5d t:%8.3f | g: %p", g->frames, g->t, (void *)g);
   g->ball->print();
   g->paddle->print();
   g->bricks[0].print();
   g->bricks[1].print();
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

void showPaddle(Game *g){
   //glLoadIdentity(); glTranslatef( -0.5 * sin(this->t), -0.5, -0.5 ); glRotatef( this->t * 25.f, 0.5f, 0.5f, 1.f);   glScalef( 0.5, 0.5, 0.5 );  glutWireTeapot(1.0);
    //    g->paddle->x = -100;
    g->paddle->y = -100;
   glLoadIdentity();
   glTranslatef( g->paddle->x / 112.0, 0.11 + g->paddle->y / 100.0, 0.0);
   glRotatef( 3.14f, 1.f, 1.f, 0.0f);
   glScalef( 0.8, 0.15, 1.0 );
   glColor3f(0.5, 0.0, 0.0 );
   glutWireCube(1.0);
}
void showBall(Game *g){
   //glLoadIdentity(); glTranslatef( -0.5 * sin(this->t), -0.5, -0.5 ); glRotatef( this->t * 25.f, 0.5f, 0.5f, 1.f);   glScalef( 0.5, 0.5, 0.5 );  glutWireTeapot(1.0);
   glLoadIdentity();
   glTranslatef( g->ball->x / 112.0, 0.11 + g->ball->y / 100.0, 0);
   glRotatef( 15.14f * g->t, 1.f, 1.f, 0.0f);
   glScalef( 0.2, 0.2, 0.2 );
   glColor3f(0.5, 0.5, 0.0 );
   glutWireSphere(1.0, 15, 15);
}
void showBricks(Game *g){
   //glLoadIdentity(); glTranslatef( -0.5 * sin(this->t), -0.5, -0.5 ); glRotatef( this->t * 25.f, 0.5f, 0.5f, 1.f);   glScalef( 0.5, 0.5, 0.5 );  glutWireTeapot(1.0);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, 0.0);
   glRotatef( 2.f, 0.f, 0.f, 1.5f);
   glRotatef( 50.f * g->t, 5.f, 4.f, 3.0f);
   glScalef( 0.2, 0.1, 0.1 );
   glColor3f(0.5, 0.5, 0.5 );
   glutWireCube(1.0);
}
void showBackground(Game *g){
    //   return;
   glLoadIdentity(); glRotatef( g->t * -50.f, 0.f, 0.f, 1.f);    showTriangle1();
   glLoadIdentity(); glRotatef( g->t * 120.f, 2.f, 1.f, 1.f);    showTriangle2();
   glLoadIdentity(); glTranslatef(  0.0,  0.0,    0.5*cos(g->t) ); glRotatef( g->t *  70.f, 0.5f, 0.5f, 1.f);   glScalef( 0.5, 0.5, 0.5 );  showCube();
   glLoadIdentity(); glTranslatef(  0.5,  0.5*cos(g->t),    0.5 ); glRotatef( g->t * -70.f, 0.5f, 0.5f, 1.f);   glScalef( 0.5, 0.5, 0.5 );  showCube();
   glLoadIdentity(); glTranslatef( -0.5 * sin(g->t), -0.5, -0.5 ); glRotatef( g->t * 150.f, 0.5f, 0.5f, 1.f);   glScalef( 0.5, 0.5, 0.5 );  showCube();   
   glColor3f(0.25, 0.25, 0.55 );
   glLoadIdentity(); glTranslatef( -0.5 * sin(g->t), -0.5, -0.5 ); glRotatef( g->t * 25.f, 0.5f, 0.5f, 1.f);   glScalef( 0.5, 0.5, 0.5 );  glutWireTeapot(1.0);
}

void game_update(Game *g){
    //printf("game_update y: %d g:%p\n", g->ball->y, (void*)g);
    {
        g->ball->x += g->ball->dx;
        g->ball->y += g->ball->dy;
        ICLAMP( g->ball->x, -120, 120 );
        ICLAMP( g->ball->y, -120, 120 );
    }
    {
        g->paddle->x += g->paddle->dx;
        g->paddle->y += g->paddle->dy;
        ICLAMP( g->paddle->x, -120, 120 );
        ICLAMP( g->paddle->y, -120, 120 );
    }
}
void game_render(Game *g){
   g->t = (float) glfwGetTime();
   g->frames++;
   ///////////////////////////////////////////////////////
   if( g->frames % 60 == 0 ) game_printstate(g);
   game_update(g);
   //   showBackground(g);
   showPaddle(g);
   showBall(g);
   showBricks(g);   
}

void game_onkey(Game *g, int key, int scancode, int action, int mods){
   printf("game_onkey game: %p | key:%d scancode:%d action:%d mods:%d\n", (void*)g, key, scancode, action, mods);

   if( key == GLFW_KEY_R )  game_init(g);

   if( key == GLFW_KEY_RIGHT ) g->paddle->dx =  3;
   if( key == GLFW_KEY_LEFT )  g->paddle->dx = -3;
   if( key == GLFW_KEY_UP )  g->paddle->dx = 0;
}

