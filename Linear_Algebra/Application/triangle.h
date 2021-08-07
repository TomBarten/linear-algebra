#pragma once
#include "matrix3d.h"

namespace application
{
	struct triangle
	{
		math::matrix3d vertices[3];

		uint8_t r = 255;
		uint8_t g = 255;
		uint32_t b = 255;
	};
}

