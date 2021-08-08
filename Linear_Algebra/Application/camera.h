#pragma once
#include "matrix3d.h"

namespace application
{
	class camera final
	{
	private:
		float modifier_ = 200.f;
		
		math::matrix3d right_;
		math::matrix3d up_;
		math::matrix3d direction_;

		// position
		math::matrix3d eye_;

		std::shared_ptr<math::matrix> camera_matrix_;
	
	public:
		camera();

		/*auto lookat(const math::matrix3d& point) -> void;*/
		auto look_at(const math::matrix3d& lookat = math::matrix3d(0, 0, 0)) -> void;
		auto get_direction() -> math::matrix3d&;
		auto get_direction() const -> const math::matrix3d&;
		auto position() -> math::matrix3d&;
		auto position() const -> const math::matrix3d&;

		auto invert_modifier(bool invert) const -> float;

		auto update_camera_matrix() -> void;

		auto get_camera_matrix() const -> std::shared_ptr<math::matrix>;

	private:
		auto update_right() -> void;
		auto update_up() -> void;

		auto calc_cross_product_normalised(math::matrix3d& member, const math::matrix3d& a, const math::matrix3d& b) const -> void;
	};
}


