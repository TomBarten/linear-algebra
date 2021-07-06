#pragma once
#include "matrix.h"

namespace math::helpers
{
	inline auto scaling_matrix_2d(float scaling_x, float scaling_y) -> std::unique_ptr<matrix>
	{
		const std::vector<float> scaling_values{ scaling_x, 0, 0, scaling_y };

		return std::move(std::make_unique<matrix>(2, 2, scaling_values));
	}

	inline auto scaling_matrix_3d(float scaling_x, float scaling_y, float scaling_z) -> std::unique_ptr<matrix>
	{
		
	}

	inline auto translation_matrix_2d(float translate_x, float translate_y, std::size_t dimensions) -> std::unique_ptr<matrix>
	{
		
	}
}
