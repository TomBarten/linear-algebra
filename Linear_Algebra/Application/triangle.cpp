#include "triangle.h"

namespace application::shape
{
	triangle::triangle
	(
		float p1_x, float p1_y, float p1_z, 
		float p2_x, float p2_y, float p2_z, 
		float p3_x, float p3_y, float p3_z
	):
	triangle
	(
		std::move(std::make_unique<math::matrix3d>(p1_x, p1_y, p1_z)), 
		std::move(std::make_unique<math::matrix3d>(p2_x, p2_y, p2_z)),
		std::move(std::make_unique<math::matrix3d>(p3_x, p3_y, p3_z))
	) {}

	triangle::triangle(
		std::unique_ptr<math::matrix3d> p1, 
		std::unique_ptr<math::matrix3d> p2,
		std::unique_ptr<math::matrix3d> p3)
	{
		points_[0] = std::move(p1);
		points_[1] = std::move(p2);
		points_[2] = std::move(p3);
	}

	auto triangle::operator[](const int index) const -> const math::matrix3d&
	{		
		return *points_[index];
	}
}

