A simple breakout game using GLFW and C++ .

Use arrows to move the paddle. 

Your goal is to keep the ball from falling through the floor.

NB: If you have a unix editor/IDE, which has a setup to simply run 
make on a shortkey (that is easily done in emacs/vim/sublime ),
you will have a much quicker feedback loop, because that runs the 
default make target 'make reload', recompiling only libgame.so, 
which is very quick (below ~160ms on my machine), then sends 
a SIGUSR1 signal to the running game, which in turn knows how 
to reload the updated libgame.so file, *without* losing your 
game state... In effect, you have live reloading in c++ :-) ...

Building:
	make clean all

Editing / live reloading / hot swapping game code:
	1) start ./cbreakout in a terminal
  2) edit game.cpp, save your changes
  3) run 'make refresh', or just 'make'
  
==>The game will load the new libgame.so produced by make.

Enjoy!
