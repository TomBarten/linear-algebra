#include "program.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <sstream>

#include "matrix3d.h"
#include "matrix_helper_3d.h"
#include "space_ship.h"

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
		setup_spaceship();
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
		//sdl_manager_->add_input_listener(SDL_SCANCODE_UP, callback_method_example);
		//sdl_manager_->add_input_listener(SDL_SCANCODE_DOWN, callback_method_example);
		//sdl_manager_->add_input_listener(SDL_SCANCODE_LEFT, callback_method_example);
		//sdl_manager_->add_input_listener(SDL_SCANCODE_RIGHT, callback_method_example);
		//sdl_manager_->add_input_listener(SDL_SCANCODE_PAGEUP, callback_method_example); // SAME CALLBACK AS UP
		//sdl_manager_->add_input_listener(SDL_SCANCODE_PAGEDOWN, callback_method_example); // SAME CALLBACK AS DOWN		
	}

	auto program::start() -> void
	{
		sdl_manager_->start_loop();
	}

	auto program::setup_spaceship() -> void
	{
		auto space_ship_obj = std::make_unique<space_ship>(R"(C:\Repositories\Avans\Minor\LINAL\space_ship_rblx.obj)");

		auto callback_w = [&mesh = *space_ship_obj, this](const SDL_Event& e) mutable
		{
			if (auto* mesh_ptr = &mesh; mesh_ptr == nullptr)
			{
				return;
			}

			const auto rot_matrix_x = get_rot_matrix_x(-4);

			for (auto& [points] : mesh.shape().triangles())
			{
				for (auto& matrix : points)
				{
					auto rot_result = matrix.multiply_by_4X4(*rot_matrix_x);

					matrix.x() = rot_result->x();
					matrix.y() = rot_result->y();
					matrix.z() = rot_result->z();
				}
			}

			std::cout << "KEY EVENT: " << std::to_string(e.key.keysym.scancode) << " MODIFIER: " << std::to_string(e.key.keysym.mod) << std::endl;
		};

		auto callback_a = [&mesh = *space_ship_obj, this](const SDL_Event& e) mutable
		{
			if (auto* mesh_ptr = &mesh; mesh_ptr == nullptr)
			{
				return;
			}

			const auto rot_matrix_y = get_rot_matrix_y(-4);

			for (auto& [points] : mesh.shape().triangles())
			{
				for (auto& matrix : points)
				{
					auto rot_result = matrix.multiply_by_4X4(*rot_matrix_y);

					matrix.x() = rot_result->x();
					matrix.y() = rot_result->y();
					matrix.z() = rot_result->z();
				}
			}

			std::cout << "KEY EVENT: " << std::to_string(e.key.keysym.scancode) << " MODIFIER: " << std::to_string(e.key.keysym.mod) << std::endl;
		};

		auto callback_s = [&mesh = *space_ship_obj, this](const SDL_Event& e) mutable
		{
			if (auto* mesh_ptr = &mesh; mesh_ptr == nullptr)
			{
				return;
			}

			const auto rot_matrix_x = get_rot_matrix_x(4);

			for (auto& [points] : mesh.shape().triangles())
			{
				for (auto& matrix : points)
				{
					auto rot_result = matrix.multiply_by_4X4(*rot_matrix_x);

					matrix.x() = rot_result->x();
					matrix.y() = rot_result->y();
					matrix.z() = rot_result->z();
				}
			}

			std::cout << "KEY EVENT: " << std::to_string(e.key.keysym.scancode) << " MODIFIER: " << std::to_string(e.key.keysym.mod) << std::endl;
		};

		auto callback_d = [&mesh = *space_ship_obj, this](const SDL_Event& e) mutable
		{
			if (auto* mesh_ptr = &mesh; mesh_ptr == nullptr)
			{
				return;
			}

			const auto rot_matrix_y = get_rot_matrix_y(4);

			for (auto& [points] : mesh.shape().triangles())
			{
				for (auto& matrix : points)
				{
					auto rot_result = matrix.multiply_by_4X4(*rot_matrix_y);

					matrix.x() = rot_result->x();
					matrix.y() = rot_result->y();
					matrix.z() = rot_result->z();
				}
			}

			std::cout << "KEY EVENT: " << std::to_string(e.key.keysym.scancode) << " MODIFIER: " << std::to_string(e.key.keysym.mod) << std::endl;
		};

		auto callback_q = [&mesh = *space_ship_obj, this](const SDL_Event& e) mutable
		{
			if (auto* mesh_ptr = &mesh; mesh_ptr == nullptr)
			{
				return;
			}

			const auto rot_matrix_z = get_rot_matrix_z(-4);

			for (auto& [points] : mesh.shape().triangles())
			{
				for (auto& matrix : points)
				{
					auto rot_result = matrix.multiply_by_4X4(*rot_matrix_z);

					matrix.x() = rot_result->x();
					matrix.y() = rot_result->y();
					matrix.z() = rot_result->z();
				}
			}

			std::cout << "KEY EVENT: " << std::to_string(e.key.keysym.scancode) << " MODIFIER: " << std::to_string(e.key.keysym.mod) << std::endl;
		};

		auto callback_e = [&mesh = *space_ship_obj, this](const SDL_Event& e) mutable
		{
			if (auto* mesh_ptr = &mesh; mesh_ptr == nullptr)
			{
				return;
			}

			const auto rot_matrix_z = get_rot_matrix_z(4);

			for (auto& [points] : mesh.shape().triangles())
			{
				for (auto& matrix : points)
				{
					auto rot_result = matrix.multiply_by_4X4(*rot_matrix_z);

					matrix.x() = rot_result->x();
					matrix.y() = rot_result->y();
					matrix.z() = rot_result->z();
				}
			}

			std::cout << "KEY EVENT: " << std::to_string(e.key.keysym.scancode) << " MODIFIER: " << std::to_string(e.key.keysym.mod) << std::endl;
		};

		auto callback_space = [&mesh = *space_ship_obj, this](const SDL_Event& e) mutable
		{
			if (auto* mesh_ptr = &mesh; mesh_ptr == nullptr)
			{
				return;
			}

			std::cout << "KEY EVENT: " << std::to_string(e.key.keysym.scancode) << " MODIFIER: " << std::to_string(e.key.keysym.mod) << std::endl;
		};

		auto callback_shift = [&mesh = *space_ship_obj, this](const SDL_Event& e) mutable
		{
			if (auto* mesh_ptr = &mesh; mesh_ptr == nullptr)
			{
				return;
			}

			std::cout << "KEY EVENT: " << std::to_string(e.key.keysym.scancode) << " MODIFIER: " << std::to_string(e.key.keysym.mod) << std::endl;
		};

		auto callback_h = [&mesh = *space_ship_obj, this](const SDL_Event& e) mutable
		{
			if (auto* mesh_ptr = &mesh; mesh_ptr == nullptr)
			{
				return;
			}

			std::cout << "KEY EVENT: " << std::to_string(e.key.keysym.scancode) << " MODIFIER: " << std::to_string(e.key.keysym.mod) << std::endl;
		};

		// SPACECRAFT CONTROLS
		sdl_manager_->add_input_listener(SDL_SCANCODE_W, callback_w);
		sdl_manager_->add_input_listener(SDL_SCANCODE_A, callback_a);
		sdl_manager_->add_input_listener(SDL_SCANCODE_S, callback_s);
		sdl_manager_->add_input_listener(SDL_SCANCODE_D, callback_d);
		sdl_manager_->add_input_listener(SDL_SCANCODE_Q, callback_q);
		sdl_manager_->add_input_listener(SDL_SCANCODE_E, callback_e);
		sdl_manager_->add_input_listener(SDL_SCANCODE_SPACE, callback_space);
		sdl_manager_->add_input_listener(SDL_SCANCODE_LSHIFT, callback_shift);
		sdl_manager_->add_input_listener(SDL_SCANCODE_RSHIFT, callback_shift);
		sdl_manager_->add_input_listener(SDL_SCANCODE_H, callback_h); // OPTIONAL

		sdl_manager_->add_obj(std::move(space_ship_obj));
	}
}
