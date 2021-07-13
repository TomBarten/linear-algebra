#include "catch.hpp"
#include "matrix2d.h"
#include "matrix3d.h"

namespace dimensional_matrix
{
	TEST_CASE("matrix2d addition should work properly")
	{
		const auto vector2d_x = std::make_unique<math::matrix2d>(1.f, 0.f);
		const auto vector2d_y = std::make_unique<math::matrix2d>(0.f, 1.f);

		auto vector2d_xy = (*vector2d_x) + (*vector2d_y);

		REQUIRE(vector2d_xy->x() == 1.f);
		REQUIRE(vector2d_xy->y() == 1.f);
	}

	TEST_CASE("matrix2d assignment addition should work properly")
	{
		const auto vector2d_x = std::make_unique<math::matrix2d>(1.f, 0.f);
		const auto vector2d_y = std::make_unique<math::matrix2d>(0.f, 1.f);

		(*vector2d_x) += (*vector2d_y);

		REQUIRE(vector2d_x->x() == 1.f);
		REQUIRE(vector2d_y->y() == 1.f);
	}
}
