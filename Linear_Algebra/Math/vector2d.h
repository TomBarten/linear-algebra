#pragma once
#include "vector_base.h"

namespace math
{
	class vector2d final : public base::vector_base<vector2d>
	{
	public:
		vector2d(float x, float y);
		explicit vector2d(std::unique_ptr<matrix> matrix_init);

		auto scale(float scale_x, float scale_y) -> void;
		
		auto x() const -> const float&;
		auto y() const -> const float&;
	};
}
