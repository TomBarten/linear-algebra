#include <SDL.h>
#include "sdl_manager.h"

#include <sstream>

namespace application
{
	sdl::sdl_manager::sdl_manager(const int window_width, const int window_height)
		: window_width_(window_width), window_height_(window_height)
	{
		x_origin_ = window_width_ / 2.f;
		y_origin_ = window_height_ / 2.f;

		initialize();
	}

	sdl::sdl_manager::~sdl_manager()
	{
		window_.reset();
		renderer_.reset();
		
		SDL_Quit();
	}

	auto sdl::sdl_manager::window_width() const -> int
	{
		return window_width_;
	}

	auto sdl::sdl_manager::window_height() const -> int
	{
		return window_height_;
	}

	auto sdl::sdl_manager::x_origin() const -> float
	{
		return x_origin_;
	}

	auto sdl::sdl_manager::y_origin() const -> float
	{
		return y_origin_;
	}

	auto sdl::sdl_manager::set_draw_color(const uint8_t r, const uint8_t g, const uint8_t b) const -> void
	{
		SDL_SetRenderDrawColor(&(*renderer_), r, g, b, SDL_ALPHA_OPAQUE);
	}

	auto sdl::sdl_manager::draw_pixel(float x, float y, const uint8_t r, const uint8_t g, const uint8_t b) const -> void
	{
		offset_xy(x, y);
	
		set_draw_color(r, g, b);
	
		SDL_RenderDrawPointF(&(*renderer_), x, y);
	}

	auto sdl::sdl_manager::draw_line(float x1, float y1, float x2, float y2, const uint8_t r, const uint8_t g, const uint8_t b) const -> void
	{
		offset_xy(x1, y1);

		offset_xy(x2, y2);
		
		set_draw_color(r, g, b);

		SDL_RenderDrawLineF(&(*renderer_), x1, y1, x2, y2);
	}

	auto sdl::sdl_manager::offset_x(float& x) const -> void
	{
		x += x_origin_;
	}

	auto sdl::sdl_manager::offset_y(float& y) const -> void
	{
		y += y_origin_;
		y = window_height_ - 1 - y;
	}

	auto sdl::sdl_manager::offset_xy(float& x, float& y) const -> void
	{
		offset_x(x);
		offset_y(y);
	}

	auto sdl::sdl_manager::initialize() -> void
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
}
