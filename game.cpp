#include "game.h"

Game::Game(){
   printf("Game()\n");
   this->init(); 
}

void Game::init(){
   this->ball = new Ball(50,50,10);
   this->paddle = new Paddle(400, 600);         
}

void Game::render(){
   this->frames++;
   printf("game->render() frames: %06d |", this->frames);
   this->ball->print();
   this->paddle->print();
   this->bricks[0].print();
   printf("\n");
}

void Game::onKey(int key, int scancode, int action, int mods){
   printf("Game::onKey key:%d scancode:%d action:%d mods:%d\n", key, scancode, action, mods);
}


Game game;
