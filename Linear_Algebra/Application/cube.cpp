#include "cube.h"

using namespace math;

namespace application
{
	cube::cube()
	{
		auto& triangles = shape_.triangles();
		
		triangles = 
		{
			// SOUTH
			{matrix3d(0.0f, 0.0f, 0.0f), matrix3d(0.0f, 1.0f, 0.0f), matrix3d(1.0f, 1.0f, 0.0f) },
			{ matrix3d(0.0f, 0.0f, 0.0f), matrix3d(1.0f, 1.0f, 0.0f), matrix3d(1.0f, 0.0f, 0.0f) },

			// EAST
			{ matrix3d(1.0f, 0.0f, 0.0f), matrix3d(1.0f, 1.0f, 0.0f), matrix3d(1.0f, 1.0f, 1.0f) },
			{ matrix3d(1.0f, 0.0f, 0.0), matrix3d(1.0f, 1.0f, 1.0), matrix3d(1.0f, 0.0f, 1.0f) },

			// NORTH
			{ matrix3d(1.0f, 0.0f, 1.0), matrix3d(1.0f, 1.0f, 1.0), matrix3d(0.0f, 1.0f, 1.0f) },
			{ matrix3d(1.0f, 0.0f, 1.0), matrix3d(0.0f, 1.0f, 1.0), matrix3d(0.0f, 0.0f, 1.0f) },

			// WEST
			{ matrix3d(0.0f, 0.0f, 1.0), matrix3d(0.0f, 1.0f, 1.0), matrix3d(0.0f, 1.0f, 0.0f) },
			{ matrix3d(0.0f, 0.0f, 1.0), matrix3d(0.0f, 1.0f, 0.0), matrix3d(0.0f, 0.0f, 0.0f) },

			// TOP
			{ matrix3d(0.0f, 1.0f, 0.0), matrix3d(0.0f, 1.0f, 1.0), matrix3d(1.0f, 1.0f, 1.0f) },
			{ matrix3d(0.0f, 1.0f, 0.0), matrix3d(1.0f, 1.0f, 1.0), matrix3d(1.0f, 1.0f, 0.0f) },

			// BOTTOM
			{matrix3d(1.0f, 0.0f, 1.0), matrix3d(0.0f, 0.0f, 1.0), matrix3d(0.0f, 0.0f, 0.0f) },
			{matrix3d(1.0f, 0.0f, 1.0), matrix3d(0.0f, 0.0f, 0.0), matrix3d(1.0f, 0.0f, 0.0f) },
		};
	}
}
