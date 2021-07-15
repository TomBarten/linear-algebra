#pragma once
#include <vector>

#include "triangle.h"

namespace application::shape
{
	class mesh
	{
	private:
		std::vector<std::unique_ptr<triangle>> triangles_;
	public:
		auto emplace_back(std::unique_ptr<triangle> triangle) -> void;
		//auto operator=(std::initializer_list<std::unique_ptr<triangle>> init_list) -> void;
	};
}

