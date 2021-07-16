// Only for testing purposes; SDL(2) setup.

//#define SDL_MAIN_HANDLED
//#include <SDL.h>
//#include <iostream>
//
//#include "matrix_helper_2d.h"
//#include "matrix2d.h"
//#include "matrix3d.h"
//
//const auto WIDTH = 500;
//const auto HEIGHT = 500;
//
//const auto X_ORIGIN = WIDTH / 2.f;
//const auto Y_ORIGIN = HEIGHT / 2.f;
//
//inline auto draw_sdl_pixel(SDL_Renderer* renderer, float x, float y, const uint8_t r, const uint8_t g, const uint8_t b)
//{
//	x += X_ORIGIN;
//	y += Y_ORIGIN;
//	y = HEIGHT - 1 - y;
//
//	SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
//
//	SDL_RenderDrawPointF(renderer, x, y);
//}
//
//inline auto draw_sdl_line(SDL_Renderer* renderer, float x1, float y1, float x2, float y2, const uint8_t r, const uint8_t g, const uint8_t b)
//{
//	x1 += X_ORIGIN;
//	y1 += Y_ORIGIN;
//	y1 = HEIGHT - 1 - y1;
//
//	x2 += X_ORIGIN;
//	y2 += Y_ORIGIN;
//	y2 = HEIGHT - 1 - y2;
//
//	SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
//
//	SDL_RenderDrawLineF(renderer, x1, y1, x2, y2);
//}
//
//auto main() -> int
//{
//	if (SDL_Init(SDL_INIT_VIDEO) != 0)
//	{
//		std::cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
//
//		return 1;
//	}
//	
//	std::cout << "SDL initialization succeeded!";
//
//	SDL_Window* window = nullptr;
//
//	SDL_Renderer* renderer = nullptr;
//
//	if(SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) != 0)
//	{
//		std::cout << "Could not create window, SDL Error: " << SDL_GetError();
//
//		return 1;
//	}
//
//	SDL_bool done = SDL_FALSE;
//
//	while (!done)
//	{
//		SDL_Event event;
//
//		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
//		
//		SDL_RenderClear(renderer);
//
//		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
//
//		const auto vector_z = std::make_unique<math::matrix3d>(0, 0, 50);
//
//		const auto vector_x = std::make_unique<math::matrix2d>(50, 0);
//
//		draw_sdl_line(renderer, 0,  0, vector_x->x(), vector_x->y(), 255, 0, 0);
//
//
//		const auto vector_y = std::make_unique<math::matrix2d>(0, 50);
//
//		draw_sdl_line(renderer, 0,  0, vector_y->x(), vector_y->y(), 0, 255, 0);
//
//		auto vector_xy = (*vector_x) + (*vector_y);
//
//		const auto m_matrix = math::create_scale_matrix_2d(2, 2);
//
//		const auto scaled_vector_xy = vector_xy->scale((*m_matrix));
//		
//		draw_sdl_line(renderer, 0 , 0, scaled_vector_xy->x(), scaled_vector_xy->y(), 0, 0, 255);
//		draw_sdl_line(renderer, 0, 0, vector_xy->x(), vector_xy->y(), 255, 255, 0);
//
//
//		vector_xy = (*vector_x) - (*vector_y);
//
//		draw_sdl_line(renderer, 0 , 0, vector_xy->x(), vector_xy->y(), 0, 255, 255);
//
//		(*vector_xy) *= -1;
//
//		draw_sdl_line(renderer, 0 , 0, vector_xy->x(), vector_xy->y(), 255, 0, 255);
//
//		SDL_RenderPresent(renderer);
//
//		while (SDL_PollEvent(&event))
//		{
//			if (event.type == SDL_QUIT)
//			{
//				done = SDL_TRUE;
//			}
//		}
//	}
//
//	if (renderer)
//	{
//		SDL_DestroyRenderer(renderer);
//	}
//
//	if (window)
//	{
//		SDL_DestroyWindow(window);
//	}
//
//	SDL_Quit();
//	
//	return 0;
//}

#define SDL_MAIN_HANDLED

#include <iostream>

#include "console_helpers.h"
#include "program.h"

using namespace application::util;

const auto WIDTH = 500;
const auto HEIGHT = 500;

static auto handle_exception(const std::exception_ptr& exception_ptr) -> void
{
    try
    {
        if (exception_ptr)
        {
            std::rethrow_exception(exception_ptr);
        }
    }
    catch (const std::exception& exception)
    {
	    clear_console();

        std::cerr << "Exception thrown:\n\"" << exception.what() << "\"\n";

	    pause_console();
    }
}

static auto run_program() -> void
{
    const auto program = std::make_unique<application::program>(WIDTH, HEIGHT);

    try
    {
        program->run();
    }
    catch (...)
    {
        const auto& exception = std::current_exception();

        handle_exception(exception);
    }
}

auto main() -> int
{
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);

    run_program();
	
    _CrtDumpMemoryLeaks();

    return 0;
}
