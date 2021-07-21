#include "mesh.h"

namespace application
{
	auto mesh::draw(
		const math::matrix& camera_matrix,
		const math::matrix& projection_matrix,
		const float x_center, 
		const float y_center,
		const std::function<void(float, float, float, float, float, float)> draw_triangle_fn) -> void
	{
		for (auto& [vertices] : triangles_)
		{
			const auto point_1 = vertices[0].multiply_by_4X4(camera_matrix);
			const auto point_2 = vertices[1].multiply_by_4X4(camera_matrix);
			const auto point_3 = vertices[2].multiply_by_4X4(camera_matrix);

			const auto point_1_proj = point_1->get_projection(projection_matrix, x_center, y_center);
			const auto point_2_proj = point_2->get_projection(projection_matrix, x_center, y_center);
			const auto point_3_proj = point_3->get_projection(projection_matrix, x_center, y_center);

			draw_triangle_fn(
				point_1_proj->x(), point_1_proj->y(),
				point_2_proj->x(), point_2_proj->y(),
				point_3_proj->x(), point_3_proj->y());
		}
	}

	auto mesh::triangles() const -> const std::vector<triangle>&
	{
		return triangles_;
	}
	auto mesh::triangles() -> std::vector<triangle>&
	{
		return triangles_;
	}

	auto mesh::min_x() const -> float
	{
		return min_x_;
	}

	auto mesh::max_x() const -> float
	{
		return max_x_;
	}

	auto mesh::min_y() const -> float
	{
		return min_y_;
	}

	auto mesh::max_y() const -> float
	{
		return max_y_;
	}

	auto mesh::min_z() const -> float
	{
		return min_z_;
	}

	auto mesh::max_z() const -> float
	{
		return max_z_;
	}

	auto mesh::update_vertices_min_max() -> void
	{
		min_x_ = std::numeric_limits<float>::max();
		max_x_ = std::numeric_limits<float>::lowest();

		min_y_ = min_x_;
		max_y_ = max_x_;

		min_z_ = min_x_;
		max_z_ = max_x_;

		for (auto& [vertices] : triangles_)
		{
			for(auto& vertex : vertices)
			{
				check_x_min_max(vertex.x());
				check_y_min_max(vertex.y());
				check_z_min_max(vertex.z());
			}
		}
	}

	auto mesh::check_x_min_max(const float val) -> void
	{
		if (val < min_x_)
		{
			min_x_ = val;
		}

		if (val > max_x_)
		{
			max_x_ = val;
		}
	}
	
	auto mesh::check_y_min_max(const float val) -> void
	{
		if (val < min_y_)
		{
			min_y_ = val;
		}

		if (val > max_y_)
		{
			max_y_ = val;
		}
	}

	auto mesh::check_z_min_max(const float val) -> void
	{
		if (val < min_z_)
		{
			min_z_ = val;
		}

		if (val > max_z_)
		{
			max_z_ = val;
		}
	}
}
