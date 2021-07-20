#include "object.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace application
{
	object::object()
		: shape_(), location_(math::matrix3d(0, 0, 0))
	{
	}

	object::object(const std::string& obj_file_location)
		: location_(math::matrix3d(0, 0, 0))
	{
		if(!parse_obj_file(obj_file_location))
		{
			throw std::runtime_error("Unable to initialize new object with .obj file: \"" + obj_file_location + "\"");
		}
	}

	auto object::location() const -> const math::matrix3d&
	{
		return location_;
	}

	auto object::shape() const -> const mesh&
	{
		return shape_;
	}

	auto object::shape() -> mesh&
	{
		return shape_;
	}

	auto object::tick(
		const bool debug, 
		const math::matrix& projection_matrix,
		const float x_center, const float y_center,
		const draw_triangle_fn draw_triangle,
		const draw_line_fn draw_line) -> void
	{
		shape_.draw(projection_matrix, x_center, y_center, draw_triangle);

		calc_bounding_box();

		if (debug)
		{
			print_location(projection_matrix, x_center, y_center, draw_line);
			bounding_box_.draw(projection_matrix, x_center, y_center, draw_line);
		}
	}

	auto object::parse_obj_file(const std::string& obj_file_location) -> bool
	{
		shape_ = mesh();
		
		std::ifstream file_stream(obj_file_location);

		if (!file_stream.is_open())
		{
			return false;
		}

		auto vertices = std::vector<math::matrix3d>();

		std::string file_line;

		char identifier;

		// triangle has 3 points
		int vertex_index[3]{};

		while (std::getline(file_stream, file_line))
		{
			std::stringstream ss;

			ss << file_line;

			if (file_line[0] == 'v')
			{
				math::matrix3d vertex;

				ss >> identifier >> vertex.x() >> vertex.y() >> vertex.z();

				vertices.push_back(vertex);
			}
			else if (file_line[0] == 'f')
			{
				ss >> identifier >> vertex_index[0] >> vertex_index[1] >> vertex_index[2];

				// file index starts counting at 1 not 0 so - 1
				const auto vertex_1 = vertex_index[0] - 1;
				const auto vertex_2 = vertex_index[1] - 1;
				const auto vertex_3 = vertex_index[2] - 1;

				shape_.triangles().push_back({
					vertices[vertex_1],
					vertices[vertex_2],
					vertices[vertex_3]
					});

			}
		}

		return true;
	}

	auto object::calc_bounding_box() -> void
	{
		shape_.update_vertices_min_max();

		const auto min_x = shape_.min_x();
		const auto max_x = shape_.max_x();

		const auto min_y = shape_.min_y();
		const auto max_y = shape_.max_y();

		const auto min_z = shape_.min_z();
		const auto max_z = shape_.max_z();

		// order for both front and back: bottom left -> top left -> top right -> bottom right
		
		// FRONT PLANE
		bounding_box_.vertices[0].x() = min_x;
		bounding_box_.vertices[0].y() = min_y;
		bounding_box_.vertices[0].z() = min_z;

		bounding_box_.vertices[1].x() = min_x;
		bounding_box_.vertices[1].y() = max_y;
		bounding_box_.vertices[1].z() = min_z;

		bounding_box_.vertices[2].x() = max_x;
		bounding_box_.vertices[2].y() = max_y;
		bounding_box_.vertices[2].z() = min_z;

		bounding_box_.vertices[3].x() = max_x;
		bounding_box_.vertices[3].y() = min_y;
		bounding_box_.vertices[3].z() = min_z;

		// BACK PLANE
		bounding_box_.vertices[4].x() = min_x;
		bounding_box_.vertices[4].y() = min_y;
		bounding_box_.vertices[4].z() = max_z;

		bounding_box_.vertices[5].x() = min_x;
		bounding_box_.vertices[5].y() = max_y;
		bounding_box_.vertices[5].z() = max_z;

		bounding_box_.vertices[6].x() = max_x;
		bounding_box_.vertices[6].y() = max_y;
		bounding_box_.vertices[6].z() = max_z;

		bounding_box_.vertices[7].x() = max_x;
		bounding_box_.vertices[7].y() = min_y; 
		bounding_box_.vertices[7].z() = max_z;
	}

	auto object::print_location(
		const math::matrix& projection_matrix,
		const float x_center, const float y_center,
		std::function<void(float, float, float, float, int8_t, int8_t, int8_t)> draw_line) -> void
	{
		const auto& x = location_.x();
		const auto& y = location_.y();
		const auto& z = location_.z();

		//const auto location_projected = location_.get_projection(projection_matrix, x_center, y_center);

		//draw_line(location_projected->x(), location_projected->y(), 0, 0, 255, 0, 0);
		
		std::cout
		<< "space_ship: "
		<< "x: \"" + std::to_string(x) + "\" "
		<< "y: \"" + std::to_string(y) + "\" "
		<< "z: \"" + std::to_string(z) + "\"" << std::endl;
	}
}
