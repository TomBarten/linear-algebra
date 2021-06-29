#include "matrix.h"

#include <memory>

namespace math
{
	matrix::matrix(const std::size_t rows, const std::size_t columns, float const& init)
		: rows_(rows), columns_(columns), values_(rows_ * columns_, init)
	{
	}

	auto matrix::rows() const noexcept -> std::size_t
	{
		return rows_;
	}

	auto matrix::columns() const noexcept -> std::size_t
	{
		return columns_;
	}

	auto matrix::get(const std::size_t row, const std::size_t col) -> float&
	{
		return values_[row * columns_ + col];
	}

	auto matrix::get(const std::size_t row, const std::size_t col) const -> float const&
	{
		return values_[row * columns_ + col];
	}

	auto matrix::operator()(const std::size_t row, const std::size_t col) -> float&
	{
		return get(row, col);
	}

	auto matrix::operator()(const std::size_t row, const std::size_t col) const -> float const&
	{
		return get(row, col);
	}

	auto matrix::operator*=(const std::size_t scalar) -> matrix&
	{
		for (auto& value : values_)
		{
			value *= scalar;
		}

		return *this;
	}

	auto matrix::operator/=(const std::size_t scalar) -> matrix&
	{
		for (auto& value : values_)
		{
			value /= scalar;
		}

		return *this;
	}

	auto matrix::operator+=(const matrix& other) -> matrix&
	{
		assertAdditiveRule(other);

		for (std::size_t row = 0; row < rows_; ++row)
		{
			for (std::size_t column = 0; column < columns_; ++column)
			{
				(*this)(row, column) += other(row, column);
			}
		}

		return *this;
	}

	auto matrix::operator-=(const matrix& other) -> matrix&
	{
		assertAdditiveRule(other);

		for (std::size_t row = 0; row < rows_; ++row)
		{
			for (std::size_t column = 0; column < columns_; ++column)
			{
				(*this)(row, column) -= other(row, column);
			}
		}

		return *this;
	}

	auto matrix::operator*(const matrix& other) -> matrix&
	{
		assertMultiplicativeRule(other);

	}

	auto matrix::assertAdditiveRule(const matrix& other) const -> void
	{
		assert(other.rows() == rows_ && other.columns() == columns_);
	}

	auto matrix::assertMultiplicativeRule(const matrix& other) const -> void
	{
		assert(columns_ == other.rows());
	}
}
