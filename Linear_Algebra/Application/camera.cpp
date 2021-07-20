#include "camera.h"

namespace application
{
	camera::camera():
		up_(0, 1, 0)
	{
	}

	auto camera::lookat(const math::matrix3d point) -> void
	{
		lookat_ = point;
		
		direction_ = *(position_ - lookat_);
	}
}
