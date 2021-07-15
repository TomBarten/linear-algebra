#pragma once
#include <vector>

#include "triangle.h"

namespace application::shape
{
	struct mesh
	{
		std::vector<triangle> tris;
	};
}
