// Only for testing purposes; SDL(2) setup.

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <iostream>
#include "vector2d.h"

const auto WIDTH = 500;
const auto HEIGHT = 500;

const auto x_origin = WIDTH / 2.f;
const auto y_origin = HEIGHT / 2.f;

inline auto draw_sdl_pixel(SDL_Renderer* renderer, float x, float y, const uint8_t r, const uint8_t g, const uint8_t b)
{
	x += x_origin;
	y += y_origin;
	y = HEIGHT - 1 - y;

	SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);

	SDL_RenderDrawPointF(renderer, x, y);
}

inline auto draw_sdl_line(SDL_Renderer* renderer, float x1, float y1, float x2, float y2, const uint8_t r, const uint8_t g, const uint8_t b)
{
	x1 += x_origin;
	y1 += y_origin;
	y1 = HEIGHT - 1 - y1;

	x2 += x_origin;
	y2 += y_origin;
	y2 = HEIGHT - 1 - y2;

	SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);

	SDL_RenderDrawLineF(renderer, x1, y1, x2, y2);
}

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

	const float origin_x = 0;
	const float origin_y = 0;

	SDL_bool done = SDL_FALSE;

	while (!done)
	{
		SDL_Event event;

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

		//SDL_RenderDrawLineF(renderer, 0, origin_y, WIDTH, origin_y);
		//SDL_RenderDrawLineF(renderer, origin_x, 0, origin_x, HEIGHT);

		//const auto vector_origin = std::make_unique<math::vector2d>(0,0);

		//draw_sdl_pixel(renderer, vector_origin->x(), vector_origin->y(), 255, 0, 0);

		const auto vector_x = std::make_unique<math::vector2d>(50, 0);

		draw_sdl_line(renderer, 0,  0, vector_x->x(), vector_x->y(), 255, 0, 0);


		const auto vector_y = std::make_unique<math::vector2d>(0, 50);

		draw_sdl_line(renderer, 0,  0, vector_y->x(), vector_y->y(), 0, 255, 0);

		auto vector_xy = (*vector_x) + (*vector_y);

		draw_sdl_line(renderer, 0 , 0, vector_xy->x(), vector_xy->y(), 255, 255, 0);

		(*vector_xy) *= -1;

		draw_sdl_line(renderer, 0 , 0, vector_xy->x(), vector_xy->y(), 0, 0, 255);


		vector_xy = (*vector_x) - (*vector_y);

		draw_sdl_line(renderer, 0 , 0, vector_xy->x(), vector_xy->y(), 0, 255, 255);

		(*vector_xy) *= -1;

		draw_sdl_line(renderer, 0 , 0, vector_xy->x(), vector_xy->y(), 255, 0, 255);

		//const auto vector_x = std::make_unique<math::vector2d>(origin_x + 50, origin_y + 0);

		//SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

		//SDL_RenderDrawLineF(renderer, origin_x, origin_y, vector_x->x(), vector_x->y());
		//

		//const auto vector_y = std::make_unique<math::vector2d>(origin_x + 0, origin_y + 50);

		//SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
		//
		//SDL_RenderDrawLineF(renderer, origin_x, origin_y, vector_y->x(), vector_y->y());

		//
		//const auto vector_xy_addition = (*vector_x) + (*vector_y);

		//(*vector_xy_addition) *= 2.f;

		//SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);

		//SDL_RenderDrawLineF(renderer, origin_x, origin_y, vector_xy_addition->x(), vector_xy_addition->y());


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
