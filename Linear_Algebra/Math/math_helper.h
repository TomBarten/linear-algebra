#pragma once

#ifndef _USE_MATH_DEFINES
	#define _USE_MATH_DEFINES
#endif

#include <math.h>

namespace math
{
	inline auto degrees_to_radial(const float degrees) -> float
	{
		// (degrees / 360) * (2 * PI)
		return (degrees / 180.f) * M_PI;
	}

	inline auto radial_to_degrees(const float radial) -> float
	{
		// (radial / (2 * PI)) * 360
		return (radial / M_PI) * 180.f;
	}
}
