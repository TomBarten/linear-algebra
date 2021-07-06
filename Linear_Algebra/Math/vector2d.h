#pragma once
#include <memory>

#include "vector_base.h"

namespace math
{
	class vector2d : public base::vector_base<vector2d>
	{
	protected:
		vector2d();

	public:
		vector2d(float x, float y);
		explicit vector2d(std::unique_ptr<matrix> matrix_init);
		virtual ~vector2d() = default;
		
		auto x() const -> const float&;
		auto y() const -> const float&;
	
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
