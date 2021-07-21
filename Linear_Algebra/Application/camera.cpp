#include "camera.h"

#include "matrix_helper_3d.h"

namespace application
{
	camera::camera():
		up_(0, 1, 0), position_(0.f,0.f,50.f), camera_matrix_(std::make_shared<math::matrix>(4, 4))
	{
	}

	auto camera::point_at(const math::matrix3d& target) -> void
	{
		const auto new_direction = (target - position_)->norm();

		direction_.x() = new_direction->x();
		direction_.y() = new_direction->y();
		direction_.z() = new_direction->z();

		const auto a = (*new_direction) * get_dot_product(up_, *new_direction);
		
		const auto new_up = (up_ - *a)->norm();

		const auto new_right = get_cross_product(*new_up, *new_direction);

		up_.x() = new_up->x();
		up_.y() = new_up->y();
		up_.z() = new_up->z();

		right_.x() = new_right->x();
		right_.y() = new_right->y();
		right_.z() = new_right->z();
	}

	//auto camera::lookat(const math::matrix3d& point) -> void
	//{
	//	lookat_.x() = point.x();
	//	lookat_.y() = point.y();
	//	lookat_.z() = point.z();

	//	const auto direction = (eye_ - lookat_)->norm();
	//	
	//	direction_.x() = direction->x();
	//	direction_.y() = direction->y();
	//	direction_.z() = direction->z();

	//	update_right();
	//	update_up();
	//	
	//}

	auto camera::get_lookat() -> math::matrix3d&
	{
		return lookat_;
	}

	auto camera::position() -> math::matrix3d&
	{
		return position_;
	}

	auto camera::position() const -> const math::matrix3d&
	{
		return position_;
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

		const auto translation_matrix = math::get_translation_matrix(-position_.x(), -position_.y(), -position_.z());

		auto result = *inverse_image_matrix * *translation_matrix;

		camera_matrix_->set_values(result->get_values());
	}

	auto camera::get_camera_matrix() const -> std::shared_ptr<math::matrix>
	{
		return camera_matrix_;
	}

	auto camera::update_right() -> void
	{
		calc_cross_product_normalised(right_, up_, direction_);
	}

	auto camera::update_up() -> void
	{
		calc_cross_product_normalised(up_, direction_, right_);
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
