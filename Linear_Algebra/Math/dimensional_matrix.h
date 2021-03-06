#pragma once
#include <stdexcept>

#include "matrix.h"

namespace math::base
{
	template<typename TMatrix>
	class dimensional_matrix
	{
	protected:
		matrix matrix_;

	public:
		dimensional_matrix()
		{
			matrix_ = matrix(0, 0);
		}

		dimensional_matrix(const std::size_t rows, const std::size_t columns)
		{
			matrix_ = matrix(rows, columns);
		}

		explicit dimensional_matrix(const std::unique_ptr<matrix> matrix_init)
		{
			matrix_ = copy_matrix_values(*matrix_init);
		}

		auto to_string() const -> std::string
		{
			return matrix_.to_string();
		}

		auto set_values(const matrix& other)
		{
			if(matrix_.rows() != other.rows() || matrix_.columns() != other.columns())
			{
				throw std::runtime_error("Rows and/or columns are not equal, cannot set values");
			}
			
			for (std::size_t row = 0; row < matrix_.rows(); ++row)
			{
				for (std::size_t column = 0; column < matrix_.columns(); ++column)
				{
					matrix_(row, column) = other(row, column);
				}
			}
		}

		// ReSharper disable once CppNonExplicitConversionOperator
		operator const matrix& () const
		{
			return matrix_;
		}

		auto operator-() const -> std::unique_ptr<TMatrix>
		{
			auto new_negated_matrix = matrix_ * -1;

			return std::move(new_negated_matrix);
		}
		
		auto operator*=(const float scalar) -> dimensional_matrix<TMatrix>&
		{
			matrix_ *= scalar;

			return *this;
		}

		auto operator*(const float scalar) const -> std::unique_ptr<TMatrix>
		{
			auto new_matrix = std::make_unique<TMatrix>(std::move((matrix_) * scalar));

			return std::move(new_matrix);
		}

		auto operator/=(const float scalar) -> dimensional_matrix<TMatrix>&
		{ 
			matrix_ /= scalar;

			return *this;
		}

		auto operator/(const float scalar) const -> std::unique_ptr<TMatrix>
		{
			auto new_matrix = std::make_unique<TMatrix>(std::move((matrix_) / scalar));

			return std::move(new_matrix);
		}

		auto operator+=(const matrix& other) -> dimensional_matrix<TMatrix>&
		{
			matrix_ += other;

			return *this;
		}

		auto operator+(const matrix& other) -> std::unique_ptr<TMatrix>
		{
			auto new_matrix = std::make_unique<TMatrix>(std::move(matrix_ + other));

			return std::move(new_matrix);
		}

		auto operator-=(const matrix& other) -> dimensional_matrix<TMatrix>&
		{
			matrix_ -= other;

			return *this;
		}

		auto operator-(const matrix& other) const -> std::unique_ptr<TMatrix>
		{
			auto new_matrix = std::make_unique<TMatrix>(std::move(matrix_ - other));

			return std::move(new_matrix);
		}

		auto operator*=(const matrix& other) -> dimensional_matrix<TMatrix>&
		{
			matrix_ *= other;

			return *this;
		}

		auto operator*(const matrix& other) const -> std::unique_ptr<TMatrix>
		{
			auto new_matrix = std::make_unique<TMatrix>(std::move(matrix_ * other));

			return std::move(new_matrix);
		}

	protected:
		static auto copy_matrix_values(const matrix& original) -> matrix
		{
			auto matrix_copy = matrix(original.rows(), original.columns());
			
			for (std::size_t row = 0; row < original.rows(); ++row)
			{
				for (std::size_t column = 0; column < original.columns(); ++column)
				{
					matrix_copy(row, column) = original(row, column);
				}
			}

			return matrix_copy;
		}
		
		auto copy_matrix_values(const std::unique_ptr<matrix>& original) const -> std::unique_ptr<matrix>
		{
			auto& matrix_copy = copy_matrix_values(*original);
			
			auto matrix_copy_managed = std::make_unique<matrix>(std::move(matrix_copy));

			return std::move(matrix_copy_managed);
		}
	};
}
