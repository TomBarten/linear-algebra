#pragma once

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

	inline auto create_scale_matrix_3d(const float scaling_x, const float scaling_y, const float scaling_z) -> std::unique_ptr<matrix>
	{
		// T1
		const auto t1_matrix = get_translation_matrix(-scaling_x, -scaling_y, -scaling_z);

		// S
		const auto s_matrix = get_scaling_matrix_3d(scaling_x, scaling_y, scaling_z);

		// T2
		const auto t2_matrix = get_translation_matrix(scaling_x, scaling_y, scaling_z);

		// T2 (S * T1)
		auto m_matrix = (*t2_matrix) * *((*s_matrix) * (*t1_matrix));

		return std::move(m_matrix);
	}

	inline auto create_scale_matrix_3d(const float scaling) -> std::unique_ptr<matrix>
	{
		return std::move(create_scale_matrix_3d(scaling, scaling, scaling));
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
}
