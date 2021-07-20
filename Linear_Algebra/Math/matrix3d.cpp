#include "matrix3d.h"

#include <stdexcept>

namespace math
{
	matrix3d::matrix3d()
		:dimensional_matrix<matrix3d>(3, 1)
	{
	}

	matrix3d::matrix3d(const float x, const float y, const float z)
		: dimensional_matrix<matrix3d>(3, 1)
	{
		matrix_(0, 0) = x;
		matrix_(1, 0) = y;
		matrix_(2, 0) = z;
	}

	matrix3d::matrix3d(std::unique_ptr<matrix> matrix_init)
		: dimensional_matrix(std::move(matrix_init))
	{
		if(matrix_.rows() != 3 || matrix_.columns() != 1)
		{
			throw std::runtime_error("Cannot initialize vector3d with invalid matrix");
		}
	}

	auto matrix3d::multiply_by_4X4(const matrix& matrix_4X4) -> std::unique_ptr<matrix3d>
	{
		// Add 1 extra row so it can be multiplied by M matrix
		// Extra value 1 in new row
		matrix_.resize(4, 1);
		matrix_(3, 0) = 1;

		auto result_matrix = matrix_4X4 * matrix_;

		// Remove extra row, will also remove extra value automatically
		matrix_.resize(3, 1);
		result_matrix->resize(3, 1);
		
		auto result = std::make_unique<matrix3d>(std::move(result_matrix));

		return std::move(result);
	}

	auto matrix3d::get_projection(const matrix& projection_matrix, const int screen_center_x, const int screen_center_y) -> std::unique_ptr<matrix3d>
	{
		matrix_.resize(4, 1);
		matrix_(3, 0) = 1;

		auto result_matrix = projection_matrix * matrix_;

		if(const auto w = result_matrix->get(3, 0); w != 0.f)
		{
			// x
			auto& x = result_matrix->get(0, 0);
			x = screen_center_x + (x / w) * screen_center_x;

			// y
			auto& y = result_matrix->get(1, 0);
			y = screen_center_y + (y / w) * screen_center_y;
		}

		matrix_.resize(3, 1);
		result_matrix->resize(3, 1);

		auto result = std::make_unique<matrix3d>(std::move(result_matrix));

		return std::move(result);
	}

	auto matrix3d::length() const -> float
	{
		const auto x_squared = powf(x(), 2.f);
		const auto y_squared = powf(y(), 2.f);
		const auto z_squared = powf(z(), 2.f);

		return sqrtf(x_squared + y_squared + z_squared);
	}

	auto matrix3d::norm() const -> std::unique_ptr<matrix3d>
	{
		auto result = matrix_ / length();

		auto result_matrix = std::make_unique<matrix3d>(std::move(result));

		return std::move(result_matrix);
	}

	auto matrix3d::x() const -> const float&
	{
		return matrix_(0, 0);
	}

	auto matrix3d::x() -> float&
	{
		return matrix_(0, 0);
	}

	auto matrix3d::y() const -> const float&
	{
		return matrix_(1, 0);
	}

	auto matrix3d::y() -> float&
	{
		return matrix_(1, 0);
	}

	auto matrix3d::z() const -> const float&
	{
		return matrix_(2, 0);
	}

	auto matrix3d::z() -> float&
	{
		return matrix_(2, 0);
	}

	auto matrix3d::w() const -> const float&
	{
		return matrix_(3, 0);
	}

	auto matrix3d::w() -> float&
	{
		return matrix_(3, 0);
	}
}
