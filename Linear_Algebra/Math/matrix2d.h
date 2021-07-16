#pragma once
#include "dimensional_matrix.h"

namespace math
{
	class matrix2d final : public base::dimensional_matrix<matrix2d>
	{
	public:
		matrix2d(float x, float y);
		explicit matrix2d(std::unique_ptr<matrix> matrix_init);

		auto scale(const matrix& m_matrix) -> std::unique_ptr<matrix2d>;
		
		auto x() const -> const float&;
		auto y() const -> const float&;
	};
}
