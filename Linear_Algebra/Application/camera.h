#pragma once
#include "matrix3d.h"

namespace application
{
	class camera final
	{
	private:
		math::matrix3d right_;
		math::matrix3d up_;
		math::matrix3d direction_;

		// eye
		math::matrix3d position_;
		math::matrix3d lookat_;
	
	public:
		camera();

		auto lookat(math::matrix3d point) -> void;
	};
}


