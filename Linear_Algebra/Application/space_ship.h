#pragma once
#include "object.h"

namespace application
{
	class space_ship final : public object
	{
	public:
		explicit space_ship(const std::string& obj_file_location);
	};
}
