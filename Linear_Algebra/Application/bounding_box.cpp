﻿#include "bounding_box.h"

namespace application
{
	auto bounding_box::draw(
		const math::matrix& projection_matrix,
		const float x_center, const float y_center,
		const std::function<void(float, float, float, float, int8_t, int8_t, int8_t)> draw_line_fn) -> void
	{
		const int8_t r = 255;
		const int8_t g = 0;
		const int8_t b = 0;

		const auto depth_temp = 50.f;
		
		// TODO make data structure that has a "connected to" property, this is "temporary" dirty fix
		// 
		// assuming frontal xy view
		// clockwise: front_bottom_left -> front_top_right -> front_top_right -> etc.
		auto& front_bottom_left = vertices[0];
		auto& front_top_left = vertices[1];
		auto& front_top_right = vertices[2];
		auto& front_bottom_right = vertices[3];

		auto& back_bottom_left = vertices[4];
		auto& back_top_left = vertices[5];
		auto& back_top_right = vertices[6];
		auto& back_bottom_right = vertices[7];

		// TODO REMOVE THIS
		front_bottom_left.z() += depth_temp;
		front_top_left.z() += depth_temp;
		front_top_right.z() += depth_temp;
		front_bottom_right.z() += depth_temp;

		// TODO REMOVE THIS
		back_bottom_left.z() += depth_temp;
		back_top_left.z() += depth_temp;
		back_top_right.z() += depth_temp;
		back_bottom_right.z() += depth_temp;

		const auto front_bottom_left_proj = front_bottom_left.get_projection(projection_matrix, x_center, y_center);
		const auto front_top_left_proj = front_top_left.get_projection(projection_matrix, x_center, y_center);
		const auto front_top_right_proj = front_top_right.get_projection(projection_matrix, x_center, y_center);
		const auto front_bottom_right_proj = front_bottom_right.get_projection(projection_matrix, x_center, y_center);

		const auto back_bottom_left_proj = back_bottom_left.get_projection(projection_matrix, x_center, y_center);
		const auto back_top_left_proj = back_top_left.get_projection(projection_matrix, x_center, y_center);
		const auto back_top_right_proj = back_top_right.get_projection(projection_matrix, x_center, y_center);
		const auto back_bottom_right_proj = back_bottom_right.get_projection(projection_matrix, x_center, y_center);

		draw_line_fn(front_bottom_left_proj->x(), front_bottom_left_proj->y(), front_top_left_proj->x(), front_top_left_proj->y(), r, g ,b);
		draw_line_fn(front_bottom_left_proj->x(), front_bottom_left_proj->y(), front_bottom_right_proj->x(), front_bottom_right_proj->y(), r, g, b);
		draw_line_fn(front_bottom_left_proj->x(), front_bottom_left_proj->y(), back_bottom_left_proj->x(), back_bottom_left_proj->y(), r, g, b);

		// connection already drawn to front_bottom_left
		draw_line_fn(front_top_left_proj->x(), front_top_left_proj->y(), front_top_right_proj->x(), front_top_right_proj->y(), r, g, b);
		draw_line_fn(front_top_left_proj->x(), front_top_left_proj->y(), back_top_left_proj->x(), back_top_left_proj->y(), r, g, b);

		// connection already drawn to front_top_left
		draw_line_fn(front_top_right_proj->x(), front_top_right_proj->y(), front_bottom_right_proj->x(), front_bottom_right_proj->y(), r, g, b);
		draw_line_fn(front_top_right_proj->x(), front_top_right_proj->y(), back_top_right_proj->x(), back_top_right_proj->y(), r, g, b);

		// connection already drawn to front_bottom_left and front_top_right
		draw_line_fn(front_bottom_right_proj->x(), front_bottom_right_proj->y(), back_bottom_right_proj->x(), back_bottom_right_proj->y(), r, g, b);

		// connection already drawn to front_bottom_left
		draw_line_fn(back_bottom_left_proj->x(), back_bottom_left_proj->y(), back_top_left_proj->x(), back_top_left_proj->y(), r, g, b);
		draw_line_fn(back_bottom_left_proj->x(), back_bottom_left_proj->y(), back_bottom_right_proj->x(), back_bottom_right_proj->y(), r, g, b);

		// connection already drawn to front_top_left and back_bottom_left
		draw_line_fn(back_top_left_proj->x(), back_top_left_proj->y(), back_top_right_proj->x(), back_top_right_proj->y(), r, g, b);

		// connection already drawn to back_top_left and front_top_right
		draw_line_fn(back_top_right_proj->x(), back_top_right_proj->y(), back_bottom_right_proj->x(), back_bottom_right_proj->y(), r, g, b);
	}
}
