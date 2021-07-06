#pragma once
#include "matrix.h"

namespace math::base
{
	template<typename TVector>
	class vector_base
	{
	protected:
		std::unique_ptr<matrix> matrix_;

	public:
		vector_base()
		{
			matrix_ = nullptr;
		}

		vector_base(std::size_t rows, std::size_t columns)
		{
			matrix_ = std::make_unique<matrix>(rows, columns);
		}
		
		// ReSharper disable once CppNonExplicitConversionOperator
		operator const matrix& () const
		{
			return *matrix_;
		}

		auto operator*=(const float scalar) -> vector_base<TVector>&
		{
			(*matrix_) *= scalar;

			return *this;
		}

		auto operator*(const float scalar) const -> std::unique_ptr<TVector>
		{
			auto new_vector = std::make_unique<TVector>((*matrix_) * scalar);

			return std::move(new_vector);
		}

		auto operator/=(const float scalar) -> vector_base<TVector>&
		{
			(*matrix_) /= scalar;

			return *this;
		}

		auto operator/(const float scalar) const -> std::unique_ptr<TVector>
		{
			auto new_vector = std::make_unique<TVector>((*matrix_) / scalar);

			return std::move(new_vector);
		}

		auto operator+=(const matrix& other) -> vector_base<TVector>&
		{
			(*matrix_) += other;

			return *this;
		}

		auto operator+(const matrix& other) -> std::unique_ptr<TVector>
		{
			auto new_vector = std::make_unique<TVector>((*matrix_) + other);

			return std::move(new_vector);
		}

		auto operator-=(const matrix& other) -> vector_base<TVector>&
		{
			(*matrix_) -= other;

			return *this;
		}

		auto operator-(const matrix& other) const -> std::unique_ptr<TVector>
		{
			auto new_vector = std::make_unique<TVector>((*matrix_) - other);

			return std::move(new_vector);
		}

		auto operator*=(const matrix& other) -> TVector&
		{
			(*matrix_) *= other;

			return *this;
		}

		auto operator*(const matrix& other) const -> std::unique_ptr<TVector>
		{
			auto new_vector = std::make_unique<TVector>((*matrix_) * other);

			return std::move(new_vector);
		}
	};
}
