#include "object.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "matrix2d.h"
#include "matrix_helper_3d.h"

namespace application
{
	object::object()
        : shape_(), location_(math::matrix3d(0, 0, 0)), x_center_(0), y_center_(0), should_be_removed_(false)
    {
    }

	object::object(const std::string& obj_file_location)
		: object()
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

	auto object::set_xy_center(const float x_center, const float y_center) -> void
	{
		x_center_ = x_center;
		y_center_ = y_center;
	}

	auto object::set_proj_matrix(const std::shared_ptr<math::matrix> projection_matrix) -> void
	{
		projection_matrix_ = projection_matrix;
	}

    auto object::set_camera_matrix(const std::shared_ptr<math::matrix> camera_matrix) -> void
	{
		camera_matrix_ = camera_matrix;
	}

    auto object::is_valid() const -> bool
    {
		// No axes means that object no longer is valid
		return axis_.is_valid() && !should_be_removed_;
    }

    auto object::has_collision(const object& other) const -> bool
    {
		const auto& other_shape = other.shape();

		const auto has_collision = (shape_.min_x() <= other_shape.max_x() && shape_.max_x() >= other_shape.min_x()) &&
			(shape_.min_y() <= other_shape.max_y() && shape_.max_y() >= other_shape.min_y()) &&
			(shape_.min_z() <= other_shape.max_z() && shape_.max_z() >= other_shape.min_z());

		return has_collision;
    }

    auto object::tick(
		const float elapsed_time,
		const bool debug, 
		const draw_triangle_fn draw_triangle,
		const draw_line_fn draw_line) -> void
	{
		const auto matrix_m = *projection_matrix_ * *camera_matrix_;

		shape_.draw(*matrix_m, x_center_, y_center_, draw_triangle);
		
		calc_bounding_box(shape_);
		
		if (debug)
		{
			print_location(*matrix_m);
			
			axis_.draw(*matrix_m, x_center_, y_center_, draw_line);
			bounding_box_.draw(*matrix_m, x_center_, y_center_, draw_line);
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

	auto object::calc_bounding_box(mesh& shape) -> void
	{
		shape.update_vertices_min_max();

		const auto min_x = shape.min_x();
		const auto max_x = shape.max_x();

		const auto min_y = shape.min_y();
		const auto max_y = shape.max_y();

		const auto min_z = shape.min_z();
		const auto max_z = shape.max_z();

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

	auto object::print_location(math::matrix& matrix_m) -> void
	{
		std::cout
		<< "x: \"" + std::to_string(location_.x()) + "\" "
		<< "y: \"" + std::to_string(location_.y()) + "\" "
		<< "z: \"" + std::to_string(location_.z()) + "\"" << std::endl;
	}
}
