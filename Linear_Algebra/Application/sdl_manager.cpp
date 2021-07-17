#include "sdl_manager.h"

#include <SDL.h>
#include <chrono>
#include <sstream>

#include "matrix_helper_3d.h"

namespace application::sdl
{
	constexpr auto NANO_SECONDS_IN_ONE_SECOND{ 1000000000.0F };
	
	sdl_manager::sdl_manager
	(
		const int window_width, const int window_height,
		const float fov_y, const float z_near, const float z_far,
		util::program_state& intial_state
	):
		program_state_(&intial_state),
		window_width_(window_width), window_height_(window_height),
		fov_y_(fov_y), z_near_(z_near), z_far_(z_far),
		color_alpha_value_(SDL_ALPHA_OPAQUE)
	{		
		x_center_ = window_width_ * 0.5f;
		y_center_ = window_height_ * 0.5f;

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

	auto sdl_manager::x_center() const -> float
	{
		return x_center_;
	}

	auto sdl_manager::y_center() const -> float
	{
		return y_center_;
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

			render_meshes(deltaTimeSeconds);
			
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
		x += x_center_;
	}

	auto sdl_manager::offset_y(float& y) const -> void
	{
		y += y_center_;
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
		offset_xy(x, y);

		set_draw_color(r, g, b);

		SDL_RenderDrawPointF(&(*renderer_), x, y);
	}

	auto sdl_manager::draw_line(
		const float x1, const float y1, 
		const float x2, const float y2, 
		const uint8_t r, const uint8_t g, const uint8_t b) const -> void
	{
		set_draw_color(r, g, b);

		draw_line(x1, y1, x2, y2);
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

	auto sdl_manager::render_meshes(float elapsed_time) const -> void
	{
		const auto projection_matrix = math::get_projection_matrix(fov_y_, z_near_, z_far_);
		
		for(auto& mesh : meshes_)
		{
			for(auto &[point] : mesh->tris)
			{
				auto point_1 = point[0];
				auto point_2 = point[1];
				auto point_3 = point[2];

				// Add depth
				point_1.z() += 3.0f;
				point_2.z() += 3.0f;
				point_3.z() += 3.0f;
				
				const auto& first_point = point_1.get_projection(*projection_matrix, x_center_, y_center_);
				const auto& second_point = point_2.get_projection(*projection_matrix, x_center_, y_center_);
				const auto& third_point = point_3.get_projection(*projection_matrix, x_center_, y_center_);

				draw_triangle(
					first_point->x(), first_point->y(),
					second_point->x(), second_point->y(),
					third_point->x(), third_point->y());
			}
		}
	}
}
