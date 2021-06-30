#include "catch.hpp"
#include "matrix.h"

TEST_CASE("Matrix rows should return correct rows")
{
    auto n_rows = 5;
	
	auto test_matrix = std::make_unique<math::matrix>(n_rows, 0);

	REQUIRE(test_matrix->rows() == n_rows);
}

TEST_CASE("Matrix columns should return correct columns")
{
	auto n_columns = 2;

	auto test_matrix = std::make_unique<math::matrix>(0, n_columns);

	REQUIRE(test_matrix->columns() == n_columns);
}

TEST_CASE("Matrix values should be at correct coordinates")
{
	const auto n_rows = 5;
	const auto n_columns = 2;

	auto test_matrix = std::make_unique<math::matrix>(n_rows, n_columns);

	float new_values[n_rows][n_columns] = { 0.f };

	for(auto row = 0; row < test_matrix->rows(); ++row)
	{
		for(auto column = 0; column < test_matrix->rows(); ++column)
		{
			const auto new_value = row * column + column + 1.f;
			
			test_matrix->operator()(row, column) = new_value;

			new_values[row][column] = new_value;
		}
	}

	for (auto row = 0; row < test_matrix->rows(); ++row)
	{
		for (auto column = 0; column < test_matrix->rows(); ++column)
		{
			const auto& added_value = new_values[row][column];
			const auto& retrieved_value = test_matrix->operator()(row, column);

			REQUIRE(added_value == retrieved_value);
		}
	}
}
