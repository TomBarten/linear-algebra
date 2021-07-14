#pragma once

#include "sdl_manager.h"

namespace application::sdl
{
	struct sdl_manager_deleter
	{
		auto operator()(sdl_manager* manager_ptr) const -> void;
	};
}
