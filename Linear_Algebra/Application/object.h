#pragma once
#include <string>

#include "bounding_box.h"
#include "mesh.h"

namespace application
{
	class object
	{
	protected:
		typedef std::function<void(float, float, float, float, int8_t, int8_t, int8_t)> draw_line_fn;
		typedef std::function<void(float, float, float, float, float, float)> draw_triangle_fn;
		
		mesh shape_;
		bounding_box bounding_box_;
		math::matrix3d location_;
	
	public:
		object();
		explicit object(const std::string& obj_file_location);
		virtual ~object() noexcept = default;

		auto location() const -> const math::matrix3d&;
		
		auto shape() const -> const mesh&;
		auto shape() -> mesh&;
		
		virtual auto tick(
			bool debug, 
			const math::matrix& projection_matrix, 
			float x_center, 
			float y_center,
			draw_triangle_fn draw_triangle,
			draw_line_fn draw_line) -> void;

	protected:
		auto parse_obj_file(const std::string& obj_file_location) -> bool;

		auto calc_bounding_box() -> void;
		auto print_location(const math::matrix& projection_matrix, float x_center, float y_center, draw_line_fn draw_line) -> void;
	};
}


