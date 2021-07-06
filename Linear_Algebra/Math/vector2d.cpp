#include "vector2d.h"

#include <sstream>

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

	auto vector2d::x() const -> const float&
	{
		return (*matrix_)(0, 0);
	}

	auto vector2d::y() const -> const float&
	{
		return (*matrix_)(1, 0);
	}
}
