#include "space_ship.h"
#include "matrix_helper_3d.h"

namespace application
{
	space_ship::space_ship(const std::string& obj_file_location)
		: object(obj_file_location), velocity_{0,0,0}, rotation_modifier(200.f)
	{
	}

	auto space_ship::pitch(const bool up, const float elapsed_time) -> void
	{
		const float modifier = invert_modifier(up);

		const auto rot_matrix_x = math::get_rot_matrix_x(modifier * elapsed_time);

		calculate(*rot_matrix_x);
	}

	auto space_ship::yaw(const bool right, const float elapsed_time) -> void
	{
		const float modifier = invert_modifier(right);
		
		const auto rot_matrix_y = math::get_rot_matrix_y(modifier * elapsed_time);

		calculate(*rot_matrix_y);
	}

	auto space_ship::roll(const bool right, const float elapsed_time) -> void
	{
		const float modifier = invert_modifier(right);
		
		const auto rot_matrix_z = math::get_rot_matrix_z(modifier * elapsed_time);

		calculate(*rot_matrix_z);
	}

	auto space_ship::invert_modifier(const bool invert) const -> float
	{
		float modifier;

		if (invert)
		{
			modifier = -rotation_modifier;
		}
		else
		{
			modifier = rotation_modifier;
		}

		return modifier;
	}

	auto space_ship::calculate(const math::matrix& m_matrix) -> void
	{
		for (auto& [points] : shape_.triangles())
		{
			for (auto& matrix : points)
			{
				const auto result = matrix.multiply_by_4X4(m_matrix);

				matrix.x() = result->x();
				matrix.y() = result->y();
				matrix.z() = result->z();
			}
		}

		// update the location
		const auto result = location_.multiply_by_4X4(m_matrix);

		location_.x() = result->x();
		location_.y() = result->y();
		location_.z() = result->z();
	}
}
