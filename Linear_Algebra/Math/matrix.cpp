#include "matrix.h"

#include <cassert>
#include <memory>

namespace math
{
	matrix::matrix(const std::size_t rows, const std::size_t columns, const float init)
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

	auto matrix::resize(const std::size_t new_row, const std::size_t new_col) -> void
	{
		rows_ = new_row;
		columns_ = new_col;

		values_.resize(rows_ * columns_);
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

	auto matrix::has_equal_values(const matrix& other) const -> bool
	{
		if(rows_ != other.rows() || columns_ != other.columns())
		{
			return false;
		}

		for(std::size_t row = 0; row < rows_; ++row)
		{
			for(std::size_t column = 0; column < columns_; ++column)
			{
				const auto& this_value = (*this)(row, column);
				const auto& other_value = other(row, column);

				if(this_value != other_value)
				{
					return false;
				}
			}
		}

		return true;
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

	auto matrix::operator*=(const matrix& other) -> matrix&
	{
		assertMultiplicativeRule(other);

		// The new matrix that is created from multiplication has the number of rows of this (current) matrix
		// and the number of columns of the other matrix
		const auto new_matrix = std::make_unique<matrix>(rows_, other.columns());

		// (this) row * (other) column
		for(std::size_t row = 0; row < new_matrix->rows(); ++row)
		{
			for(std::size_t column = 0; column < new_matrix->columns(); ++column)
			{
				auto multiplication_accumulator = 0.f;

				for(std::size_t i = 0; i < columns_; ++i)
				{
					const auto row_val = (*this)(row, i);
					const auto col_val = other(i, column);
					
					multiplication_accumulator += row_val * col_val;
				}

				(*new_matrix)(row, column) = multiplication_accumulator;
			}
		}
		
		*this = *new_matrix;

		return *this;
	}

	auto matrix::assertAdditiveRule(const matrix& other) const -> void
	{
		assert(rows_ == other.rows()  && columns_ == other.columns());
	}

	auto matrix::assertMultiplicativeRule(const matrix& other) const -> void
	{
		assert(columns_ == other.rows());
	}
}
