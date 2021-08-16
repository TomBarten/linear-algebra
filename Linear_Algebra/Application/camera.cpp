#include "camera.h"

#include "matrix_helper_3d.h"

namespace application
{
	camera::camera():
		up_(0, 1, 0), eye_(5.f,5.f,15.f), camera_matrix_(std::make_shared<math::matrix>(4, 4))
	{
	}

	auto camera::get_direction() -> math::matrix3d&
	{
		return direction_;
	}

	auto camera::get_direction() const -> const math::matrix3d&
	{
		return direction_;
	}

	auto camera::position() -> math::matrix3d&
	{
		return eye_;
	}

	auto camera::position() const -> const math::matrix3d&
	{
		return eye_;
	}

	auto camera::get_camera_matrix() const -> std::shared_ptr<math::matrix>
	{
		return camera_matrix_;
	}

	auto camera::move_vertical(const bool up) -> void
	{
		calc_move_direction(up_, up);
	}

    auto camera::move_direction(const bool backward) -> void
    {
		calc_move_direction(direction_, backward);
    }

    auto camera::move_horizontal(const bool right) -> void
    {
		calc_move_direction(right_, right);
    }

    auto camera::yaw(const float degrees) -> void
    {
        const auto rot_matrix = get_axis_rot_matrix(eye_, *up_.normalise(), -degrees);

        const auto new_lookat = math::matrix3d(*rot_matrix * lookat_);

		look_at(new_lookat);
    }

    auto camera::pitch(const float degrees) -> void
    {
		const auto rot_matrix = get_axis_rot_matrix(eye_, *right_.normalise(), -degrees);

		const auto new_lookat = math::matrix3d(*rot_matrix * lookat_);

		look_at(new_lookat);
    }

    auto camera::look_at(const math::matrix3d& lookat) -> void
	{
		lookat_.set_values(lookat);

		const auto new_direction = (lookat_ - eye_)->normalise();

		direction_.set_values(*new_direction);

		calc_cross_product_normalised(right_, up_, direction_);

		calc_cross_product_normalised(up_, direction_, right_);

		update_camera_matrix();
	}

	auto camera::invert_modifier(const bool invert) const -> float
	{
		if(invert)
		{
			return -modifier_;
		}
		
		return modifier_;
	}

	auto camera::update_camera_matrix() -> void
	{
		const std::vector<float> inverse_image_values
		{
			right_.x(), right_.y(), right_.z(), 0,
			up_.x(), up_.y(), up_.z(), 0,
			direction_.x(), direction_.y(), direction_.z(), 0,
			0, 0, 0, 1
		};

		const auto inverse_image_matrix = std::make_unique<math::matrix>(4, 4, inverse_image_values);

		const auto translation_matrix = math::get_translation_matrix(-eye_.x(), -eye_.y(), -eye_.z());

        const auto result = *inverse_image_matrix * *translation_matrix;

		camera_matrix_->set_values(result->get_values());
	}

	auto camera::calc_move_direction(math::matrix3d direction, const bool invert_mod) -> void
	{
		const auto modifier = invert_modifier(invert_mod);

		eye_.x() = (eye_.x() + (direction.x() * modifier));
		eye_.y() = (eye_.y() + (direction.y() * modifier));
		eye_.z() = (eye_.z() + (direction.z() * modifier));

        const auto new_lookat = math::matrix3d(
			(lookat_.x() + (direction.x() * modifier)),
			(lookat_.y() + (direction.y() * modifier)),
			(lookat_.z() + (direction.z() * modifier)));

		look_at(new_lookat);
	}
	
	auto camera::calc_cross_product_normalised(math::matrix3d& member, const math::matrix3d& a, const math::matrix3d& b) const -> void
	{
		const auto cross_product = get_cross_product(a, b);

		auto normalised = cross_product->normalise();

		member.set_values(*normalised);
	}
}
