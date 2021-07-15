#include "sdl_manager.h"

#include <SDL.h>
#include <chrono>
#include <sstream>

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

	auto sdl_manager::draw_pixel(float x, float y, const uint8_t r, const uint8_t g, const uint8_t b) const -> void
	{
		offset_xy(x, y);
	
		set_draw_color(r, g, b);
	
		SDL_RenderDrawPointF(&(*renderer_), x, y);
	}

	auto sdl_manager::draw_line(float x1, float y1, float x2, float y2, const uint8_t r, const uint8_t g, const uint8_t b) const -> void
	{
		offset_xy(x1, y1);

		offset_xy(x2, y2);
		
		set_draw_color(r, g, b);

		SDL_RenderDrawLineF(&(*renderer_), x1, y1, x2, y2);
	}

	auto sdl_manager::handle_input() -> void
	{
		SDL_Event sdl_event;

		while(SDL_PollEvent(&sdl_event) != 0)
		{
			switch(sdl_event.type)
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

	auto sdl_manager::add_input_listener(const SDL_Scancode code, input_handler_fn listener_callback) -> bool
	{
		const auto [_, result] = controls_.insert(std::pair(code, listener_callback));

		return result;
	}

	auto sdl_manager::start_loop() -> void
	{
		auto timeOfLastFrame{ std::chrono::high_resolution_clock::now() };
		auto deltaTimeSeconds{ 0.0F };

		while (*program_state_ != util::program_state::stopping)
		{
			handle_input();
			
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
		const auto sdl_scancode = reinterpret_cast<SDL_Scancode*>(scancode_val);

		if(sdl_scancode == nullptr)
		{
			throw std::runtime_error("Invalid SDL scancode value: " + std::to_string(scancode_val));
		}
		
		const auto it = controls_.find(*sdl_scancode);

		// Not found
		if(it == controls_.end())
		{
			return;
		}

		auto& [_, callback] = *it;

		callback(sdl_event);
	}
}
