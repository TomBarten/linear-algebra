#include "vector3d.h"

namespace math
{
	vector3d::vector3d(const float x, const float y, const float z)
		: vector2d(x, y), z_(z)
	{
		matrix_ = std::make_unique<matrix>(3, 1);

		(*matrix_)(0, 0) = x_;
		(*matrix_)(1, 0) = y_;
		(*matrix_)(2, 0) = z_;
	}
}
