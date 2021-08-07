#pragma once
#include <functional>

#include "matrix3d.h"

namespace application
{
	struct bounding_box final
	{
	private:
		const int8_t r_ = 255;
		const int8_t g_ = 0;
		const int8_t b_ = 255;

		struct connection_data
		{
			math::matrix3d* point;

			std::vector<math::matrix3d*> connected_to;
		};

		std::vector<connection_data> connections_;

	public:
		math::matrix3d vertices[8];

	public:
		bounding_box();
		
		auto draw(
			const math::matrix& matrix_m,
			float x_center,
			float y_center,
			std::function<void(float, float, float, float, int8_t, int8_t, int8_t)> draw_line_fn) -> void;
	};
}

