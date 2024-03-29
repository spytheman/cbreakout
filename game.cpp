#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "game.h"

/////////////////////////////////////////////////////////////////////////////////////
class X {
 public:
    int x,y; // center of the object
    int w,h; // half width and half height - distances to the edges
    int dx;
    int dy;
    char *name;
    X();
    void setName(char *s);
    void print();
};

class Brick: public X { 
 public: 
    Brick();
    Brick(int x, int y);
};

class Ball: public X{
 public:
    Ball(int x, int y, int r);
};

class Paddle: public X{
 public:
    Paddle(int x, int y);
};
/////////////////////////////////////////////////////////////////////////////////////

#define ICLAMP(x, xmin, xmax )  x = ( x < xmin ) ? xmin : ( ( x > xmax ) ? xmax :  x )

struct GameState {
 public:
   int frames = 0;
   int oldframes = 0;
   float t = 0.0f;
   Ball *ball = NULL;
   Paddle *paddle = NULL;
   Brick *bricks = NULL;
};

void game_init(Game *g){
   srand(time(NULL));
   g->state = new GameState();
   g->state->ball = new Ball(-40, 100, 1);
   g->state->paddle = new Paddle(0, -100);
   g->state->bricks = new Brick[60];
   //atomic_store( &g->handlers, 0 );
}

/// zzz
void game_printstate(Game *g){
   int fps = g->state->frames - g->state->oldframes;
   g->state->oldframes = g->state->frames;
   printf("f: %5d fps: %2d t:%8.3f | ", g->state->frames, fps, g->state->t);
   g->state->ball->print();
   g->state->paddle->print();
   g->state->bricks[0].print();
   printf("\n");
}

void showPaddle(Game *g){
   glLoadIdentity();
   glTranslatef( g->state->paddle->x / 112.0, 0.11 + g->state->paddle->y / 100.0, 0.0);
   glRotatef( 3.14f, 1.f, 1.f, 0.0f);
   glScalef( 0.8, 0.15, 1.0 );
   glColor3f(0.5, 0.0, 0.1 );
   glutWireCube(1.0);
}

void showBall(Game *g){
   glLoadIdentity();
   glTranslatef( g->state->ball->x / 112.0, 0.11 + g->state->ball->y / 100.0, 0);
   glRotatef( 235.14f * g->state->t, 5.5f, 5.f, 8.0f);
   glScalef( 0.2, 0.2, 0.2 );
   glColor3f(0.1, 0.2, 0.9 );
   glutWireSphere(1.0, 15, 15);
}

void showBricks(Game *g){
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, 0.0);
   glRotatef( 2.f, 0.f, 0.f, 1.5f);
   glRotatef( 50.f * g->state->t, 5.f, 4.f, 3.0f);
   glScalef( 0.2, 0.1, 0.1 );
   glColor3f(0.5, 0.5, 0.5 );
   glutWireCube(1.0);
}

void showBackground(Game *g){
    if(0)printf("g: %p\n", (void*)g); //TODO
}

void game_update(Game *g){
    {
        g->state->ball->x += g->state->ball->dx;
        g->state->ball->y += g->state->ball->dy;
        if( g->state->ball->dy < 0 && g->state->ball->y < -90 ) g->state->ball->dy *= -1;
        if( g->state->ball->dy > 0 && g->state->ball->y >  72 ) g->state->ball->dy *= -1;
        if( g->state->ball->dx < 0 && g->state->ball->x < -128 ) g->state->ball->dx *= -1;
        if( g->state->ball->dx > 0 && g->state->ball->x >  128 ) g->state->ball->dx *= -1;
        ICLAMP( g->state->ball->x, -130, 130 );
        ICLAMP( g->state->ball->y, -90, 72 );
    }
    {
        g->state->paddle->x += g->state->paddle->dx;
        g->state->paddle->y += g->state->paddle->dy;
        ICLAMP( g->state->paddle->x, -120, 120 );
        ICLAMP( g->state->paddle->y, -120, 120 );
    }
}

void game_render(Game *g){
   g->state->t = (float) glfwGetTime();
   g->state->frames++;
   ///////////////////////////////////////////////////////
   game_update(g);
   if( g->state->frames % 60 == 0 ) game_printstate(g);
   showBackground(g);
   showPaddle(g);
   showBall(g);
   showBricks(g);   
}

void game_onkey(Game *g, int key, int scancode, int action, int mods){
   printf("game_onkey game: %p | key:%d scancode:%d action:%d mods:%d\n", (void*)g, key, scancode, action, mods);

   if( key == GLFW_KEY_R && action == GLFW_PRESS)  game_init(g);

   if( key == GLFW_KEY_RIGHT ) g->state->paddle->dx =  3;
   if( key == GLFW_KEY_LEFT )  g->state->paddle->dx = -3;
   if( key == GLFW_KEY_UP )  g->state->paddle->dx = 0;
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
    printf("%5s:%4d,%4d %4d,%4d |", this->name, this->x, this->y, this->w, this->h);
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
    printf("New %s created ... %p\n", this->name, (void *)this);
}
Paddle::Paddle(int x, int y){    
    this->setName( strdup("Pad") );
    this->x = x;
    this->y = y;
    this->w = 40;
    this->h = 6;
    printf("New %s created ... %p\n", this->name, (void *)this);
}
