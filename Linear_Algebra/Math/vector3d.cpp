#include "vector3d.h"

namespace math
{
	vector3d::vector3d(const float x, const float y, const float z)
		: vector2d(x, y)
	{
		matrix_->resize(3, 0);
		
		(*matrix_)(2, 0) = z;
	}

	auto vector3d::z() const -> const float&
	{
		return (*matrix_)(2, 0);
	}
}
