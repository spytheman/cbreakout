#include <stdio.h>
#include "common.h"

int main(int argc, char **argv){
    Ball *b = new Ball(50,50,10);
    Paddle *p = new Paddle(400, 600);
    Brick bricks[60];

    b->print();
    p->print();
    bricks[0].print();
    
    return 0;
}
