#include "mesh.h"

namespace application::shape
{
	auto mesh::emplace_back(std::unique_ptr<triangle> triangle) -> void
	{
		triangles_.emplace_back(std::move(triangle));
	}

	//auto mesh::operator=(std::initializer_list<std::unique_ptr<triangle>> init_list) -> void
	//{
	//	triangles_ = { std::move(init_list) };
	//}
}
