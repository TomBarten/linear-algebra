// Only for testing purposes; SDL(2) setup.

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <iostream>
#include "vector2d.h"

const auto WIDTH = 525.f;
const auto HEIGHT = 525.f;

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

	if(SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) != 0)
	{
		std::cout << "Could not create window, SDL Error: " << SDL_GetError();

		return 1;
	}

	const float origin_x = WIDTH / 2.f;
	const float origin_y = HEIGHT / 2.f;

	SDL_bool done = SDL_FALSE;

	while (!done)
	{
		SDL_Event event;

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

		SDL_RenderDrawLineF(renderer, 0, origin_y, WIDTH, origin_y);
		SDL_RenderDrawLineF(renderer, origin_x, 0, origin_x, HEIGHT);

		const auto vector_x = std::make_unique<math::vector2d>(origin_x + 50, origin_y + 0);

		const auto vector_y = std::make_unique<math::vector2d>(origin_x + 0, origin_y + 50);

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

		SDL_RenderDrawLineF(renderer, origin_x, origin_y, vector_x->x(), vector_x->y());

		SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
		
		SDL_RenderDrawLineF(renderer, origin_x, origin_y, vector_y->x(), vector_y->y());

		const auto vector_xy = (*vector_x) + (*vector_y);

		SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);

		SDL_RenderDrawLineF(renderer, origin_x, origin_y, vector_xy->x(), vector_xy->y());

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
	
	return 0;
}
