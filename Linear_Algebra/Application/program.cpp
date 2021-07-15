#include "program.h"

#include <algorithm>
#include <iostream>
#include <ostream>
#include <string>

using namespace math;
using namespace application::shape;

namespace application
{
	program::program(const int window_width, const int window_height):
		current_state_(util::program_state::running),
		sdl_manager_{std::make_unique<sdl::sdl_manager>(window_width, window_height, current_state_)}
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

		auto test1a = std::make_unique<matrix3d>(0.0f, 0.0f, 0.0f);
		auto test2a = std::make_unique<matrix3d>(0.0f, 0.0f, 0.0f);
		auto test3a = std::make_unique<matrix3d>(0.0f, 0.0f, 0.0f);
		
		//std::unique_ptr<matrix3d> pa[3] = { std::move(test1a), std::move(test2a), std::move(test3a) };

		struct test
		{
			std::unique_ptr<matrix3d> p[3];
		};

		// TODO this is bad
		//std::vector testb = { std::move(testa) };

		auto test1 = matrix3d(0.0f, 0.0f, 0.0f);
		auto test2 = matrix3d(0.0f, 1.0f, 0.0f);
		auto test3 = matrix3d(1.0f, 1.0f, 0.0f);

		matrix3d p[3] = { (std::move(matrix3d(0.0f, 0.0f, 0.0f))), (std::move(matrix3d(0.0f, 1.0f, 0.0f))), (std::move(matrix3d(1.0f, 1.0f, 0.0f))) };
		
		
		//const auto item1 = p[0];
		
		//meshCube.tris = 
		//{
			// SOUTH
			/*{ (std::move(matrix3d(0.0f, 0.0f, 0.0f))), (std::move(matrix3d(0.0f, 1.0f, 0.0f))), (std::move(matrix3d(1.0f, 1.0f, 0.0f))) },*/
			/*{ std::move(std::make_unique<matrix3d>(0.0f, 0.0f, 0.0f)), std::move(std::make_unique<matrix3d>(0.0f, 1.0f, 0.0f)), std::move(std::make_unique<matrix3d>(1.0f, 1.0f, 0.0f)) },*/
			//{ matrix3d(0.0f, 0.0f, 0.0f), matrix3d(1.0f, 1.0f, 0.0f), matrix3d(1.0f, 0.0f, 0.0f) },

			//// EAST                                                      
			//{ matrix3d(1.0f, 0.0f, 0.0f), matrix3d(1.0f, 1.0f, 0.0f), matrix3d(1.0f, 1.0f, 1.0f) },
			//{ matrix3d(1.0f, 0.0f, 0.0f), matrix3d(1.0f, 1.0f, 1.0f), matrix3d(1.0f, 0.0f, 1.0f) },

			//// NORTH                                                     
			//{ matrix3d(1.0f, 0.0f, 1.0f), matrix3d(1.0f, 1.0f, 1.0f), matrix3d(0.0f, 1.0f, 1.0f) },
			//{ matrix3d(1.0f, 0.0f, 1.0f), matrix3d(0.0f, 1.0f, 1.0f), matrix3d(0.0f, 0.0f, 1.0f) },

			//// WEST                                                      
			//{ matrix3d(0.0f, 0.0f, 1.0f), matrix3d(0.0f, 1.0f, 1.0f), matrix3d(0.0f, 1.0f, 0.0f) },
			//{ matrix3d(0.0f, 0.0f, 1.0f), matrix3d(0.0f, 1.0f, 0.0f), matrix3d(0.0f, 0.0f, 0.0f) },

			//// TOP                                                       
			//{ matrix3d(0.0f, 1.0f, 0.0f), matrix3d(0.0f, 1.0f, 1.0f), matrix3d(1.0f, 1.0f, 1.0f) },
			//{ matrix3d(0.0f, 1.0f, 0.0f), matrix3d(1.0f, 1.0f, 1.0f), matrix3d(1.0f, 1.0f, 0.0f) },

			//// BOTTOM                                                    
			//{ matrix3d(1.0f, 0.0f, 1.0f), matrix3d(0.0f, 0.0f, 1.0f), matrix3d(0.0f, 0.0f, 0.0f) },
			//{ matrix3d(1.0f, 0.0f, 1.0f), matrix3d(0.0f, 0.0f, 0.0f), matrix3d(1.0f, 0.0f, 0.0f) },
		//};
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
		
		auto callback_method_example = [](const SDL_Event& e)
		{
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
