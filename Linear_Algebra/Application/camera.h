#pragma once
#include "matrix3d.h"

namespace application
{
	class camera final
	{
	private:
		float modifier_ = 1.5f;
		
		math::matrix3d right_;
		math::matrix3d up_;
		math::matrix3d direction_;
		math::matrix3d lookat_;

		// position
		math::matrix3d eye_;

		std::shared_ptr<math::matrix> camera_matrix_;
	
	public:
		camera();
		
		auto look_at(const math::matrix3d& lookat = math::matrix3d(0, 0, 0)) -> void;
		auto get_direction() -> math::matrix3d&;
		auto get_direction() const -> const math::matrix3d&;
		auto position() -> math::matrix3d&;
		auto position() const -> const math::matrix3d&;

		auto invert_modifier(bool invert) const -> float;

		auto update_camera_matrix() -> void;

		auto get_camera_matrix() const -> std::shared_ptr<math::matrix>;

        auto move_vertical(bool up) -> void;

		auto move_direction(bool backward) -> void;
		auto move_horizontal(bool right) -> void;

	private:
		auto calc_move_direction(math::matrix3d direction, bool invert_mod) -> void;
		auto calc_cross_product_normalised(math::matrix3d& member, const math::matrix3d& a, const math::matrix3d& b) const -> void;
	};
}


