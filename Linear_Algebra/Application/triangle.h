#pragma once
#include <memory>

#include "matrix3d.h"

namespace application::shape
{
	class triangle
	{
	private:
		std::unique_ptr<math::matrix3d> points_[3];
	
	public:
		triangle(
			float p1_x, float p1_y, float p1_z, 
			float p2_x, float p2_y, float p2_z, 
			float p3_x, float p3_y, float p3_z);
		
		triangle(
			std::unique_ptr<math::matrix3d> p1, 
			std::unique_ptr<math::matrix3d> p2, 
			std::unique_ptr<math::matrix3d> p3);

		auto operator[](int index) const -> const math::matrix3d&;
	};
}

