#pragma once
#include "matrix.h"

namespace math
{
	inline auto scaling_matrix_2d(const float scaling_x, const float scaling_y) -> std::unique_ptr<matrix>
	{
		const std::vector<float> scaling_values
		{
			scaling_x, 0,
			0, scaling_y
		};

		return std::move(std::make_unique<matrix>(2, 2, scaling_values));
	}

	inline auto scaling_matrix_3d(const float scaling_x, const float scaling_y, const float scaling_z) -> std::unique_ptr<matrix>
	{
		const std::vector<float> scaling_values
		{
			scaling_x, 0, 0, 0,
			0, scaling_y, 0, 0,
			0, 0, scaling_z, 0,
			0, 0, 0, 1,
		};

		return std::move(std::make_unique<matrix>(4, 4, scaling_values));
	}

	inline auto translation_matrix_2d(const float translate_x, const float translate_y) -> std::unique_ptr<matrix>
	{
		const std::vector<float> translation_values
		{
			1, 0, translate_x,
			0, 1, translate_y,
			0, 0, 1,
		};

		return std::move(std::make_unique<matrix>(3, 3, translation_values));
	}

	inline auto translation_matrix_3d(const float translate_x, const float translate_y, const float translate_z) -> std::unique_ptr<matrix>
	{
		const std::vector<float> translation_values
		{
			1, 0, 0, translate_x,
			0, 1, 0, translate_y,
			0, 0, 1, translate_z,
			0, 0, 0, 1,
		};

		return std::move(std::make_unique<matrix>(4, 4, translation_values));
	}
}
