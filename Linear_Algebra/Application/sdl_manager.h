#pragma once

#include <memory>

#include "sdl_deleter.h"

namespace application::sdl
{
	class sdl_manager
	{
	private:
		std::unique_ptr<SDL_Window, sdl_deleter> window_;
		std::unique_ptr<SDL_Renderer, sdl_deleter> renderer_;

		int window_width_;
		int window_height_;

		float x_origin_;
		float y_origin_;

	public:
		sdl_manager(int window_width, int window_height);
		~sdl_manager();

		auto window_width() const -> int;
		auto window_height() const -> int;

		auto x_origin() const -> float;
		auto y_origin() const -> float;

		auto set_draw_color(uint8_t r, uint8_t g, uint8_t b) const -> void;
		
		auto draw_pixel(float x, float y, uint8_t r, uint8_t g, uint8_t b) const -> void;
		auto draw_line(float x1, float y1, float x2, float y2, uint8_t r, uint8_t g, uint8_t b) const -> void;
		
	private:
		auto offset_x(float& x) const -> void;
		auto offset_y(float& y) const -> void;
		auto offset_xy(float& x, float& y) const -> void;
		auto initialize() -> void;
	};
}
