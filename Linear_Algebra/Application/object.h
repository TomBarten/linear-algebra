#pragma once
#include <string>

#include "axis.h"
#include "bounding_box.h"
#include "mesh.h"

namespace application
{
	class object
	{
	protected:
		typedef std::function<void(float, float, float, float, int8_t, int8_t, int8_t)> draw_line_fn;
		typedef std::function<void(float, float, float, float, float, float, int8_t, int8_t, int8_t)> draw_triangle_fn;
		
		mesh shape_;
		bounding_box bounding_box_;
		math::matrix3d location_;
		axis axis_;

		float x_center_;
		float y_center_;

		std::shared_ptr<math::matrix> projection_matrix_;
		std::shared_ptr<math::matrix> camera_matrix_;
	
	public:
		object();
		explicit object(const std::string& obj_file_location);
		virtual ~object() noexcept = default;

		auto location() const -> const math::matrix3d&;
		
		virtual auto shape() const -> const mesh&;
		virtual auto shape() -> mesh&;

		auto set_xy_center(float x_center, float y_center) -> void;
		auto set_proj_matrix(std::shared_ptr<math::matrix> projection_matrix) -> void;
		auto set_camera_matrix(std::shared_ptr<math::matrix> camera_matrix) -> void;

		auto is_valid() const -> bool;

		auto has_collision(const object& other) const -> bool;
		
		virtual auto tick(
			float elapsed_time,
			bool debug,
			draw_triangle_fn draw_triangle, draw_line_fn draw_line) -> void;

		virtual auto remove_on_collide(const object& other) -> bool = 0;

	protected:
		auto parse_obj_file(const std::string& obj_file_location) -> bool;

		auto calc_bounding_box(mesh& shape) -> void;
		virtual auto print_location(math::matrix& matrix_m) -> void;
	};
}


