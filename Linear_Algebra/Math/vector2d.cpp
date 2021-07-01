#include "vector2d.h"

namespace math
{
	vector2d::vector2d(const float x, const float y)
		: matrix_(std::make_unique<matrix>(2, 1))
	{
		(*matrix_)(0, 0) = x;
		(*matrix_)(1, 0) = y;
	}

	vector2d::operator const matrix&() const
	{
		return *matrix_;
	}

	vector2d::operator matrix&() const
	{
		return *matrix_;
	}

	auto vector2d::operator*=(const std::size_t scalar) -> vector2d&
	{
		(*matrix_) *= scalar;
		
		return *this;
	}

	auto vector2d::operator/=(const std::size_t scalar) -> vector2d&
	{
		(*matrix_) /= scalar;

		return *this;
	}

	auto vector2d::operator+=(const matrix& other) -> vector2d&
	{
		(*matrix_) += other;

		return *this;
	}

	auto vector2d::operator-=(const matrix& other) -> vector2d&
	{
		(*matrix_) -= other;

		return *this;
	}

	auto vector2d::operator*=(const matrix& other) -> vector2d&
	{
		(*matrix_) *= other;

		return *this;
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
