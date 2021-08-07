#include <memory>

#include "matrix.h"

#include <sstream>
#include <stdexcept>
#include <string>

namespace math
{
	matrix::matrix()
		: rows_(0), columns_(0), values_(0)
	{
	}

	matrix::matrix(const std::size_t rows, const std::size_t columns, const float init)
		: rows_(rows), columns_(columns), values_(rows_ * columns_, init)
	{
	}

	matrix::matrix(const std::size_t rows, const std::size_t columns, const std::vector<float>& values)
		: matrix(rows, columns)
	{
		set_values(values);
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

	auto matrix::set_values(const std::vector<float>& values) -> void
	{
		if(values.size() != rows_ * columns_)
		{
			throw std::runtime_error("Unable to set values; invalid new values size");
		}
		
		for (auto row = 0; row < rows_; ++row)
		{
			for (auto column = 0; column < columns_; ++column)
			{
				const auto new_value = values[row * columns_ + column];

				(*this)(row, column) = new_value;
			}
		}
	}

	auto matrix::get_values() const -> std::vector<float>
	{
		return values_;
	}

	auto matrix::get_values() -> std::vector<float>&
	{
		return values_;
	}

	auto matrix::operator-() const -> std::unique_ptr<matrix>
	{
		auto negated_matrix = this->operator*(-1);

		return std::move(negated_matrix);
	}

	auto matrix::operator()(const std::size_t row, const std::size_t col) -> float&
	{
		return get(row, col);
	}

	auto matrix::operator()(const std::size_t row, const std::size_t col) const -> float const&
	{
		return get(row, col);
	}

	auto matrix::operator*=(const float scalar) -> matrix&
	{
		for (auto& value : values_)
		{
			value *= scalar;
		}

		return *this;
	}

	auto matrix::operator*(const float scalar) const -> std::unique_ptr<matrix>
	{
		auto new_matrix = std::make_unique<matrix>(rows_, columns_);

		for (std::size_t row = 0; row < rows_; ++row)
		{
			for (std::size_t column = 0; column < columns_; ++column)
			{
				(*new_matrix)(row, column) = (*this)(row, column) * scalar;
			}
		}

		return std::move(new_matrix);
	}

	auto matrix::operator/=(const float scalar) -> matrix&
	{
		for (auto& value : values_)
		{
			value /= scalar;
		}

		return *this;
	}

	auto matrix::operator/(const float scalar) const -> std::unique_ptr<matrix>
	{
		auto new_matrix = std::make_unique<matrix>(rows_, columns_);

		for (std::size_t row = 0; row < rows_; ++row)
		{
			for (std::size_t column = 0; column < columns_; ++column)
			{
				(*new_matrix)(row, column) = (*this)(row, column) / scalar;
			}
		}

		return std::move(new_matrix);
	}

	auto matrix::operator+=(const matrix& other) -> matrix&
	{
		checkAdditiveRule(other);

		for (std::size_t row = 0; row < rows_; ++row)
		{
			for (std::size_t column = 0; column < columns_; ++column)
			{
				(*this)(row, column) += other(row, column);
			}
		}

		return *this;
	}

	auto matrix::operator+(const matrix& other) const -> std::unique_ptr<matrix>
	{
		checkAdditiveRule(other);

		auto new_matrix = std::make_unique<matrix>(rows_, columns_);

		for (std::size_t row = 0; row < rows_; ++row)
		{
			for (std::size_t column = 0; column < columns_; ++column)
			{
				(*new_matrix)(row, column) = (*this)(row, column) + other(row, column);
			}
		}

		return std::move(new_matrix);
	}

	auto matrix::operator-=(const matrix& other) -> matrix&
	{
		checkAdditiveRule(other);

		for (std::size_t row = 0; row < rows_; ++row)
		{
			for (std::size_t column = 0; column < columns_; ++column)
			{
				(*this)(row, column) -= other(row, column);
			}
		}

		return *this;
	}

	auto matrix::operator-(const matrix& other) const -> std::unique_ptr<matrix>
	{
		checkAdditiveRule(other);

		auto new_matrix = std::make_unique<matrix>(rows_, columns_);

		for (std::size_t row = 0; row < rows_; ++row)
		{
			for (std::size_t column = 0; column < columns_; ++column)
			{
				const auto& this_val = (*this)(row, column);
				const auto& other_val = other(row, column);
				
				(*new_matrix)(row, column) = this_val - other_val;
			}
		}

		return std::move(new_matrix);
	}

	auto matrix::operator*=(const matrix& other) -> matrix&
	{
		const auto new_matrix = get_matrix_multiplication_result(other);

		*this = *new_matrix;

		return *this;
	}

	auto matrix::operator*(const matrix& other) const -> std::unique_ptr<matrix>
	{
		return std::move(get_matrix_multiplication_result(other));
	}

	auto matrix::to_string() const -> std::string
	{
		std::stringstream ss;
		
		for (std::size_t row = 0; row < rows_; ++row)
		{
			for (std::size_t column = 0; column < columns_; ++column)
			{
				const auto this_value = (*this)(row, column);

				ss << this_value << " ";
			}

			ss << std::endl;
		}

		return ss.str();
	}

	auto matrix::checkAdditiveRule(const matrix& other) const -> void
	{
		if(rows_ != other.rows() || columns_ != other.columns())
		{
			throw std::runtime_error("Additive rule violated");
		}
	}

	auto matrix::checkMultiplicativeRule(const matrix& other) const -> void
	{
		if(columns_ != other.rows())
		{
			throw std::runtime_error("Multiplicative rule violated");
		}
	}

	auto matrix::has_equal_values(const matrix& other) const -> bool
	{
		if (rows_ != other.rows() || columns_ != other.columns())
		{
			return false;
		}

		for (std::size_t row = 0; row < rows_; ++row)
		{
			for (std::size_t column = 0; column < columns_; ++column)
			{
				const auto& this_value = (*this)(row, column);
				const auto& other_value = other(row, column);

				if (this_value != other_value)
				{
					return false;
				}
			}
		}

		return true;
	}

	auto matrix::get_matrix_multiplication_result(const matrix& other) const -> std::unique_ptr<matrix>
	{
		checkMultiplicativeRule(other);
		
		// The new matrix that is created from multiplication has the number of rows of this (current) matrix
		// and the number of columns of the other matrix
		auto new_matrix = std::make_unique<matrix>(rows_, other.columns());
		
		// (this) row * (other) column
		for (std::size_t row = 0; row < new_matrix->rows(); ++row)
		{
			for (std::size_t column = 0; column < new_matrix->columns(); ++column)
			{
				auto multiplication_accumulator = 0.f;

				for (std::size_t i = 0; i < columns_; ++i)
				{
					const auto& row_val = (*this)(row, i);
					const auto& col_val = other(i, column);

					multiplication_accumulator += row_val * col_val;
				}

				(*new_matrix)(row, column) = multiplication_accumulator;
			}
		}

		return std::move(new_matrix);
	}
}
