#pragma once
#include <functional>

#include "matrix3d.h"

namespace application
{
	struct bounding_box
	{
		math::matrix3d vertices[8];

		auto draw(
			const math::matrix& camera_matrix,
			const math::matrix& projection_matrix,
			float x_center,
			float y_center,
			std::function<void(float, float, float, float, int8_t, int8_t, int8_t)> draw_line_fn) const -> void;
	};
}

