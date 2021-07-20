#include "program.h"

#include <algorithm>

#include "matrix_helper_3d.h"
#include "space_ship.h"

using namespace math;

namespace application
{
	program::program(
		const int window_width, const int window_height,
		const float fov_y, const float z_near, const float z_far, bool debug):
		current_state_(util::program_state::running),
		sdl_manager_{
			std::make_unique<sdl::sdl_manager>(window_width, window_height, fov_y, z_near, z_far, debug, current_state_)
		}
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
		auto space_ship_obj = std::make_unique<space_ship>(R"(C:\Repositories\Avans\Minor\LINAL\axis_rblx.obj)");

		auto callback_w = [&space_ship = *space_ship_obj, this](const SDL_Event& e, const float elapsed_time) mutable
		{
			if (auto* mesh_ptr = &space_ship; mesh_ptr == nullptr)
			{
				return;
			}

			space_ship.pitch(true, elapsed_time);
		};

		auto callback_a = [&space_ship = *space_ship_obj, this](const SDL_Event& e, const float elapsed_time) mutable
		{
			if (auto* mesh_ptr = &space_ship; mesh_ptr == nullptr)
			{
				return;
			}

			space_ship.yaw(false, elapsed_time);
		};

		auto callback_s = [&space_ship = *space_ship_obj, this](const SDL_Event& e, const float elapsed_time) mutable
		{
			if (auto* mesh_ptr = &space_ship; mesh_ptr == nullptr)
			{
				return;
			}

			space_ship.pitch(false, elapsed_time);
		};

		auto callback_d = [&space_ship = *space_ship_obj, this](const SDL_Event& e, const float elapsed_time) mutable
		{
			if (auto* mesh_ptr = &space_ship; mesh_ptr == nullptr)
			{
				return;
			}

			space_ship.yaw(true, elapsed_time);
		};

		auto callback_q = [&space_ship = *space_ship_obj, this](const SDL_Event& e, const float elapsed_time) mutable
		{
			if (auto* mesh_ptr = &space_ship; mesh_ptr == nullptr)
			{
				return;
			}

			space_ship.roll(true, elapsed_time);
		};

		auto callback_e = [&space_ship = *space_ship_obj, this](const SDL_Event& e, const float elapsed_time) mutable
		{
			if (auto* mesh_ptr = &space_ship; mesh_ptr == nullptr)
			{
				return;
			}

			space_ship.roll(false, elapsed_time);
		};

		auto callback_space = [&space_ship = *space_ship_obj, this](const SDL_Event& e, const float elapsed_time) mutable
		{
			if (auto* mesh_ptr = &space_ship; mesh_ptr == nullptr)
			{
				return;
			}
		};

		auto callback_shift = [&space_ship = *space_ship_obj, this](const SDL_Event& e, const float elapsed_time) mutable
		{
			if (auto* mesh_ptr = &space_ship; mesh_ptr == nullptr)
			{
				return;
			}
		};

		auto callback_h = [&space_ship = *space_ship_obj, this](const SDL_Event& e, const float elapsed_time) mutable
		{
			if (auto* mesh_ptr = &space_ship; mesh_ptr == nullptr)
			{
				return;
			}
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
