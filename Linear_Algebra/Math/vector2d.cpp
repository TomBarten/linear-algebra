#include "vector2d.h"

namespace math
{
	vector2d::vector2d(const float x, const float y)
		: x_(x), y_(y), matrix_(std::make_unique<matrix>(2, 1))
	{
		(*matrix_)(0, 0) = x_;
		(*matrix_)(1, 0) = y_;
	}
}
