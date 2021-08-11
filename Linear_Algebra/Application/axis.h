#pragma once
#include <functional>

#include "matrix3d.h"

namespace application
{
	class axis final
	{
	private:
		struct line_data
		{
			math::matrix3d from;
			math::matrix3d to;
			
			uint8_t r;
			uint8_t g;
			uint32_t b;
		};

		std::vector<line_data> axes_;
		
		axis(float x, float y, float z);
	
	public:
		axis();
		explicit axis(float axis_size);
		auto move(const math::matrix& translation_matrix) -> void;
		auto rotate(const math::matrix& matrix_m) -> void;

		auto is_valid() const -> bool;

		auto x() const -> std::unique_ptr<math::matrix3d>;
		auto y() const -> std::unique_ptr<math::matrix3d>;
		auto z() const -> std::unique_ptr<math::matrix3d>;
		
		auto draw(
			const math::matrix& matrix_m,
			float x_center,
			float y_center,
			std::function<void(float, float, float, float, int8_t, int8_t, int8_t)> draw_line_fn) -> void;
	};
}


