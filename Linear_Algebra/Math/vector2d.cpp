#include "vector2d.h"

#include "matrix_helpers.h"

namespace math
{
	vector2d::vector2d(const float x, const float y)
		: vector_base<vector2d>(2, 1)
	{
		(*matrix_)(0, 0) = x;
		(*matrix_)(1, 0) = y;
	}

	vector2d::vector2d(std::unique_ptr<matrix> matrix_init)
	{
		if (matrix_init->rows() != 2 || matrix_init->columns() != 1)
		{
			throw std::exception("Cannot initialize vector2d with invalid matrix");
		}

		matrix_ = std::move(matrix_init);
	}

	// TODO left to right multiplication so ( S*V = SV )
	auto vector2d::scale(const float scale_x, const float scale_y) -> void
	{
		const auto s_matrix = scaling_matrix_2d(scale_x, scale_y);

		// Add value 1 on third row
		//(*matrix_).resize(3, 1);
		//(*matrix_)(2, 0) = 1;

		(*this) *= *s_matrix;

		// Remove value 1 on third row (automatically)
		//(*matrix_).resize(2, 1);
	}

	auto vector2d::x() const -> const float&
	{
		return (*matrix_)(0, 0);
	}

	auto vector2d::y() const -> const float&
	{
		return (*matrix_)(1, 0);
	}
}
