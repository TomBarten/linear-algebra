#include "program.h"

#include <algorithm>
#include <iostream>
#include <ostream>
#include <string>

#include "matrix2d.h"
#include "matrix3d.h"

using namespace math;
using namespace application::shape;

namespace application
{
	program::program(const int window_width, const int window_height):
		current_state_(util::program_state::running),
		sdl_manager_{std::make_unique<sdl::sdl_manager>(window_width, window_height, current_state_)},
		meshCube{std::make_unique<mesh>()}
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
		setup_controls();

		// SOUTH
		meshCube->emplace_back(std::move(std::make_unique<triangle>(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f)));
		meshCube->emplace_back(std::move(std::make_unique<triangle>(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f)));

		// EAST
		meshCube->emplace_back(std::move(std::make_unique<triangle>(1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f)));
		meshCube->emplace_back(std::move(std::make_unique<triangle>(1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f)));

		// NORTH
		meshCube->emplace_back(std::move(std::make_unique<triangle>(1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f)));
		meshCube->emplace_back(std::move(std::make_unique<triangle>(1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f)));

		// WEST
		meshCube->emplace_back(std::move(std::make_unique<triangle>(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f)));
		meshCube->emplace_back(std::move(std::make_unique<triangle>(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f)));

		// TOP
		meshCube->emplace_back(std::move(std::make_unique<triangle>(0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f)));
		meshCube->emplace_back(std::move(std::make_unique<triangle>(0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f)));

		// BOTTOM
		meshCube->emplace_back(std::move(std::make_unique<triangle>(1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f)));
		meshCube->emplace_back(std::move(std::make_unique<triangle>(1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f)));
	}

	auto program::setup_controls() const -> void
	{
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

		auto vector_x = std::make_unique<matrix2d>(50, 0);

		
		auto callback_method_example = [vector_x = *vector_x, this](const SDL_Event& e) mutable
		{
			vector_x *= 2;

			sdl_manager_->draw_line(0, 0, vector_x.x(), vector_x.y(), 255, 0, 0);
			
			std::cout << "KEY EVENT: " << std::to_string(e.key.keysym.scancode) << " MODIFIER: " << std::to_string(e.key.keysym.mod) << std::endl;
		};

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
	}

	auto program::start() -> void
	{
		sdl_manager_->start_loop();
	}
}
