#pragma once
#include <memory>
#include <string>

#include "matrix.h"

namespace math
{
	class vector2d
	{
	protected:
		std::unique_ptr<matrix> matrix_;
		vector2d();

	public:
		vector2d(float x, float y);
		explicit vector2d(std::unique_ptr<matrix> matrix_init);
		virtual ~vector2d() = default;
		
		operator const matrix&() const;
		virtual auto operator*=(float scalar) -> vector2d&;
		virtual auto operator*(float scalar)->std::unique_ptr<vector2d>;
		virtual auto operator/=(float scalar) -> vector2d&;
		virtual auto operator/(float scalar)->std::unique_ptr<vector2d>;
		virtual auto operator+=(const matrix& other) -> vector2d&;
		virtual auto operator+(const matrix& other) -> std::unique_ptr<vector2d>;
		virtual auto operator-=(const matrix& other) -> vector2d&;
		virtual auto operator-(const matrix& other) -> std::unique_ptr<vector2d>;
		virtual auto operator*=(const matrix& other) -> vector2d&;
		virtual auto operator*(const matrix& other) -> std::unique_ptr<vector2d>;

		auto x() const -> const float&;
		auto y() const -> const float&;

		auto print() const -> std::string;
	
	private:
		auto copy_matrix_values(const std::unique_ptr<matrix>& other) const -> std::unique_ptr<matrix>
		{
			auto matrix_copy = std::make_unique<matrix>(other->rows(), other->columns());
			
			for(std::size_t row = 0; row < other->rows(); ++row)
			{
				for(std::size_t column = 0; column < other->columns(); ++column)
				{
					(*matrix_copy)(row, column) = (*other)(row, column);
				}
			}

			return std::move(matrix_copy);
		}
	};
}
