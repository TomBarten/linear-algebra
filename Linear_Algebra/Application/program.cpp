#include "program.h"

#include <stdexcept>

namespace application
{
	program::program(const int window_width, const int window_height):
		sdl_manager_{std::make_unique<sdl::sdl_manager>(window_width, window_height)},
		current_state_(util::program_state::running)
	{
	}

	auto program::get_state() const -> util::program_state
	{
		return current_state_;
	}

	auto program::run() -> void
	{
		start();
	}

	auto program::start() const -> void
	{
		
	}
}
