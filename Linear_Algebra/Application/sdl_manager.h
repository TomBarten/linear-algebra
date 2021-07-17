#pragma once

#include <map>
#include <memory>

#include "matrix2d.h"
#include "mesh_simple.h"
#include "progam_state.h"
#include "sdl_deleter.h"
#include "sdl_input.h"

namespace application::sdl
{
	class sdl_manager
	{
	private:
		util::program_state* program_state_;
		std::unique_ptr<SDL_Window, sdl_deleter> window_;
		std::unique_ptr<SDL_Renderer, sdl_deleter> renderer_;

		int window_width_;
		int window_height_;

		float fov_y_;
		
		float z_near_;
		float z_far_;

		float x_center_;
		float y_center_;

		uint8_t color_alpha_value_;

		std::map<SDL_Scancode, input_handler_fn> controls_;
		std::vector<std::shared_ptr<mesh_simple>> meshes_;

	public:
		sdl_manager
		(
			int window_width, int window_height,
			float fov_y, float z_near, float z_far,
			util::program_state& intial_state
		);
		
		~sdl_manager();

		auto window_width() const -> int;
		auto window_height() const -> int;

		auto x_center() const -> float;
		auto y_center() const -> float;

		auto set_draw_color(uint8_t r, uint8_t g, uint8_t b) const -> void;
		auto set_alpha_value(uint8_t a) -> void;
		
		auto add_mesh(std::shared_ptr<mesh_simple> mesh) -> void;
		auto add_input_listener(SDL_Scancode code, input_handler_fn listener_callback) -> bool;
		auto add_input_listener(std::pair<SDL_Scancode, input_handler_fn> sdl_code_callback_pair) -> bool;

		auto start_loop() -> void;
	
	private:
		auto offset_x(float& x) const -> void;
		auto offset_y(float& y) const -> void;
		auto offset_xy(float& x, float& y) const -> void;
		
		auto initialize() -> void;
		auto execute_input_listener(int scancode_val, const SDL_Event& sdl_event) -> void;
		
		auto handle_input() -> void;

		auto draw_pixel(float x, float y, uint8_t r, uint8_t g, uint8_t b) const -> void;
		auto draw_line(float x1, float y1, float x2, float y2, uint8_t r, uint8_t g, uint8_t b) const -> void;
		auto draw_line(float x1, float y1, float x2, float y2) const -> void;

		auto draw_triangle(float x1, float y1, float x2, float y2, float x3, float y3) const -> void;
		
		auto draw_background() const -> void;
		
		auto clear_renderer() const -> void;
		auto present_renderer() const -> void;
		auto render_meshes(float elapsed_time) const -> void;
	};
}
