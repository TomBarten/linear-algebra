// Only for testing purposes; SDL(2) setup.

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <iostream>

auto main() -> int
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL initialization failed. SDL Error: " << SDL_GetError();

		return 1;
	}
	
	std::cout << "SDL initialization succeeded!";

	SDL_Window* window = nullptr;

	SDL_Renderer* renderer = nullptr;

	if(SDL_CreateWindowAndRenderer(1000, 900, 0, &window, &renderer) != 0)
	{
		std::cout << "Could not create window, SDL Error: " << SDL_GetError();

		return 1;
	}

	SDL_bool done = SDL_FALSE;

	while (!done)
	{
		SDL_Event event;

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLine(renderer, 320, 200, 300, 240);
		SDL_RenderDrawLine(renderer, 300, 240, 340, 240);
		SDL_RenderDrawLine(renderer, 340, 240, 320, 200);
		SDL_RenderPresent(renderer);

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				done = SDL_TRUE;
			}
		}
	}

	if (renderer)
	{
		SDL_DestroyRenderer(renderer);
	}

	if (window)
	{
		SDL_DestroyWindow(window);
	}

	SDL_Quit();
	
	std::cin.get();

	return 0;
}
