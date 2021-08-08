#include "target_obj.h"
#include "matrix_helper_3d.h"

using namespace math;

namespace application
{
	target_obj::target_obj(): object(),
		scale_up_(true), max_scale_(15.f), min_scale_(1.f), tick_scale_(5.f), current_scale_(1)
	{
		auto& triangles = shape_.triangles();

		triangles =
		{
			{matrix3d(0.0f, 0.0f, 0.0f), matrix3d(0.0f, 1.0f, 0.0f), matrix3d(1.0f, 1.0f, 0.0f)},
			{matrix3d(0.0f, 0.0f, 0.0f), matrix3d(1.0f, 1.0f, 0.0f), matrix3d(1.0f, 0.0f, 0.0f)},

			{matrix3d(1.0f, 0.0f, 0.0f), matrix3d(1.0f, 1.0f, 0.0f), matrix3d(1.0f, 1.0f, 1.0f)},
			{matrix3d(1.0f, 0.0f, 0.0), matrix3d(1.0f, 1.0f, 1.0), matrix3d(1.0f, 0.0f, 1.0f)},

			{matrix3d(1.0f, 0.0f, 1.0), matrix3d(1.0f, 1.0f, 1.0), matrix3d(0.0f, 1.0f, 1.0f)},
			{matrix3d(1.0f, 0.0f, 1.0), matrix3d(0.0f, 1.0f, 1.0), matrix3d(0.0f, 0.0f, 1.0f)},

			{matrix3d(0.0f, 0.0f, 1.0), matrix3d(0.0f, 1.0f, 1.0), matrix3d(0.0f, 1.0f, 0.0f)},
			{matrix3d(0.0f, 0.0f, 1.0), matrix3d(0.0f, 1.0f, 0.0), matrix3d(0.0f, 0.0f, 0.0f)},

			{matrix3d(0.0f, 1.0f, 0.0), matrix3d(0.0f, 1.0f, 1.0), matrix3d(1.0f, 1.0f, 1.0f)},
			{matrix3d(0.0f, 1.0f, 0.0), matrix3d(1.0f, 1.0f, 1.0), matrix3d(1.0f, 1.0f, 0.0f)},

			{matrix3d(1.0f, 0.0f, 1.0), matrix3d(0.0f, 0.0f, 1.0), matrix3d(0.0f, 0.0f, 0.0f)},
			{matrix3d(1.0f, 0.0f, 1.0), matrix3d(0.0f, 0.0f, 0.0), matrix3d(1.0f, 0.0f, 0.0f)},
		};
	}

	target_obj::target_obj(const float x, const float y, const float z)
		: target_obj()
	{
		const auto translation_matrix = get_translation_matrix(x, y, z);
		
		for (auto& [points, _0, _1, _2] : shape_.triangles())
		{
			for (auto& matrix : points)
			{
				const auto result = matrix.multiply_by_4X4(*translation_matrix);

				matrix.set_values(*result);
			}
		}

		axis_.move(*translation_matrix);
	}

	target_obj::target_obj(const matrix3d& location)
		: target_obj(location.x(), location.y(), location.z())
	{
		location_.set_values(location);
	}

	auto target_obj::tick(
		const float elapsed_time, const bool debug, 
		const draw_triangle_fn draw_triangle, const draw_line_fn draw_line) -> void
	{
		const auto matrix_m = *projection_matrix_ * *camera_matrix_;
		
		auto scaled_shape = pulse(elapsed_time);

		scaled_shape.draw(*matrix_m, x_center_, y_center_, draw_triangle);

		calc_bounding_box(scaled_shape);

		if (debug)
		{
			print_location(*matrix_m);

			axis_.draw(*matrix_m, x_center_, y_center_, draw_line);
			bounding_box_.draw(*matrix_m, x_center_, y_center_, draw_line);
		}
	}

	auto target_obj::pulse(const float elapsed_time) -> mesh
	{
		const auto modifier = tick_scale_ * elapsed_time;

		mesh result;

		if (scale_up_)
		{
			current_scale_ = approach_val(current_scale_, max_scale_, modifier);

			const auto scale_matrix = get_scale_matrix(current_scale_);

			result = scale(*scale_matrix);

			if(current_scale_ == max_scale_)
			{
				scale_up_ = false;
			}
		}
		else
		{
			current_scale_ = approach_val(current_scale_, min_scale_, modifier);

			const auto scale_matrix = get_scale_matrix(current_scale_);

			result = scale(*scale_matrix);

			if (current_scale_ == min_scale_)
			{
				scale_up_ = true;
			}
		}

		return result;
	}

	auto target_obj::get_scale_matrix(const float scaling) const -> std::unique_ptr<matrix>
	{		
		auto scale_matrix = create_scale_matrix_3d(location_, scaling);

		return std::move(scale_matrix);
	}


	auto target_obj::scale(const matrix& scale_matrix) -> mesh
	{
		const auto amount_of_triangles = shape_.triangles().size();
		
		auto scaled_shape = mesh(amount_of_triangles);
		
		for(auto i = 0; i < amount_of_triangles; ++i)
		{
			// copy intended
			const auto original_triangle = shape_.triangles()[i];
			
			scaled_shape.triangles()[i] = original_triangle;

			for(auto j = 0; j < std::size(scaled_shape.triangles()[i].vertices); ++j)
			{
				auto& vertex = scaled_shape.triangles()[i].vertices[j];
				const auto result = vertex.multiply_by_4X4(scale_matrix);
				
				vertex.set_values(*result);
			}
		}

		return scaled_shape;
		
		//for (auto triangle : shape_.triangles())
		//{
		//	scaled_shape->triangles().push_back(triangle);
		//	
		//	for (auto& matrix : triangle.vertices)
		//	{
		//		const auto result = matrix.multiply_by_4X4(scale_matrix);

		//		matrix.set_values(*result);
		//	}
		//}
	}

	auto target_obj::print_location(matrix& matrix_m) -> void
	{
		// target doesn't move, so no need to log its location
		return;
	}

	auto target_obj::approach_val(const float current, const float target, const float speed) const -> float
	{
		if (abs(target - current) <= speed)
			return target;

		const auto sign = [](const float val)
		{
			return val >= 0.f ? 1.f : -1.f;
		};

		return current + sign(target - current) * speed;
	}
}
