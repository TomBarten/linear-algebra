#pragma once
#include "matrix.h"

namespace math
{	
	inline auto get_scaling_matrix_2d(const float scaling_x, const float scaling_y) -> std::unique_ptr<matrix>
	{
		const std::vector<float> scaling_values
		{
			scaling_x, 0, 0,
			0, scaling_y, 0,
			0, 0, 1,
		};

		return std::move(std::make_unique<matrix>(3, 3, scaling_values));
	}

	inline auto get_translation_matrix_2d(const float translate_x, const float translate_y) -> std::unique_ptr<matrix>
	{
		const std::vector<float> translation_values
		{
			1, 0, translate_x,
			0, 1, translate_y,
			0, 0, 1,
		};

		return std::move(std::make_unique<matrix>(3, 3, translation_values));
	}

	inline auto create_scale_matrix_2d(const float scaling_x, const float scaling_y) -> std::unique_ptr<matrix>
	{
		// T1
		const auto t1_matrix = get_translation_matrix_2d(-scaling_x, -scaling_y);

		// S
		const auto s_matrix = get_scaling_matrix_2d(scaling_x, scaling_y);

		// T2
		const auto t2_matrix = get_translation_matrix_2d(scaling_x, scaling_y);

		// T2 (S * T1)
		auto m_matrix = (*t2_matrix) * (*((*s_matrix) * (*t1_matrix)));

		return std::move(m_matrix);
	}
}
