#include "camera.h"

#include "matrix_helper_3d.h"

namespace application
{
	camera::camera():
		up_(0, 1, 0), eye_(0.f,0.f,5.f), camera_matrix_(std::make_shared<math::matrix>(4, 4))
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
	
	auto camera::look_at(const math::matrix3d& lookat) -> void
	{		
		const auto new_direction = (lookat - eye_)->norm();

		direction_.x() = new_direction->x();
		direction_.y() = new_direction->y();
		direction_.z() = new_direction->z();

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

		auto result = *inverse_image_matrix * *translation_matrix;

		camera_matrix_->set_values(result->get_values());
	}
	
	auto camera::calc_cross_product_normalised(math::matrix3d& member, const math::matrix3d& a, const math::matrix3d& b) const -> void
	{
		const auto cross_product = get_cross_product(a, b);

		auto normalised = cross_product->norm();

		member.x() = normalised->x();
		member.y() = normalised->y();
		member.z() = normalised->z();
	}
}
