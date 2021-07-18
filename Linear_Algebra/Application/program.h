#pragma once

#include <memory>
#include <string>

#include "progam_state.h"
#include "sdl_manager.h"

namespace application
{
	class program
	{
	private:
		typedef std::pair<SDL_Scancode, sdl::input_handler_fn> sdl_scancode_callback_pair;
		util::program_state current_state_;
		std::unique_ptr<sdl::sdl_manager> sdl_manager_;
	
	public:
		program(int window_width, int window_height, float fov_y, float z_near, float z_far);
		auto get_state() const -> util::program_state;
		auto run() -> void;

	private:
		auto setup() -> void;
		auto start() -> void;

		auto parse_obj_file(const std::string& obj_file_location, std::vector<triangle_simple>& tris) const -> bool;
	};
}


