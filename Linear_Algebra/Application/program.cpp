#include "program.h"

#include <algorithm>

#include "target_obj.h"
#include "axis.h"
#include "bullet.h"
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
		setup_target();
	}

	auto program::start() -> void
	{
		sdl_manager_->start_loop();
	}

	auto program::setup_spaceship() -> void
	{
		auto space_ship_obj = std::make_unique<space_ship>("space_ship_rblxV2.obj");

		auto space_ship_controls = [space_ship = space_ship_obj.get(), this](const SDL_Event& e, const float elapsed_time) mutable
		{
			if (space_ship == nullptr || !space_ship->is_valid())
			{
				return;
			}

			const uint8_t* key_state = SDL_GetKeyboardState(nullptr);

			auto matrices = std::vector<std::unique_ptr<matrix>>();

			if (key_state[SDL_SCANCODE_SPACE])
			{
				auto projectile = space_ship->shoot();

				sdl_manager_->add_obj(std::move(projectile));
			}

			if (key_state[SDL_SCANCODE_W])
			{
				matrices.push_back(std::move(space_ship->get_pitch_matrix(true, elapsed_time)));
			}

			if (key_state[SDL_SCANCODE_A])
			{
				matrices.push_back(std::move(space_ship->get_yaw_matrix(false, elapsed_time)));
			}

			if (key_state[SDL_SCANCODE_S])
			{
				matrices.push_back(std::move(space_ship->get_pitch_matrix(false, elapsed_time)));
			}

			if (key_state[SDL_SCANCODE_D])
			{
				matrices.push_back(std::move(space_ship->get_yaw_matrix(true, elapsed_time)));
			}

			if (key_state[SDL_SCANCODE_Q])
			{
				matrices.push_back(std::move(space_ship->get_roll_matrix(true, elapsed_time)));
			}

			if (key_state[SDL_SCANCODE_E])
			{
				matrices.push_back(std::move(space_ship->get_roll_matrix(false, elapsed_time)));
			}

			const auto matrix_m = get_identity_matrix();

			for(auto r_it = matrices.rbegin(); r_it != matrices.rend(); ++r_it)
			{
				const auto& rot_matrix = (*r_it);
				
				*matrix_m *= *rot_matrix;
			}

			space_ship->calculate_rotation(*matrix_m);

			if(key_state[SDL_SCANCODE_LSHIFT] || key_state[SDL_SCANCODE_RSHIFT])
			{
				space_ship->move(elapsed_time);
			}
		};

		// SPACECRAFT CONTROLS
		sdl_manager_->add_input_listener(SDL_SCANCODE_W, space_ship_controls);
		sdl_manager_->add_input_listener(SDL_SCANCODE_A, space_ship_controls);
		sdl_manager_->add_input_listener(SDL_SCANCODE_S, space_ship_controls);
		sdl_manager_->add_input_listener(SDL_SCANCODE_D, space_ship_controls);
		sdl_manager_->add_input_listener(SDL_SCANCODE_Q, space_ship_controls);
		sdl_manager_->add_input_listener(SDL_SCANCODE_E, space_ship_controls);
		sdl_manager_->add_input_listener(SDL_SCANCODE_SPACE, space_ship_controls);
		sdl_manager_->add_input_listener(SDL_SCANCODE_LSHIFT, space_ship_controls);
		sdl_manager_->add_input_listener(SDL_SCANCODE_RSHIFT, space_ship_controls);

		sdl_manager_->add_obj(std::move(space_ship_obj));
	}

	auto program::setup_camera() -> void
	{
		camera_->look_at();
		
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
		
		auto callback_camera = [this](const SDL_Event& e, const float elapsed_time) mutable
		{
			const uint8_t* key_state = SDL_GetKeyboardState(nullptr);

			auto& direction = camera_->get_direction();

			const auto new_direction = direction * (200.f * elapsed_time);

			if(key_state[SDL_SCANCODE_PAGEUP])
			{
				camera_->position().y() += 200.f * elapsed_time;
			}

			if(key_state[SDL_SCANCODE_PAGEDOWN])
			{
				camera_->position().y() -= 200.f * elapsed_time;
			}

			if(key_state[SDL_SCANCODE_UP])
			{
				camera_->position() = *(camera_->position() + *new_direction);
			}

			if (key_state[SDL_SCANCODE_DOWN])
			{
				camera_->position() = *(camera_->position() - *new_direction);
			}

			if(key_state[SDL_SCANCODE_LEFT])
			{
				camera_->position().x() -= 200.f * elapsed_time;
			}

			if(key_state[SDL_SCANCODE_RIGHT])
			{
				camera_->position().x() += 200.f * elapsed_time;
			}

			camera_->update_camera_matrix();
		};

		// CAMERA CONTROLS
		sdl_manager_->add_input_listener(SDL_SCANCODE_UP, callback_camera);
		sdl_manager_->add_input_listener(SDL_SCANCODE_DOWN, callback_camera);
		sdl_manager_->add_input_listener(SDL_SCANCODE_LEFT, callback_camera);
		sdl_manager_->add_input_listener(SDL_SCANCODE_RIGHT, callback_camera);
		sdl_manager_->add_input_listener(SDL_SCANCODE_PAGEUP, callback_camera);
		sdl_manager_->add_input_listener(SDL_SCANCODE_PAGEDOWN, callback_camera);
	}

	auto program::setup_target() const -> void
	{
		const auto target_location = std::make_unique<matrix3d>(150, 150, -150);
		
		auto target = std::make_unique<target_obj>(*target_location, "target_rblxV2.obj");

		sdl_manager_->add_obj(std::move(target));
	}
}
