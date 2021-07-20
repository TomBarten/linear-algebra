#pragma once
#include <SDL.h>

#include <functional>

namespace application::sdl
{
	typedef std::function<void(SDL_Event, float)> input_handler_fn;
}
