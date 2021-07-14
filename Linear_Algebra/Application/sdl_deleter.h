#pragma once

#include <SDL.h>

namespace application::sdl
{
	struct sdl_deleter
	{
		auto operator()(SDL_Renderer* renderer_ptr) const -> void;
		auto operator()(SDL_Window* window_ptr)  const -> void;
	};
}
