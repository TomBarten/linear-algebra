#include "sdl_deleter.h"

namespace application::sdl
{
	auto sdl_deleter::operator()(SDL_Renderer* renderer_ptr) const -> void
	{
		if(renderer_ptr != nullptr)
		{
			SDL_DestroyRenderer(renderer_ptr);
		}
	}

	auto sdl_deleter::operator()(SDL_Window* window_ptr) const -> void
	{
		if(window_ptr != nullptr)
		{
			SDL_DestroyWindow(window_ptr);
		}
	}
}
