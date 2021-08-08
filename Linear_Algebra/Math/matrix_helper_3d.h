#pragma once

#include <cmath>
#include "math_helper.h"
#include "matrix3d.h"

namespace math
{
	inline auto get_scaling_matrix_3d(const float scaling_x, const float scaling_y, const float scaling_z) -> std::unique_ptr<matrix>
	{
		const std::vector<float> scaling_values
		{
			scaling_x, 0, 0, 0,
			0, scaling_y, 0, 0,
			0, 0, scaling_z, 0,
			0, 0, 0, 1,
		};

		return std::move(std::make_unique<matrix>(4, 4, scaling_values));
	}
	
	inline auto get_translation_matrix(const float translate_x, const float translate_y, const float translate_z) -> std::unique_ptr<matrix>
	{
		const std::vector<float> translation_values
		{
			1, 0, 0, translate_x,
			0, 1, 0, translate_y,
			0, 0, 1, translate_z,
			0, 0, 0, 1,
		};

		return std::move(std::make_unique<matrix>(4, 4, translation_values));
	}

	inline auto create_scale_matrix_3d(const matrix3d& position, const float scaling_x, const float scaling_y, const float scaling_z) -> std::unique_ptr<matrix>
	{
		// T1
		const auto t1_matrix = get_translation_matrix(-position.x(), -position.y(), -position.z());

		// S
		const auto s_matrix = get_scaling_matrix_3d(scaling_x, scaling_y, scaling_z);

		// T2
		const auto t2_matrix = get_translation_matrix(position.x(), position.y(), position.z());

		// T2 (S * T1)
		auto m_matrix = (*t2_matrix) * *((*s_matrix) * (*t1_matrix));

		return std::move(m_matrix);
	}

	inline auto create_scale_matrix_3d(const matrix3d& position, const float scaling) -> std::unique_ptr<matrix>
	{
		return std::move(create_scale_matrix_3d(position, scaling, scaling, scaling));
	}

	inline auto get_rot_matrix_x(const float degrees) -> std::unique_ptr<matrix>
	{
		const auto radial = degrees_to_radial(degrees);
		
		const std::vector<float> rot_x_values
		{
			1, 0, 0, 0,
			0, cosf(radial), -sinf(radial), 0,
			0, sinf(radial), cosf(radial), 0,
			0, 0, 0, 1,
		};

		return std::move(std::make_unique<matrix>(4, 4, rot_x_values));
	}

	inline auto get_rot_matrix_y(const float degrees) -> std::unique_ptr<matrix>
	{
		const auto radial = degrees_to_radial(degrees);

		const std::vector<float> rot_y_values
		{
			cosf(radial), 0, sinf(radial), 0,
			0, 1, 0, 0,
			-sinf(radial), 0, cosf(radial), 0,
			0, 0, 0, 1,
		};

		return std::move(std::make_unique<matrix>(4, 4, rot_y_values));
	}

	inline auto get_rot_matrix_z(const float degrees) -> std::unique_ptr<matrix>
	{
		const auto radial = degrees_to_radial(degrees);

		const std::vector<float> rot_z_values
		{
			cosf(radial), -sinf(radial), 0, 0,
			sinf(radial), cosf(radial), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1,
		};

		return std::move(std::make_unique<matrix>(4, 4, rot_z_values));
	}

	inline auto get_projection_matrix(const float fov_y, const float z_near, const float z_far) -> std::unique_ptr<matrix>
	{
		const float scale = z_near * tanf(degrees_to_radial(fov_y * 0.5));

		const std::vector<float> projection_values
		{
			scale, 0, 0, 0,
			0, scale, 0, 0,
			0, 0, (-z_far / (z_far - z_near)), -1, /* -1 to put w = -z */
			0, 0, ((-z_far * z_near) / (z_far - z_near)), 0,
		};

		return std::move(std::make_unique<matrix>(4, 4, projection_values));
	}

	inline auto get_identity_matrix() -> std::unique_ptr<matrix>
	{
		const std::vector<float> identity_values
		{
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1,
		};

		return std::move(std::make_unique<matrix>(4, 4, identity_values));
	}

	/*
	 * "In product"
	 * VECTOR MULTIPLICATION; NOT MATRIX MULTIPLICATION
	 */
	inline auto get_dot_product(const matrix3d& vector_v, const matrix3d& vector_w) -> float
	{
		const auto x_result = vector_v.x() * vector_w.x();
		const auto y_result = vector_v.y() * vector_w.y();
		const auto z_result = vector_v.z() * vector_w.z();

		const auto v_dot_w = x_result + y_result + z_result;

		return v_dot_w;
	}

	/*
	 * VECTOR MULTIPLICATION; NOT MATRIX MULTIPLICATION
	 */
	inline auto get_angle_degrees(const matrix3d& vector_v, const matrix3d& vector_w) -> float
	{
		const auto dot_product = get_dot_product(vector_v, vector_w);
		
		const auto length_multiplied = vector_v.length() * vector_w.length();

		// v is the exact same direction as w = 1
		// v perpendicular to w = 0
		// v is the exact opposite direction to w = -1
		const auto result = dot_product / length_multiplied;
		
		// acosf returns arc cosine of x (input) expressed in radians, so convert to degrees for consistency
		return radial_to_degrees(acosf(result));
	}

	/*
	 * "Uit product"
	 * VECTOR MULTIPLICATION; NOT MATRIX MULTIPLICATION
	 *
	 * returns vector that is perpendicular to the input vectors
	 */
	inline auto get_cross_product(const matrix3d& vector_v, const matrix3d& vector_w) -> std::unique_ptr<matrix3d>
	{
		// create empty matrix to populate with the cross product results
		auto result_matrix = std::make_unique<matrix3d>();

		result_matrix->x() = (vector_v.y() * vector_w.z()) - (vector_v.z() * vector_w.y());
		result_matrix->y() = (vector_v.z() * vector_w.x()) - (vector_v.x() * vector_w.z());
		result_matrix->z() = (vector_v.x() * vector_w.y()) - (vector_v.y() * vector_w.x());
		
		return std::move(result_matrix);
	}

	inline auto get_axis_rot_matrix(const matrix3d& position, const matrix3d& axis, const float degrees)
	{
		auto validate_val = [](const float val) -> float
		{
			if (std::isnan(val))
			{
				return 0.f;
			}

			return val;
		};
		
		// T-Back
		const auto t_back = get_translation_matrix(position.x(), position.y(), position.z());

		// T-To
		const auto t_to = get_translation_matrix(-position.x(), -position.y(), -position.z());

		const auto x = axis.x();
		const auto x_sq = (x * x);
		
		const auto y = axis.y();
		const auto y_sq = (y * y);
		
		const auto z = axis.z();
		const auto z_sq = (z * z);

		// M1 rotate to xy plane (y rotation)
		std::vector<float> rot_to_xy_plane_values
		{
			validate_val(x / sqrtf(x_sq + z_sq)), 0, validate_val(z / sqrtf(x_sq + z_sq)), 0,
			0, 1, 0, 0,
			-validate_val(z / sqrtf(x_sq + z_sq)), 0, validate_val(x / sqrtf(x_sq + z_sq)), 0,
			0, 0, 0, 1,
		};
		const auto m1 = std::make_unique<matrix>(4, 4, rot_to_xy_plane_values);

		// M2 rotate to x axis (z rotation)
		const std::vector<float> rot_to_x_values
		{
			validate_val(sqrtf(x_sq + z_sq) / sqrtf(x_sq + y_sq + z_sq)), validate_val(y / sqrtf(x_sq + y_sq + z_sq)), 0, 0,
			-validate_val(y / sqrtf(x_sq + y_sq + z_sq)), validate_val(sqrtf(x_sq + z_sq) / sqrtf(x_sq + y_sq + z_sq)), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1,
		};
		const auto m2 = std::make_unique<matrix>(4, 4, rot_to_x_values);

		// M3 rotate around x axis
		const auto m3 = get_rot_matrix_x(degrees);

		// M4 opposite of M2 (rotate away from x axis) (z rotation)
		const std::vector<float> rot_from_x_values
		{
			validate_val(sqrtf(x_sq + z_sq) / sqrtf(x_sq + y_sq + z_sq)), -validate_val(y / sqrtf(x_sq + y_sq + z_sq)), 0, 0,
			validate_val(y / sqrtf(x_sq + y_sq + z_sq)), validate_val(sqrtf(x_sq + z_sq) / sqrtf(x_sq + y_sq + z_sq)), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1,
		};
		const auto m4 = std::make_unique<matrix>(4, 4, rot_from_x_values);

		// M5 opposite of M1 (rotate out of xy plane) (y rotation)
		const std::vector<float> rot_from_xy_plane_values
		{
			validate_val(x / sqrtf(x_sq + z_sq)), 0, -validate_val(z / sqrtf(x_sq + z_sq)), 0,
			0, 1, 0, 0,
			validate_val(z / sqrtf(x_sq + z_sq)), 0, validate_val(x / sqrtf(x_sq + z_sq)), 0,
			0, 0, 0, 1,
		};
		const auto m5 = std::make_unique<matrix>(4, 4, rot_from_xy_plane_values);

		const auto validate_result = [](matrix& result_matrix)
		{
			if(auto& x_modifier = result_matrix.get(0, 0); x_modifier == 0.f)
			{
				x_modifier = 1.f;
			}

			if(auto& y_modifier = result_matrix.get(1, 1); y_modifier == 0.f)
			{
				y_modifier = 1.f;
			}

			if(auto& z_modifier =  result_matrix.get(2, 2); z_modifier == 0.f)
			{
				z_modifier = 1.f;
			}
		};

		// Tback * M5 * M4 * M3 * M2 * M1 * Tto
		auto result = *(*(*t_back * *m5) * *(*m4 * *m3)) * *(*(*m2 * *m1) * *t_to);

		validate_result(*result);

		return std::move(result);
	}
}
