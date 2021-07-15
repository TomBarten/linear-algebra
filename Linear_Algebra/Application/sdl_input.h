#pragma once
#include <SDL.h>

#include <functional>

namespace application::sdl
{
	typedef std::function<void(SDL_Event)> input_handler_fn;
}
