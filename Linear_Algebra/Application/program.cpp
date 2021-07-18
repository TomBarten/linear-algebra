#include "program.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <sstream>

#include "matrix3d.h"

using namespace math;

namespace application
{
	program::program(
		const int window_width, const int window_height,
		const float fov_y, const float z_near, const float z_far):
		current_state_(util::program_state::running),
		sdl_manager_{std::make_unique<sdl::sdl_manager>(window_width, window_height, fov_y, z_near, z_far, current_state_)}
	{
	}

	auto program::get_state() const -> util::program_state
	{
		return current_state_;
	}

	auto program::run() -> void
	{
		setup();
		start();
	}

	auto program::setup() -> void
	{
		auto mesh_cube = std::make_shared<mesh_simple>();
		
		parse_obj_file(R"(C:\Repositories\Avans\Minor\LINAL\space_ship.obj)", mesh_cube->tris);

		//mesh_cube->tris =
		//{
		//	// SOUTH
		//	{ matrix3d(0.0f, 0.0f, 0.0f), matrix3d(0.0f, 1.0f, 0.0f), matrix3d(1.0f, 1.0f, 0.0f) },
		//	{ matrix3d(0.0f, 0.0f, 0.0f), matrix3d(1.0f, 1.0f, 0.0f), matrix3d(1.0f, 0.0f, 0.0f) },

		//	// EAST
		//	{ matrix3d(1.0f, 0.0f, 0.0f), matrix3d(1.0f, 1.0f, 0.0f), matrix3d(1.0f, 1.0f, 1.0f) },
		//	{ matrix3d(1.0f, 0.0f, 0.0), matrix3d(1.0f, 1.0f, 1.0), matrix3d(1.0f, 0.0f, 1.0f) },

		//	// NORTH
		//	{ matrix3d(1.0f, 0.0f, 1.0), matrix3d(1.0f, 1.0f, 1.0), matrix3d(0.0f, 1.0f, 1.0f) },
		//	{ matrix3d(1.0f, 0.0f, 1.0), matrix3d(0.0f, 1.0f, 1.0), matrix3d(0.0f, 0.0f, 1.0f) },

		//	// WEST
		//	{ matrix3d(0.0f, 0.0f, 1.0), matrix3d(0.0f, 1.0f, 1.0), matrix3d(0.0f, 1.0f, 0.0f) },
		//	{ matrix3d(0.0f, 0.0f, 1.0), matrix3d(0.0f, 1.0f, 0.0), matrix3d(0.0f, 0.0f, 0.0f) },

		//	// TOP
		//	{ matrix3d(0.0f, 1.0f, 0.0), matrix3d(0.0f, 1.0f, 1.0), matrix3d(1.0f, 1.0f, 1.0f) },
		//	{ matrix3d(0.0f, 1.0f, 0.0), matrix3d(1.0f, 1.0f, 1.0), matrix3d(1.0f, 1.0f, 0.0f) },

		//	// BOTTOM
		//	{ matrix3d(1.0f, 0.0f, 1.0), matrix3d(0.0f, 0.0f, 1.0), matrix3d(0.0f, 0.0f, 0.0f) },
		//	{ matrix3d(1.0f, 0.0f, 1.0), matrix3d(0.0f, 0.0f, 0.0), matrix3d(1.0f, 0.0f, 0.0f) },
		//};

		auto callback_method_example = [mesh = mesh_cube, this](const SDL_Event& e) mutable
		{
			for(auto &[p] : mesh->tris)
			{
				for(auto& matrix : p)
				{
					matrix *= 1.5;
				}
			}
			
			std::cout << "KEY EVENT: " << std::to_string(e.key.keysym.scancode) << " MODIFIER: " << std::to_string(e.key.keysym.mod) << std::endl;
		};

		// TODO: controls handling
		/*
		 * Space ship controls:
		 *
		 * W: UP
		 * S: DOWN
		 * A: LEFT
		 * D: RIGHT
		 * Q: ROTATE LEFT
		 * E: ROTATE RIGHT
		 * SPACEBAR: SHOOT
		 * (OPTIONAL) H: TOGGLE (ON/OFF) AIM-LINE FOR SHOOTING:
		 *
		 *
		 * Camera controls:
		 *
		 * ARROW KEYS: UP, DOWN, LEFT, RIGHT
		 * PAGE UP: UP
		 * PAGE DOWN: DOWN
		 */

		// CAMERA CONTROLS
		sdl_manager_->add_input_listener(SDL_SCANCODE_UP, callback_method_example);
		sdl_manager_->add_input_listener(SDL_SCANCODE_DOWN, callback_method_example);
		sdl_manager_->add_input_listener(SDL_SCANCODE_LEFT, callback_method_example);
		sdl_manager_->add_input_listener(SDL_SCANCODE_RIGHT, callback_method_example);
		sdl_manager_->add_input_listener(SDL_SCANCODE_PAGEUP, callback_method_example); // SAME CALLBACK AS UP
		sdl_manager_->add_input_listener(SDL_SCANCODE_PAGEDOWN, callback_method_example); // SAME CALLBACK AS DOWN

		// SPACECRAFT CONTROLS
		sdl_manager_->add_input_listener(SDL_SCANCODE_W, callback_method_example); // CHECK SHIFT MODIFIER
		sdl_manager_->add_input_listener(SDL_SCANCODE_A, callback_method_example);
		sdl_manager_->add_input_listener(SDL_SCANCODE_S, callback_method_example); // CHECK SHIFT MODIFIER
		sdl_manager_->add_input_listener(SDL_SCANCODE_D, callback_method_example);
		sdl_manager_->add_input_listener(SDL_SCANCODE_Q, callback_method_example);
		sdl_manager_->add_input_listener(SDL_SCANCODE_E, callback_method_example);
		sdl_manager_->add_input_listener(SDL_SCANCODE_SPACE, callback_method_example);
		sdl_manager_->add_input_listener(SDL_SCANCODE_H, callback_method_example); // OPTIONAL

		sdl_manager_->add_mesh(std::move(mesh_cube));
	}

	auto program::start() -> void
	{
		sdl_manager_->start_loop();
	}

	auto program::parse_obj_file(const std::string& obj_file_location, std::vector<triangle_simple>& tris) const -> bool
	{
		std::ifstream file_stream(obj_file_location);

		if (!file_stream.is_open())
		{
			return false;
		}

		auto vectors = std::vector<matrix3d>();

		std::string file_line;

		while (std::getline(file_stream, file_line))
		{
			std::stringstream ss;

			ss << file_line;

			char identifier;

			if (file_line[0] == 'v')
			{
				matrix3d vector;

				ss >> identifier >> vector.x() >> vector.y() >> vector.z();

				vectors.push_back(vector);
			}
			else if (file_line[0] == 'f')
			{
				// triangle has 3 points
				int vector_indexes[3]{};

				ss >> identifier >> vector_indexes[0] >> vector_indexes[1] >> vector_indexes[2];

				// file index starts counting at 1 not 0 so - 1
				tris.push_back({ vectors[vector_indexes[0] - 1], vectors[vector_indexes[1] - 1], vectors[vector_indexes[2] - 1] });
			}
		}

		return true;
	}
}
