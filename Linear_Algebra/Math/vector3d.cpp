#include "vector3d.h"

namespace math
{
	vector3d::vector3d(const float x, const float y, const float z)
		: vector2d(x, y)
	{
		matrix_->resize(3, 0);
		
		(*matrix_)(2, 0) = z;
	}

	vector3d::vector3d(std::unique_ptr<matrix> matrix_init)
		: vector2d()
	{
		if(matrix_init->rows() != 3 || matrix_init->columns() != 1)
		{
			throw std::exception("Cannot initialize vector3d with invalid matrix");
		}
		
		matrix_ = std::move(matrix_init);
	}

	auto vector3d::z() const -> const float&
	{
		return (*matrix_)(2, 0);
	}
}
