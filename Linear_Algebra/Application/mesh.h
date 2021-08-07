#pragma once
#include <functional>
#include "triangle.h"

namespace application
{
	class mesh
	{
	private:
		std::vector<triangle> triangles_;

		float min_x_;
		float max_x_;

		float min_y_;
		float max_y_;

		float min_z_;
		float max_z_;

	protected:
		typedef std::function<void(float, float, float, float, float, float, int8_t, int8_t, int8_t)> draw_triangle_fn;
	
	public:
		mesh() = default;
		
		auto draw(
			const math::matrix& matrix_m,
			float x_center,
			float y_center, draw_triangle_fn draw_triangle_fn) -> void;

		auto triangles() const -> const std::vector<triangle>&;

		auto triangles() -> std::vector<triangle>&;
		
		auto min_x() const -> float;
		auto max_x() const -> float;

		auto min_y() const -> float;
		auto max_y() const -> float;

		auto min_z() const -> float;
		auto max_z() const -> float;

		auto update_vertices_min_max() -> void;

	private:
		auto check_x_min_max(float val) -> void;

		auto check_y_min_max(float val) -> void;

		auto check_z_min_max(float val) -> void;
	};
}

