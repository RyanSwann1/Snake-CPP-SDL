#include "Window.h"
#include "Game.h"
#include "Character.h"

#include <SDL.h>
#include <iostream>

int main(int argc, char* args[])
{
	Window window;
	Game game(window);


	SDL_Event e;
	Character player;

	//Begin game loop
	while(!game.isGameOver())
	{
		
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT) {
				game.endGame();
			}
		}
		game.update(player);
		game.render(window, player);

		SDL_Delay(16); //Simulate 60fps - Will change to proper thing
	}


	//SDL_Delay(4000);
	return 0;
}

/*
JmCriat: 1) A menu (with a start button and a config bottom (despite not having nothing to config you should include a multi buttom menu to work as training)
JmCriat: 2) A score counter. it can be something simple but add a HUD, with the number of things eat, maybe the number of deaths.
JmCriat: 3) Make a way to get out of the game to the menu, be that pressing ESC key, or a buttom on the game.
JmCriat: 4) if you want to do something more, i would recommend creating a level system somehow.


*/