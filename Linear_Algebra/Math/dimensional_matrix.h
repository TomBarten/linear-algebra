#pragma once
#include "matrix.h"

namespace math::base
{
	template<typename TMatrix>
	class dimensional_matrix
	{
	protected:
		std::unique_ptr<matrix> matrix_;

	public:
		dimensional_matrix()
		{
			matrix_ = nullptr;
		}

		dimensional_matrix(std::size_t rows, std::size_t columns)
		{
			matrix_ = std::make_unique<matrix>(rows, columns);
		}
	
		// ReSharper disable once CppNonExplicitConversionOperator
		operator const matrix& () const
		{
			return *matrix_;
		}

		auto operator*=(const float scalar) -> dimensional_matrix<TMatrix>&
		{
			(*matrix_) *= scalar;

			return *this;
		}

		auto operator*(const float scalar) const -> std::unique_ptr<TMatrix>
		{
			auto new_matrix = std::make_unique<TMatrix>(std::move((*matrix_) * scalar));

			return std::move(new_matrix);
		}

		auto operator/=(const float scalar) -> dimensional_matrix<TMatrix>&
		{ 
			(*matrix_) /= scalar;

			return *this;
		}

		auto operator/(const float scalar) const -> std::unique_ptr<TMatrix>
		{
			auto new_matrix = std::make_unique<TMatrix>(std::move((*matrix_) / scalar));

			return std::move(new_matrix);
		}

		auto operator+=(const matrix& other) -> dimensional_matrix<TMatrix>&
		{
			(*matrix_) += other;

			return *this;
		}

		auto operator+(const matrix& other) -> std::unique_ptr<TMatrix>
		{
			auto new_matrix = std::make_unique<TMatrix>(std::move((*matrix_) + other));

			return std::move(new_matrix);
		}

		auto operator-=(const matrix& other) -> dimensional_matrix<TMatrix>&
		{
			(*matrix_) -= other;

			return *this;
		}

		auto operator-(const matrix& other) const -> std::unique_ptr<TMatrix>
		{
			auto new_matrix = std::make_unique<TMatrix>(std::move((*matrix_) - other));

			return std::move(new_matrix);
		}

		auto operator*=(const matrix& other) -> dimensional_matrix<TMatrix>&
		{
			(*matrix_) *= other;

			return *this;
		}

		auto operator*(const matrix& other) const -> std::unique_ptr<TMatrix>
		{
			auto new_matrix = std::make_unique<TMatrix>(std::move((*matrix_) * other));

			return std::move(new_matrix);
		}

	protected:
		auto copy_matrix_values(const std::unique_ptr<matrix>& other) const -> std::unique_ptr<matrix>
		{
			auto matrix_copy = std::make_unique<matrix>(other->rows(), other->columns());

			for (std::size_t row = 0; row < other->rows(); ++row)
			{
				for (std::size_t column = 0; column < other->columns(); ++column)
				{
					(*matrix_copy)(row, column) = (*other)(row, column);
				}
			}

			return std::move(matrix_copy);
		}
	};
}
