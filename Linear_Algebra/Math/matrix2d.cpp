#include "matrix2d.h"

#include <stdexcept>

namespace math
{
	matrix2d::matrix2d(const float x, const float y)
		: dimensional_matrix<matrix2d>(2, 1)
	{
		matrix_(0, 0) = x;
		matrix_(1, 0) = y;
	}

	matrix2d::matrix2d(std::unique_ptr<matrix> matrix_init)
		: dimensional_matrix<matrix2d>(std::move(matrix_init))
	{
		if (matrix_.rows() != 2 || matrix_.columns() != 1)
		{
			throw std::runtime_error("Cannot initialize vector2d with invalid matrix");
		}
	}

	auto matrix2d::scale(const matrix& m_matrix) -> std::unique_ptr<matrix2d>
	{
		// Add 1 extra row so it can be multiplied by M matrix
		// Extra value 1 in new row
		matrix_.resize(3, 1);
		matrix_(2, 0) = 1;

		auto result_matrix = m_matrix * matrix_;

		// Remove extra row, will also remove extra value automatically
		matrix_.resize(2, 1);
		(*result_matrix).resize(2, 1);

		auto result = std::make_unique<matrix2d>(std::move(result_matrix));

		return std::move(result);
	}

	auto matrix2d::x() const -> const float&
	{
		return matrix_(0, 0);
	}

	auto matrix2d::y() const -> const float&
	{
		return matrix_(1, 0);
	}
}
