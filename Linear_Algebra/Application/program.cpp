#include "program.h"

#include <algorithm>

#include "cube.h"
#include "matrix_helper_3d.h"
#include "space_ship.h"

using namespace math;

namespace application
{
	program::program(
		const int window_width, const int window_height,
		const float fov_y, const float z_near, const float z_far, bool debug):
		current_state_(util::program_state::running),
		camera_{ std::make_unique<camera>() },
		sdl_manager_{std::make_unique<sdl::sdl_manager>(window_width, window_height, fov_y, z_near, z_far, *camera_, debug, current_state_)}
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
		setup_camera();
		
		setup_spaceship();


	}

	auto program::start() -> void
	{
		sdl_manager_->start_loop();
	}

	auto program::setup_spaceship() -> void
	{
		auto space_ship_obj = std::make_unique<space_ship>("space_ship_rblx.obj");

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

	auto program::setup_camera() -> void
	{
		const auto raw_target = std::make_unique<matrix3d>(0.f, 0.f, 0.01f);

		const auto target = camera_->position() + *raw_target;

		camera_->point_at(*target);
		
		camera_->update_camera_matrix();
		
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

		// TODO move copy pasted code into functions; do this after functionality testing
		
		auto callback_up = [&camera_ref = *camera_, this](const SDL_Event& e, const float elapsed_time) mutable
		{
			if (auto* camera_ptr = &camera_ref; camera_ptr == nullptr)
			{
				return;
			}

			camera_ref.position().z() += 200.0f * elapsed_time;
			camera_->update_camera_matrix();
		};

		auto callback_down = [&camera_ref = *camera_, this](const SDL_Event& e, const float elapsed_time) mutable
		{
			if (auto* camera_ptr = &camera_ref; camera_ptr == nullptr)
			{
				return;
			}

			camera_ref.position().z() -= 200.0f * elapsed_time;
			camera_->update_camera_matrix();
		};

		auto callback_left = [&camera_ref = *camera_, this](const SDL_Event& e, const float elapsed_time) mutable
		{
			if (auto* camera_ptr = &camera_ref; camera_ptr == nullptr)
			{
				return;
			}

			camera_ref.position().x() += 200.0f * elapsed_time;
			camera_->update_camera_matrix();
		};

		auto callback_right = [&camera_ref = *camera_, this](const SDL_Event& e, const float elapsed_time) mutable
		{
			if (auto* camera_ptr = &camera_ref; camera_ptr == nullptr)
			{
				return;
			}

			camera_ref.position().x() -= 200.0f * elapsed_time;
			camera_->update_camera_matrix();
		};

		auto callback_pgup = [&camera_ref = *camera_, this](const SDL_Event& e, const float elapsed_time) mutable
		{
			if (auto* camera_ptr = &camera_ref; camera_ptr == nullptr)
			{
				return;
			}

			camera_ref.position().y() += 200.0f * elapsed_time;
			camera_->update_camera_matrix();
		};
		auto callback_pgdown = [&camera_ref = *camera_, this](const SDL_Event& e, const float elapsed_time) mutable
		{
			if (auto* camera_ptr = &camera_ref; camera_ptr == nullptr)
			{
				return;
			}

			camera_ref.position().y() -= 200.0f * elapsed_time;
			camera_->update_camera_matrix();
		};

		// CAMERA CONTROLS
		sdl_manager_->add_input_listener(SDL_SCANCODE_UP, callback_up);
		sdl_manager_->add_input_listener(SDL_SCANCODE_DOWN, callback_down);
		sdl_manager_->add_input_listener(SDL_SCANCODE_LEFT, callback_left);
		sdl_manager_->add_input_listener(SDL_SCANCODE_RIGHT, callback_right);
		sdl_manager_->add_input_listener(SDL_SCANCODE_PAGEUP, callback_pgup);
		sdl_manager_->add_input_listener(SDL_SCANCODE_PAGEDOWN, callback_pgdown);
	}
}
