#include "catch.hpp"
#include "vector2d.h"
#include "vector3d.h"

namespace vector
{
	TEST_CASE("Vector addition should work properly")
	{
		const auto vector2d_x = std::make_unique<math::vector2d>(1.f, 0.f);
		const auto vector2d_y = std::make_unique<math::vector2d>(0.f, 1.f);

		auto vector2d_xy = (*vector2d_x) + (*vector2d_y);

		REQUIRE(vector2d_xy->x() == 1.f);
		REQUIRE(vector2d_xy->y() == 1.f);
	}

	TEST_CASE("Vector assignment addition should work properly")
	{
		const auto vector2d_x = std::make_unique<math::vector2d>(1.f, 0.f);
		const auto vector2d_y = std::make_unique<math::vector2d>(0.f, 1.f);

		(*vector2d_x) += (*vector2d_y);

		REQUIRE(vector2d_x->x() == 1.f);
		REQUIRE(vector2d_y->y() == 1.f);
	}
}
