#include "game.h"
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define ICLAMP(x, xmin, xmax )  x = ( x < xmin ) ? xmin : ( ( x > xmax ) ? xmax :  x )

void game_init(Game *g){
   srand(time(NULL));
   g->ball = new Ball(-40, 100, 1);
   g->paddle = new Paddle(0, -100);
   g->bricks = new Brick[60];
   //atomic_store( &g->handlers, 0 );
}

void game_printstate(Game *g){
   printf("zFrames: %5d t:%8.3f | g: %p", g->frames, g->t, (void *)g);
   g->ball->print();
   g->paddle->print();
   g->bricks[0].print();
   g->bricks[1].print();
   printf("\n");
}

void showPaddle(Game *g){
   glLoadIdentity();
   glTranslatef( g->paddle->x / 112.0, 0.11 + g->paddle->y / 100.0, 0.0);
   glRotatef( 3.14f, 1.f, 1.f, 0.0f);
   glScalef( 0.8, 0.15, 1.0 );
   glColor3f(0.5, 0.0, 0.1 );
   glutWireCube(1.0);
}

void showBall(Game *g){
   glLoadIdentity();
   glTranslatef( g->ball->x / 112.0, 0.11 + g->ball->y / 100.0, 0);
   glRotatef( 235.14f * g->t, 5.5f, 5.f, 8.0f);
   glScalef( 0.2, 0.2, 0.2 );
   glColor3f(0.1, 0.2, 0.9 );
   glutWireSphere(1.0, 15, 15);
}

void showBricks(Game *g){
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, 0.0);
   glRotatef( 2.f, 0.f, 0.f, 1.5f);
   glRotatef( 50.f * g->t, 5.f, 4.f, 3.0f);
   glScalef( 0.2, 0.1, 0.1 );
   glColor3f(0.5, 0.5, 0.5 );
   glutWireCube(1.0);
}

void showBackground(Game *g){
    //TODO
    if(0){
        printf("g: %p\n", (void*)g);
    }
}

void game_update(Game *g){
    //printf("game_update y: %d g:%p\n", g->ball->y, (void*)g);
    {
        g->ball->x += g->ball->dx;
        g->ball->y += g->ball->dy;
        if( g->ball->dy < 0 && g->ball->y < -90 ) g->ball->dy *= -1;
        if( g->ball->dy > 0 && g->ball->y >  72 ) g->ball->dy *= -1;
        if( g->ball->dx < 0 && g->ball->x < -128 ) g->ball->dx *= -1;
        if( g->ball->dx > 0 && g->ball->x >  128 ) g->ball->dx *= -1;
        ICLAMP( g->ball->x, -130, 130 );
        ICLAMP( g->ball->y, -90, 72 );
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
   game_update(g);
   if( g->frames % 60 == 0 ) game_printstate(g);
   showBackground(g);
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

X::X(){
    this->setName(strdup("X"));
    this->x = 0;
    this->y = 0;
    this->w = 0;
    this->h = 0;
    this->dx = 0;
    this->dy = 0;
}

void X::setName(char *s){
    this->name=s;
}

void X::print(){
    printf("%6s: xy %3d, %3d ; wh %3d, %3d |", this->name, this->x, this->y, this->w, this->h);
}

Brick::Brick(){
    this->setName( strdup("Brick") );
    this->x = 0;
    this->y = 0;
    this->w = 40;
    this->h = 10;
}

Brick::Brick(int x, int y){
    this->setName( strdup("Brick") );
    this->x = x;
    this->y = y;
    this->w = 40;
    this->h = 10;
}

Ball::Ball(int x, int y, int r){
    this->setName( strdup("Ball") );
    this->x = x;
    this->y = y;
    this->w = r;
    this->h = r;
    this->dx =  1;
    this->dy = -1;
}
Paddle::Paddle(int x, int y){ 
    this->setName( strdup("Paddle") );
    this->x = x;
    this->y = y;
    this->w = 40;
    this->h = 6;
}

