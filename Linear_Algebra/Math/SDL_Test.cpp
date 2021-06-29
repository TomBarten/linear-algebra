// Only for testing purposes; SDL(2) setup.

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <iostream>

auto main() -> int
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
	}
	else
	{
		std::cout << "SDL initialization succeeded!";
	}

	std::cin.get();

	return 0;
}
