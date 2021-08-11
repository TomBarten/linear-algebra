#include "axis.h"

#include "matrix_helper_3d.h"

using namespace math;

namespace application
{
	axis::axis(const float x, const float y, const float z)
	{
		axes_ = 
		{
			{matrix3d(), matrix3d(x, 0.0f, 0.0f), 255, 0, 0},
			{matrix3d(), matrix3d(0.0f, y, 0.0f), 0, 255, 0},
			{matrix3d(), matrix3d(0.0f, 0.0f, z), 0, 0, 255}
		};
	}
	
	axis::axis()
		:axis(1, 1, 1)
	{
	}

	axis::axis(const float axis_size)
		:axis(axis_size, axis_size, axis_size)
	{
		
	}

	auto axis::move(const matrix& translation_matrix) -> void
	{
		for (auto& axis : axes_)
		{
			const auto new_from = axis.from.multiply_by_4X4(translation_matrix);

			axis.from.set_values(*new_from);

			const auto new_to = axis.to.multiply_by_4X4(translation_matrix);
			
			axis.to.set_values(*new_to);
		}
	}

	auto axis::rotate(const matrix& matrix_m) -> void
	{
		for(auto& axis : axes_)
		{
			const auto rot_result = axis.to.multiply_by_4X4(matrix_m);

			axis.to.set_values(*rot_result);
		}
	}

    auto axis::is_valid() const -> bool
    {
		// If there are no axes, then the axis representation is not valid
		return axes_.capacity() != 0;
    }

    auto axis::x() const -> std::unique_ptr<matrix3d>
	{
		const auto& [from, to, _1, _2, _3] = axes_[0];

		auto direction = (to - from)->normalise();

		direction->w() = 1;

		return std::move(direction);
	}

	auto axis::y() const -> std::unique_ptr<matrix3d>
	{
		const auto& [from, to, _1, _2, _3] = axes_[1];

		auto direction = (to - from)->normalise();

		direction->w() = 1;

		return std::move(direction);
	}

	auto axis::z() const -> std::unique_ptr<matrix3d>
	{
		const auto& [from, to, _1, _2, _3] = axes_[2];

		auto direction = (to - from)->normalise();

		direction->w() = 1;

		return std::move(direction);
	}

	auto axis::draw(
		const matrix& matrix_m,
		const float x_center, const float y_center,
		const std::function<void(float, float, float, float, int8_t, int8_t, int8_t)> draw_line_fn) -> void
	{
		for(const auto& [from, to, r, g, b] : axes_)
		{
			const auto from_projected = from.get_projection(matrix_m, x_center, y_center);
			const auto to_projected = to.get_projection(matrix_m, x_center, y_center);
			
			draw_line_fn(from_projected->x(), from_projected->y(), to_projected->x(), to_projected->y(), r, g, b);
		}
	}
}
