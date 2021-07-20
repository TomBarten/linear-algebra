#include "catch.hpp"
#include "matrix_helper_3d.h"

namespace matrix3d_helper_test
{
	TEST_CASE("matrix3d helper get_angle should work properly [1]")
	{
		const auto vector_v = std::make_unique<math::matrix3d>(2.f, -1.f, 0.f);

		const auto vector_w = std::make_unique<math::matrix3d>(3.f, 1.f, 4.f);

		const auto expected_output = 64.f;

		const auto result = get_angle_degrees(*vector_v, *vector_w);

		REQUIRE(result == Catch::Approx(expected_output).epsilon(0.005));
	}

	TEST_CASE("matrix3d helper get_angle should work properly [2]")
	{
		const auto vector_v = std::make_unique<math::matrix3d>(2.f, -1.f, -4.f);

		const auto vector_w = std::make_unique<math::matrix3d>(-2.f, 1.f, 4.f);

		const auto expected_output = 180.f;

		const auto result = get_angle_degrees(*vector_v, *vector_w);

		REQUIRE(result == Catch::Approx(expected_output).epsilon(0.005));
	}

	TEST_CASE("matrix3d helper get_angle_degrees should work properly [3]")
	{
		const auto vector_v = std::make_unique<math::matrix3d>(2.f, 0.f, 0.f);

		const auto vector_w = std::make_unique<math::matrix3d>(0.f, 2.f, 0.f);

		const auto expected_output = 90.f;

		const auto result = get_angle_degrees(*vector_v, *vector_w);

		REQUIRE(result == Catch::Approx(expected_output).epsilon(0.005));
	}

	TEST_CASE("matrix3d helper get_cross_product should work properly")
	{
		const auto vector_v = std::make_unique<math::matrix3d>(1.f, 0.f, 0.f);

		const auto vector_w = std::make_unique<math::matrix3d>(0.f, 1.f, 0.f);

		const auto expected_output = std::make_unique<math::matrix3d>(0.f, 0.f, 1.f);

		const auto result = get_cross_product(*vector_v, *vector_w);

		REQUIRE(result->x() == Catch::Approx(expected_output->x()).epsilon(0.005));
		REQUIRE(result->y() == Catch::Approx(expected_output->y()).epsilon(0.005));
		REQUIRE(result->z() == Catch::Approx(expected_output->z()).epsilon(0.005));
	}

	TEST_CASE("matrix3d helper get_cross_product combined with get_angle_degrees")
	{
		const auto vector_v = std::make_unique<math::matrix3d>(5.f, 6.f, 7.f);

		const auto vector_w = std::make_unique<math::matrix3d>(1.f, 2.f, 3.f);

		const auto expected_output_degrees = 90.f;

		const auto cross_product_result = get_cross_product(*vector_v, *vector_w);

		const auto result_degrees_v = get_angle_degrees(*cross_product_result, *vector_v);
		const auto result_degrees_w = get_angle_degrees(*cross_product_result, *vector_w);

		REQUIRE(result_degrees_v == Catch::Approx(expected_output_degrees).epsilon(0.005));
		REQUIRE(result_degrees_w == Catch::Approx(expected_output_degrees).epsilon(0.005));
	}
}
