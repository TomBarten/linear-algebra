#pragma once
#include <memory>

#include "matrix.h"

namespace math
{
	class vector2d
	{
	protected:
		float x_;
		float y_;
		std::unique_ptr<matrix> matrix_;

	public:
		vector2d(float x, float y);

	};
}
