#include "sdl_manager.h"

#include <SDL.h>
#include <chrono>
#include <sstream>

#include "matrix_helper_3d.h"

namespace application::sdl
{
	constexpr auto NANO_SECONDS_IN_ONE_SECOND{ 1000000000.0F };
	
	sdl_manager::sdl_manager(const int window_width, const int window_height, util::program_state& intial_state):
		program_state_(&intial_state),
		window_width_(window_width),
		window_height_(window_height),
		color_alpha_value_(SDL_ALPHA_OPAQUE)
	{
		x_origin_ = window_width_ / 2.f;
		y_origin_ = window_height_ / 2.f;

		initialize();
	}

	sdl_manager::~sdl_manager()
	{
		window_.reset();
		renderer_.reset();
		
		SDL_Quit();
	}

	auto sdl_manager::window_width() const -> int
	{
		return window_width_;
	}

	auto sdl_manager::window_height() const -> int
	{
		return window_height_;
	}

	auto sdl_manager::x_origin() const -> float
	{
		return x_origin_;
	}

	auto sdl_manager::y_origin() const -> float
	{
		return y_origin_;
	}

	auto sdl_manager::set_draw_color(const uint8_t r, const uint8_t g, const uint8_t b) const -> void
	{
		SDL_SetRenderDrawColor(&(*renderer_), r, g, b, color_alpha_value_);
	}

	auto sdl_manager::set_alpha_value(const uint8_t a) -> void
	{
		color_alpha_value_ = a;
	}
	
	auto sdl_manager::add_mesh(std::shared_ptr<mesh_simple> mesh) -> void
	{
		meshes_.push_back(std::move(mesh));
	}

	auto sdl_manager::add_input_listener(const SDL_Scancode code, input_handler_fn listener_callback) -> bool
	{
		return add_input_listener(std::pair(code, listener_callback));
	}

	auto sdl_manager::add_input_listener(std::pair<SDL_Scancode, input_handler_fn> sdl_code_callback_pair) -> bool
	{
		const auto [_, result] = controls_.insert(sdl_code_callback_pair);

		return result;
	}

	auto sdl_manager::start_loop() -> void
	{
		auto timeOfLastFrame{ std::chrono::high_resolution_clock::now() };
		auto deltaTimeSeconds{ 0.0F };

		while (*program_state_ != util::program_state::stopping)
		{
			draw_background();
			
			handle_input();

			render_meshes();
			
			present_renderer();
			
			// Calculate delta time since last frame
			auto currentTime{ std::chrono::high_resolution_clock::now() };
			auto frameTime{ currentTime - timeOfLastFrame };
			auto frameTimeNs{ std::chrono::duration_cast<std::chrono::nanoseconds>(frameTime) };
			deltaTimeSeconds = frameTimeNs.count() / NANO_SECONDS_IN_ONE_SECOND;
			timeOfLastFrame = currentTime;
		}
	}

	auto sdl_manager::offset_x(float& x) const -> void
	{
		x += x_origin_;
	}

	auto sdl_manager::offset_y(float& y) const -> void
	{
		y += y_origin_;
		y = window_height_ - 1 - y;
	}

	auto sdl_manager::offset_xy(float& x, float& y) const -> void
	{
		offset_x(x);
		offset_y(y);
	}

	auto sdl_manager::initialize() -> void
	{
		std::ostringstream exception_msg_stream;
		
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			exception_msg_stream << "SDL initialization failed. SDL Error: " << SDL_GetError();
			
			throw std::runtime_error(exception_msg_stream.str());
		}

		SDL_Window* window = nullptr;
		SDL_Renderer* renderer = nullptr;
	
		if(SDL_CreateWindowAndRenderer(window_width_, window_height_, 0, &window, &renderer) != 0)
		{
			exception_msg_stream << "Could not create window, SDL Error: " << SDL_GetError();

			throw std::runtime_error(exception_msg_stream.str());
		}

		window_ = std::unique_ptr<SDL_Window, sdl_deleter>(window);
		renderer_ = std::unique_ptr<SDL_Renderer, sdl_deleter>(renderer);
	}

	auto sdl_manager::execute_input_listener(const int scancode_val, const SDL_Event& sdl_event) -> void
	{
		const auto sdl_scancode = static_cast<SDL_Scancode>(scancode_val);
		
		const auto it = controls_.find(sdl_scancode);

		// Not found
		if(it == controls_.end())
		{
			return;
		}

		auto& [_, callback] = *it;

		callback(sdl_event);
	}

	auto sdl_manager::handle_input() -> void
	{
		SDL_Event sdl_event;

		while (SDL_PollEvent(&sdl_event) != 0)
		{
			switch (sdl_event.type)
			{
			case SDL_QUIT:
				*program_state_ = util::program_state::stopping;
				break;
			case SDL_KEYDOWN:
				execute_input_listener(sdl_event.key.keysym.scancode, sdl_event);
				break;
			default:
				break;
			}
		}
	}

	auto sdl_manager::draw_pixel(float x, float y, const uint8_t r, const uint8_t g, const uint8_t b) const -> void
	{
		//offset_xy(x, y);

		set_draw_color(r, g, b);

		SDL_RenderDrawPointF(&(*renderer_), x, y);
	}

	auto sdl_manager::draw_line(float x1, float y1, float x2, float y2, const uint8_t r, const uint8_t g, const uint8_t b) const -> void
	{
		//offset_xy(x1, y1);

		//offset_xy(x2, y2);

		set_draw_color(r, g, b);

		SDL_RenderDrawLineF(&(*renderer_), x1, y1, x2, y2);
	}

	auto sdl_manager::draw_line(float x1, float y1, float x2, float y2) const -> void
	{
		//offset_xy(x1, y1);

		//offset_xy(x2, y2);

		SDL_RenderDrawLineF(&(*renderer_), x1, y1, x2, y2);
	}

	auto sdl_manager::draw_triangle(
		const float x1, const float y1, 
		const float x2, const float y2, 
		const float x3, const float y3) const -> void
	{
		draw_line(x1, y1, x2, y2);
		draw_line(x2, y2, x3, y3);
		draw_line(x3, y3, x1, y1);
	}
	
	auto sdl_manager::draw_background() const -> void
	{
		set_draw_color(0, 0, 0);

		clear_renderer();

		set_draw_color(255, 255, 255);
	}

	auto sdl_manager::clear_renderer() const -> void
	{
		SDL_RenderClear(&(*renderer_));
	}
	
	auto sdl_manager::present_renderer() const -> void
	{
		SDL_RenderPresent(&(*renderer_));
	}

	auto sdl_manager::render_meshes() const -> void
	{
		auto matrix_test = std::make_unique<math::matrix3d>(1, 2, 3);

		for(auto& mesh : meshes_)
		{
			for(auto &[point] : mesh->tris)
			{
				const auto first_point = point[0];
				const auto second_point = point[1];
				const auto third_point = point[2];

				draw_triangle(
					first_point.x(), first_point.y(),
					second_point.x(), second_point.y(),
					third_point.x(), third_point.y());
			}
		}
	}
}
