#pragma once
#include "matrix3d.h"

namespace application
{
	class camera final
	{
	private:		
		math::matrix3d right_;
		math::matrix3d up_;
		math::matrix3d direction_;

		// eye
		math::matrix3d position_;
		math::matrix3d lookat_;

		std::shared_ptr<math::matrix> camera_matrix_;
	
	public:
		camera();

		/*auto lookat(const math::matrix3d& point) -> void;*/
		auto point_at(const math::matrix3d& target) -> void;
		auto get_lookat() -> math::matrix3d&;
		auto position() -> math::matrix3d&;
		auto position() const -> const math::matrix3d&;

		auto update_camera_matrix() -> void;

		auto get_camera_matrix() const -> std::shared_ptr<math::matrix>;

	private:
		auto update_right() -> void;
		auto update_up() -> void;

		auto calc_cross_product_normalised(math::matrix3d& member, const math::matrix3d& a, const math::matrix3d& b) const -> void;
	};
}


