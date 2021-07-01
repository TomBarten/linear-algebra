#include "vector2d.h"

#include <sstream>

namespace math
{
	vector2d::vector2d()
	{
	}

	vector2d::vector2d(const float x, const float y)
		: matrix_(std::make_unique<matrix>(2, 1))
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

	vector2d::operator const matrix&() const
	{
		return *matrix_;
	}

	auto vector2d::operator*=(const std::size_t scalar) -> vector2d&
	{
		(*matrix_) *= scalar;
		
		return *this;
	}

	auto vector2d::operator*(const std::size_t scalar) -> std::unique_ptr<vector2d>
	{
		auto new_vector = std::make_unique<vector2d>((*matrix_) * scalar);

		return std::move(new_vector);
	}

	auto vector2d::operator/=(const std::size_t scalar) -> vector2d&
	{
		(*matrix_) /= scalar;

		return *this;
	}

	auto vector2d::operator/(const std::size_t scalar) -> std::unique_ptr<vector2d>
	{
		auto new_vector = std::make_unique<vector2d>((*matrix_) / scalar);

		return std::move(new_vector);
	}

	auto vector2d::operator+=(const matrix& other) -> vector2d&
	{
		(*matrix_) += other;

		return *this;
	}

	auto vector2d::operator+(const matrix& other) -> std::unique_ptr<vector2d>
	{
		auto new_vector = std::make_unique<vector2d>((*matrix_) + other);

		return std::move(new_vector);
	}

	auto vector2d::operator-=(const matrix& other) -> vector2d&
	{
		(*matrix_) -= other;

		return *this;
	}		

	auto vector2d::operator-(const matrix& other) -> std::unique_ptr<vector2d>
	{
		auto new_vector = std::make_unique<vector2d>((*matrix_) - other);

		return std::move(new_vector);
	}

	auto vector2d::operator*=(const matrix& other) -> vector2d&
	{
		(*matrix_) *= other;

		return *this;
	}

	auto vector2d::operator*(const matrix& other) -> std::unique_ptr<vector2d>
	{
		auto new_vector = std::make_unique<vector2d>((*matrix_) * other);

		return std::move(new_vector);
	}

	auto vector2d::x() const -> const float&
	{
		return (*matrix_)(0, 0);
	}

	auto vector2d::y() const -> const float&
	{
		return (*matrix_)(1, 0);
	}

	auto vector2d::print() const -> std::string
	{
		return "X: \"" + std::to_string(x()) + "\" Y: \"" + std::to_string(y()) + "\"";
	}
}
