#pragma once
#include "matrix3d.h"

namespace application::shape
{
	struct triangle
	{
		std::unique_ptr<math::matrix3d> p[3];
	};
}


