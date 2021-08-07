#include "bounding_box.h"

namespace application
{
	bounding_box::bounding_box()
	{
		connections_ = 
		{
			{
				&vertices[0],
				{ &vertices[1], &vertices[3], &vertices[4] }
			},
			{
				&vertices[1],
				{ &vertices[2], &vertices[5] }
			},
			{
				&vertices[2],
				{ &vertices[3], &vertices[6] }
			},
			{
				&vertices[3],
				{ &vertices[7] }
			},
			{
				&vertices[4],
				{ &vertices[5], &vertices[7] }
			},
			{
				&vertices[5],
				{ &vertices[6] }
			},
			{
				&vertices[6],
				{ &vertices[7] }
			}
			
		};
	}

	auto bounding_box::draw(
		const math::matrix& matrix_m,
		const float x_center, const float y_center,
		const std::function<void(float, float, float, float, int8_t, int8_t, int8_t)> draw_line_fn) -> void
	{

		auto has_null_ptrs = false;

		for(const auto& [from, connected_to_collection] : connections_)
		{
			if(from == nullptr)
			{
				has_null_ptrs = true;
				return;
			}
			
			const auto from_projected = from->get_projection(matrix_m, x_center, y_center);
			
			for(const auto connected_to : connected_to_collection)
			{
				const auto connected_to_projected = connected_to->get_projection(matrix_m, x_center, y_center);
				
				draw_line_fn(from_projected->x(), from_projected->y(), connected_to_projected->x(), connected_to_projected->y(), r_, g_, b_);
			}
		}

		if(has_null_ptrs)
		{
			connections_.clear();
		}

		// TODO make data structure that has a "connected to" property, this is "temporary" dirty fix
		// 
		// assuming frontal xy view
		// clockwise: front_bottom_left -> front_top_right -> front_top_right -> etc.

		//const auto& front_bottom_left = vertices[0];
		//const auto& front_top_left = vertices[1];
		//const auto& front_top_right = vertices[2];
		//const auto& front_bottom_right = vertices[3];

		//const auto& back_bottom_left = vertices[4];
		//const auto& back_top_left = vertices[5];
		//const auto& back_top_right = vertices[6];
		//const auto& back_bottom_right = vertices[7];

		//const auto front_bottom_left_proj = front_bottom_left.get_projection(matrix_m, x_center, y_center);
		//const auto front_top_left_proj = front_top_left.get_projection(matrix_m, x_center, y_center);
		//const auto front_top_right_proj = front_top_right.get_projection(matrix_m, x_center, y_center);
		//const auto front_bottom_right_proj = front_bottom_right.get_projection(matrix_m, x_center, y_center);

		//const auto back_bottom_left_proj = back_bottom_left.get_projection(matrix_m, x_center, y_center);
		//const auto back_top_left_proj = back_top_left.get_projection(matrix_m, x_center, y_center);
		//const auto back_top_right_proj = back_top_right.get_projection(matrix_m, x_center, y_center);
		//const auto back_bottom_right_proj = back_bottom_right.get_projection(matrix_m, x_center, y_center);

		//draw_line_fn(front_bottom_left_proj->x(), front_bottom_left_proj->y(), front_top_left_proj->x(), front_top_left_proj->y(), r_, g_ ,b_);
		//draw_line_fn(front_bottom_left_proj->x(), front_bottom_left_proj->y(), front_bottom_right_proj->x(), front_bottom_right_proj->y(), r_, g_, b_);
		//draw_line_fn(front_bottom_left_proj->x(), front_bottom_left_proj->y(), back_bottom_left_proj->x(), back_bottom_left_proj->y(), r_, g_, b_);

		//// connection already drawn to front_bottom_left
		//draw_line_fn(front_top_left_proj->x(), front_top_left_proj->y(), front_top_right_proj->x(), front_top_right_proj->y(), r_, g_, b_);
		//draw_line_fn(front_top_left_proj->x(), front_top_left_proj->y(), back_top_left_proj->x(), back_top_left_proj->y(), r_, g_, b_);

		//// connection already drawn to front_top_left
		//draw_line_fn(front_top_right_proj->x(), front_top_right_proj->y(), front_bottom_right_proj->x(), front_bottom_right_proj->y(), r_, g_, b_);
		//draw_line_fn(front_top_right_proj->x(), front_top_right_proj->y(), back_top_right_proj->x(), back_top_right_proj->y(), r_, g_, b_);

		//// connection already drawn to front_bottom_left and front_top_right
		//draw_line_fn(front_bottom_right_proj->x(), front_bottom_right_proj->y(), back_bottom_right_proj->x(), back_bottom_right_proj->y(), r_, g_, b_);

		//// connection already drawn to front_bottom_left
		//draw_line_fn(back_bottom_left_proj->x(), back_bottom_left_proj->y(), back_top_left_proj->x(), back_top_left_proj->y(), r_, g_, b_);
		//draw_line_fn(back_bottom_left_proj->x(), back_bottom_left_proj->y(), back_bottom_right_proj->x(), back_bottom_right_proj->y(), r_, g_, b_);

		//// connection already drawn to front_top_left and back_bottom_left
		//draw_line_fn(back_top_left_proj->x(), back_top_left_proj->y(), back_top_right_proj->x(), back_top_right_proj->y(), r_, g_, b_);

		//// connection already drawn to back_top_left and front_top_right
		//draw_line_fn(back_top_right_proj->x(), back_top_right_proj->y(), back_bottom_right_proj->x(), back_bottom_right_proj->y(), r_, g_, b_);
	}
}
