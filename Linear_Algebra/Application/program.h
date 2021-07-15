#pragma once
#include <memory>

#include "mesh.h"
#include "progam_state.h"
#include "sdl_manager.h"

namespace application
{
	class program
	{
	private:
		util::program_state current_state_;
		std::unique_ptr<sdl::sdl_manager> sdl_manager_;
		shape::mesh meshCube;
	
	public:
		program(int window_width, int window_height);
		auto get_state() const -> util::program_state;
		auto run() -> void;

	private:
		auto setup() -> void;
		auto setup_controls() const -> void;
		auto start() -> void;
	};
}


