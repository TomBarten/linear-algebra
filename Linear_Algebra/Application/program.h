#pragma once
#include <memory>

#include "progam_state.h"
#include "sdl_manager.h"

namespace application
{
	class program
	{
	private:
		std::unique_ptr<sdl::sdl_manager> sdl_manager_;
		util::program_state current_state_;
	
	public:
		program(int window_width, int window_height);
		auto get_state() const -> util::program_state;
		auto run() -> void;

	private:
		auto start() const -> void;
	};
}


