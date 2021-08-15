#include "space_ship.h"

#include <iostream>

#include "bullet.h"
#include "matrix_helper_3d.h"
#include "target_obj.h"

namespace application
{
	space_ship::space_ship(const std::string& obj_file_location)
		: object(obj_file_location), movement_speed_(1.f), rotation_modifier_(1.5f)
	{
	}

	auto space_ship::get_pitch_matrix(const bool up, const float elapsed_time) const -> std::unique_ptr<math::matrix>
	{
		const float modifier = invert_modifier(up);

		auto rot_matrix = get_axis_rot_matrix(location_, *axis_.x(), modifier);

		return std::move(rot_matrix);
	}

	auto space_ship::get_yaw_matrix(const bool right, const float elapsed_time) const -> std::unique_ptr<math::matrix>
	{
		const float modifier = invert_modifier(right);

		auto rot_matrix = get_axis_rot_matrix(location_, *axis_.y(), modifier);

		return std::move(rot_matrix);
	}

	auto space_ship::get_roll_matrix(const bool right, const float elapsed_time) const -> std::unique_ptr<math::matrix>
	{
		const float modifier = invert_modifier(right);
	
		auto rot_matrix = get_axis_rot_matrix(location_, *axis_.z(), modifier);

		return std::move(rot_matrix);
	}

	auto space_ship::move(const float elapsed_time) -> void
	{
		const auto v_movement = (*axis_.z() * (movement_speed_));

		const auto move_translation = math::get_translation_matrix(v_movement->x(), v_movement->y(), v_movement->z());
		
		const auto new_location = location_.multiply_by_4X4(*move_translation);
		
		location_.set_values(*new_location);

		axis_.move(*move_translation);

		for (auto& [points, _0, _1, _2] : shape_.triangles())
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

	auto space_ship::shoot() -> std::unique_ptr<bullet>
	{
		const auto offset_matrix = get_offset_translation_matrix();

		const auto projectile_location = location_.multiply_by_4X4(*offset_matrix);

		// copy intended
	    auto projectile_axis = axis_;

		projectile_axis.move(*offset_matrix);

		auto projectile = std::make_unique<bullet>(*projectile_location, projectile_axis, movement_speed_, "bullet_rblxV2.obj");

		projectile->set_camera_matrix(camera_matrix_);
		projectile->set_proj_matrix(projection_matrix_);
		projectile->set_xy_center(x_center_, y_center_);

		return std::move(projectile);
	}

    auto space_ship::remove_on_collide(object& other) -> bool
    {
		if(dynamic_cast<const target_obj*>(&other) == nullptr)
		{
			return false;
		}

		return true;
    }

    auto space_ship::get_offset_translation_matrix() -> std::unique_ptr<math::matrix>
    {
        const auto offset = (*axis_.z() * (shape_.max_z() - location_.z()));

	    auto offset_translation_m = math::get_translation_matrix(offset->x(), offset->y(), offset->z());

		return std::move(offset_translation_m);
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
