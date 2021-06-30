#include "catch.hpp"
#include "matrix.h"

namespace matrix
{
	inline auto create_test_matrix(const std::size_t n_rows, const std::size_t n_columns, std::vector<float> values = {}) -> std::unique_ptr<math::matrix>
	{
		auto test_matrix = std::make_unique<math::matrix>(n_rows, n_columns);

		if(values.size() > 0)
		{
			assert(values.size() == n_rows * n_columns);

			for (auto row = 0; row < test_matrix->rows(); ++row)
			{
				for (auto column = 0; column < test_matrix->columns(); ++column)
				{
					const auto new_value = values[row * test_matrix->columns() + column];

					test_matrix->get(row, column) = new_value;
				}
			}
		}
		
		return std::move(test_matrix);
	}
	
	TEST_CASE("Matrix rows should return correct rows")
	{
		auto n_rows = 5;

		auto test_matrix = create_test_matrix(n_rows, 0);

		REQUIRE(test_matrix->rows() == n_rows);
	}

	TEST_CASE("Matrix columns should return correct columns")
	{
		auto n_columns = 2;

		auto test_matrix = create_test_matrix(0, n_columns);

		REQUIRE(test_matrix->columns() == n_columns);
	}

	TEST_CASE("Matrix values should be at correct coordinates")
	{
		const auto n_rows = 5;
		const auto n_columns = 2;

		auto test_matrix = create_test_matrix(n_rows, n_columns);

		float new_values[n_rows][n_columns];

		for (auto row = 0; row < test_matrix->rows(); ++row)
		{
			for (auto column = 0; column < test_matrix->columns(); ++column)
			{
				const auto new_value = row * column + column + row + 1.f;

				new_values[row][column] = new_value;

				test_matrix->get(row, column) = new_value;
			}
		}

		for (auto row = 0; row < test_matrix->rows(); ++row)
		{
			for (auto column = 0; column < test_matrix->columns(); ++column)
			{
				const auto& added_value = new_values[row][column];
				const auto& retrieved_value = test_matrix->get(row, column);

				REQUIRE(added_value == retrieved_value);
			}
		}
	}

	TEST_CASE("Matrix multiplied by scalar should have correct values")
	{
		const auto n_rows = 5;
		const auto n_columns = 3;

		auto values_array[][] =
		{
			{},
			{}
		};

		auto values_vector = std::vector<float>()

		auto test_matrix = create_test_matrix(n_rows, n_columns);

		REQUIRE(test_matrix->columns() == n_columns);
	}
}
