#pragma once

#include <map>
#include <memory>

#include "camera.h"
#include "object.h"
#include "progam_state.h"
#include "sdl_deleter.h"
#include "sdl_input.h"

namespace application::sdl
{
	class sdl_manager
	{
	private:
		typedef std::function<void(float, float, float, float, float, float, int8_t, int8_t, int8_t)> draw_triangle_fn;
		typedef std::function<void(float, float, float, float, int8_t, int8_t, int8_t)> draw_line_fn;

		util::program_state* program_state_;
		std::unique_ptr<SDL_Window, sdl_deleter> window_;
		std::unique_ptr<SDL_Renderer, sdl_deleter> renderer_;
		std::unique_ptr<math::matrix3d> world_matrix_;

		bool debug_;

		int window_width_;
		int window_height_;

		float fov_y_;
		
		float z_near_;
		float z_far_;

		float x_center_;
		float y_center_;

		uint8_t color_alpha_value_;

		camera& camera_;

		std::map<SDL_Scancode, input_handler_fn> controls_;
		std::vector<std::unique_ptr<object>> objects_;
		std::shared_ptr<math::matrix> camera_matrix_;
		std::shared_ptr<math::matrix> proj_matrix_;

	public:
		sdl_manager
		(
			int window_width, int window_height,
			float fov_y, float z_near, float z_far,
			camera& camera,
			bool debug,
			util::program_state& intial_state
		);
		
		~sdl_manager();

		auto window_width() const -> int;
		auto window_height() const -> int;

		auto x_center() const -> float;
		auto y_center() const -> float;

		auto set_draw_color(uint8_t r, uint8_t g, uint8_t b) const -> void;
		auto set_alpha_value(uint8_t a) -> void;
		
		auto add_obj(std::unique_ptr<object> obj) -> void;
		auto add_input_listener(const SDL_Scancode code, input_handler_fn listener_callback) -> bool;
		auto add_input_listener(std::pair<SDL_Scancode, input_handler_fn> sdl_code_callback_pair) -> bool;

		auto start_loop() -> void;
	
	private:
		auto offset_x(float& x) const -> void;
		auto offset_y(float& y) const -> void;
		auto offset_xy(float& x, float& y) const -> void;
		
		auto initialize() -> void;
		auto execute_input_listener(const int scancode_val, const SDL_Event& sdl_event, const float elapsed_time) -> void;
		
		auto handle_input(const float elapsed_time) -> void;

		auto draw_pixel(float x, float y, uint8_t r, uint8_t g, uint8_t b) const -> void;
		auto draw_pixel(float x, float y) const -> void;
		auto draw_line(float x1, float y1, float x2, float y2, uint8_t r, uint8_t g, uint8_t b) const -> void;
		auto draw_line(float x1, float y1, float x2, float y2) const -> void;

		auto draw_triangle(float x1, float y1, float x2, float y2, float x3, float y3, uint8_t r = 255, uint8_t g = 255, uint8_t b = 255) const -> void;
		
		auto draw_background() const -> void;
		
		auto clear_renderer() const -> void;
		auto present_renderer() const -> void;
		auto render_meshes(
			float elapsed_time,
			draw_triangle_fn draw_triangle_function,
			draw_line_fn draw_line_function, bool debug = false) -> void;

		auto check_collision(std::vector<std::unique_ptr<object>>::iterator it) -> bool;
	};
}
