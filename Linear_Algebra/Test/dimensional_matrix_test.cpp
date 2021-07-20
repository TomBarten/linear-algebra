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

	TEST_CASE("matrix3d length should work properly [1]")
	{
		const auto vector3d = std::make_unique<math::matrix3d>(4.f, 3.f, 0.f);

		const auto expected_length = 5.f;
		const auto result_length = vector3d->length();

		REQUIRE(expected_length == result_length);
	}

	TEST_CASE("matrix3d length should work properly [2]")
	{
		const auto vector3d = std::make_unique<math::matrix3d>(4.f, 3.f, 7.f);

		const auto expected_length = 8.6f;
		const auto result_length = vector3d->length();

		REQUIRE(result_length == Catch::Approx(expected_length).epsilon(0.01));
	}

	TEST_CASE("matrix3d norm should work properly [1]")
	{
		const auto vector3d = std::make_unique<math::matrix3d>(4.f, 3.f, 0.f);

		const auto expected_output = std::make_unique<math::matrix3d>(0.8f, 0.6f, 0.f);
		
		const auto result = vector3d->norm();

		REQUIRE(result->x() == Catch::Approx(expected_output->x()).epsilon(0.005));
		REQUIRE(result->y() == Catch::Approx(expected_output->y()).epsilon(0.005));
		REQUIRE(result->z() == Catch::Approx(expected_output->z()).epsilon(0.005));
	}

	TEST_CASE("matrix3d norm should work properly [2]")
	{
		const auto vector3d = std::make_unique<math::matrix3d>(4.f, 3.f, 7.f);

		const auto expected_output = std::make_unique<math::matrix3d>(0.464f, 0.348f, 0.813f);

		const auto result = vector3d->norm();

		REQUIRE(result->x() == Catch::Approx(expected_output->x()).epsilon(0.005));
		REQUIRE(result->y() == Catch::Approx(expected_output->y()).epsilon(0.005));
		REQUIRE(result->z() == Catch::Approx(expected_output->z()).epsilon(0.005));
	}
}
