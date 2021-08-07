#include "space_ship.h"

#include <iostream>

#include "matrix_helper_3d.h"

namespace application
{
	space_ship::space_ship(const std::string& obj_file_location)
		: object(obj_file_location), movement_speed_(150.f), rotation_modifier_(400.f)
	{
	}

	auto space_ship::get_pitch_matrix(const bool up, const float elapsed_time) const -> std::unique_ptr<math::matrix>
	{
		const float modifier = invert_modifier(up);

		auto rot_matrix = get_axis_rot_matrix(location_, *axis_.x(), modifier * elapsed_time);

		return std::move(rot_matrix);
	}

	auto space_ship::get_yaw_matrix(const bool right, const float elapsed_time) const -> std::unique_ptr<math::matrix>
	{
		const float modifier = invert_modifier(right);

		auto rot_matrix = get_axis_rot_matrix(location_, *axis_.y(), modifier * elapsed_time);

		const auto test = rot_matrix->to_string();

		return std::move(rot_matrix);
	}

	auto space_ship::get_roll_matrix(const bool right, const float elapsed_time) const -> std::unique_ptr<math::matrix>
	{
		const float modifier = invert_modifier(right);
	
		auto rot_matrix = get_axis_rot_matrix(location_, *axis_.z(), modifier * elapsed_time);

		return std::move(rot_matrix);
	}

	auto space_ship::move(const float elapsed_time) -> void
	{
		const auto v_movement = (*axis_.z() * (elapsed_time * movement_speed_));

		const auto move_translation = math::get_translation_matrix(v_movement->x(), v_movement->y(), v_movement->z());
		
		const auto new_location = location_.multiply_by_4X4(*move_translation);
		
		location_.set_values(*new_location);

		axis_.move(*move_translation);

		for (auto& [points, _1, _2, _3] : shape_.triangles())
		{
			for (auto& matrix : points)
			{
				const auto result = matrix.multiply_by_4X4(*move_translation);

				matrix.set_values(*result);
			}
		}
	}

	auto space_ship::calculate_rotation(const math::matrix& m_matrix) -> void
	{
		axis_.rotate(m_matrix);

		for (auto& [points, _1, _2, _3] : shape_.triangles())
		{
			for (auto& matrix : points)
			{
				const auto result = matrix.multiply_by_4X4(m_matrix);

				matrix.set_values(*result);
			}
		}
	}

	auto space_ship::invert_modifier(const bool invert) const -> float
	{
		if (invert)
		{
			return -rotation_modifier_;
		}

		return rotation_modifier_;
	}

	auto space_ship::print_location(math::matrix& matrix_m) -> void
	{
		std::cout << "space_ship: ";
		object::print_location(matrix_m);
	}
}
