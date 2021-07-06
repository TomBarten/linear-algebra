#include "catch.hpp"
#include "matrix.h"

namespace matrix
{
	inline auto create_test_matrix(const std::size_t n_rows, const std::size_t n_columns, const std::vector<float> values = {}) -> std::unique_ptr<math::matrix>
	{
		std::unique_ptr<math::matrix> test_matrix;

		if(values.size() > 0)
		{
			test_matrix = std::make_unique<math::matrix>(n_rows, n_columns, values);
		}
		else
		{
			test_matrix = std::make_unique<math::matrix>(n_rows, n_columns);
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
		const auto n_rows = 2;
		const auto n_columns = 3;
		const auto multiplicator = 5;

		const std::vector<float> values_vector{ 1,2,3,4,5,6 };

		auto test_matrix = create_test_matrix(n_rows, n_columns, values_vector);

		*test_matrix *= multiplicator;

		for (std::size_t row = 0; row < test_matrix->rows(); ++row)
		{
			for (std::size_t column = 0; column < test_matrix->columns(); ++column)
			{
				const auto& value = values_vector[row * test_matrix->columns() + column];
				const auto& multiplied_value = test_matrix->get(row, column);

				REQUIRE((value * multiplicator) == multiplied_value);
			}
		}
	}

	TEST_CASE("Matrix divided by scalar should have correct values")
	{
		const auto n_rows = 2;
		const auto n_columns = 3;
		const auto divisor = 5;

		const std::vector<float> values_vector{ 1,2,3,4,5,6 };

		auto test_matrix = create_test_matrix(n_rows, n_columns, values_vector);

		*test_matrix /= divisor;

		for (std::size_t row = 0; row < test_matrix->rows(); ++row)
		{
			for (std::size_t column = 0; column < test_matrix->columns(); ++column)
			{
				const auto& value = values_vector[row * test_matrix->columns() + column];
				const auto& divided_value = test_matrix->get(row, column);

				REQUIRE((value / divisor) == divided_value);
			}
		}
	}

	TEST_CASE("Matrix added by another matrix should have correct values")
	{
		const auto n_rows = 2;
		const auto n_columns = 3;

		const std::vector<float> values_vector{ 1,2,3,4,5,6 };

		const auto test_matrix_1 = create_test_matrix(n_rows, n_columns, values_vector);
		const auto test_matrix_2 = create_test_matrix(n_rows, n_columns, values_vector);

		*test_matrix_1 += *test_matrix_2;

		for (std::size_t row = 0; row < test_matrix_1->rows(); ++row)
		{
			for (std::size_t column = 0; column < test_matrix_1->columns(); ++column)
			{
				const auto& addition_value = test_matrix_2->get(row, column);
				const auto& result_value = test_matrix_1->get(row, column);

				// This check only works if both matrix's have the same initial values
				REQUIRE((result_value - addition_value) == addition_value);
			}
		}
	}

	TEST_CASE("Matrix subracted by another matrix should have correct values")
	{
		const auto n_rows = 2;
		const auto n_columns = 3;

		const std::vector<float> values_vector{ 1,2,3,4,5,6 };

		const auto test_matrix_1 = create_test_matrix(n_rows, n_columns, values_vector);
		const auto test_matrix_2 = create_test_matrix(n_rows, n_columns, values_vector);

		*test_matrix_1 -= *test_matrix_2;

		for (std::size_t row = 0; row < test_matrix_1->rows(); ++row)
		{
			for (std::size_t column = 0; column < test_matrix_1->columns(); ++column)
			{
				const auto& subtraction_value = test_matrix_2->get(row, column);
				const auto& result_value = test_matrix_1->get(row, column);

				// This check only works if both matrix's have the same initial values
				REQUIRE((result_value + subtraction_value) == subtraction_value);
			}
		}
	}

	TEST_CASE("Matrix multiplied by another matrix should have correct values [1]")
	{
		const auto n_rows_1 = 3;
		const auto n_columns_1 = 2;

		const auto n_rows_2 = n_columns_1;
		const auto n_columns_2 = n_rows_1;

		const std::vector<float> values_1{ 1,-2,4,0,-1,7 };
		const std::vector<float> values_2{ 3,-4,5,0,-2,1 };

		const auto test_matrix_1 = create_test_matrix(n_rows_1, n_columns_1, values_1);
		const auto test_matrix_2 = create_test_matrix(n_rows_2, n_columns_2, values_2);

		*test_matrix_1 *= *test_matrix_2;

		const std::vector<float> expected_values{ 3,0,3,12,-16,20,-3,-10,2 };
		
		const auto expected_matrix = create_test_matrix(test_matrix_1->rows(), test_matrix_2->columns(), expected_values);

		REQUIRE(test_matrix_1->has_equal_values(*expected_matrix));
	}

	TEST_CASE("Matrix multiplied by another matrix should have correct values [2]")
	{
		const auto n_rows_1 = 1;
		const auto n_columns_1 = 2;

		const auto n_rows_2 = n_columns_1;
		const auto n_columns_2 = n_rows_1;

		const std::vector<float> values_1{ 1,2 };
		const std::vector<float> values_2{ 3,4 };

		const auto test_matrix_1 = create_test_matrix(n_rows_1, n_columns_1, values_1);
		const auto test_matrix_2 = create_test_matrix(n_rows_2, n_columns_2, values_2);

		*test_matrix_1 *= *test_matrix_2;

		const std::vector<float> expected_values{ 11 };

		const auto expected_matrix = create_test_matrix(test_matrix_1->rows(), test_matrix_2->columns(), expected_values);

		REQUIRE(test_matrix_1->has_equal_values(*expected_matrix));
	}

	TEST_CASE("Matrix multiplied by another matrix should have correct values [3]")
	{
		const auto n_rows_1 = 1;
		const auto n_columns_1 = 2;

		const auto n_rows_2 = n_columns_1;
		const auto n_columns_2 = n_rows_1;

		const std::vector<float> values_1{ 1,2 };
		const std::vector<float> values_2{ 3,4 };

		const auto test_matrix_1 = create_test_matrix(n_rows_1, n_columns_1, values_1);
		const auto test_matrix_2 = create_test_matrix(n_rows_2, n_columns_2, values_2);

		*test_matrix_2 *= *test_matrix_1;

		const std::vector<float> expected_values{ 3,6,4,8 };

		const auto expected_matrix = create_test_matrix(test_matrix_2->rows(), test_matrix_1->columns(), expected_values);

		REQUIRE(test_matrix_2->has_equal_values(*expected_matrix));
	}
}
