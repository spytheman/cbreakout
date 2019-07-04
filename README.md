A simple breakout game using GLFW and C++ .
=======================================================

Use arrows to move the paddle. 

Your goal is to keep the ball from falling through the floor.

NB: If you have a unix editor/IDE, which has a setup to simply run
make on a shortkey (that is easily done in emacs/vim/sublime ),
you will have a _much_ quicker feedback loop, because it will run
the default make target 'make reload', recompiling _only_ libgame.so, 
which is very quick (below ~160ms on my machine), then it will send 
a SIGUSR1 signal to the running game, which in turn knows how to 
reload the updated libgame.so file, _without_ losing your game state... 
In effect, you will have live code reloading in c++ :-) ...


Building:
=======================================================
```shell
	make clean all
```

Editing / live reloading / hot swapping game code:
=======================================================
1) start ./cbreakout in a terminal
2) edit game.cpp, save your changes
3) run 'make refresh', or just 'make'
  
==>The game will load the new libgame.so produced by make.


Enjoy!
