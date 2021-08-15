#pragma once
#include "object.h"

namespace application
{
	class target_obj final : public object
	{
	private:
        explicit target_obj(const std::string& obj_file_location);
        target_obj(float x, float y, float z, const std::string& obj_file_location);

		bool scale_up_;

		float max_scale_;
		float min_scale_;

		float tick_scale_;
		float current_scale_;

		int max_hits_ = 5;
		int amount_times_hit_ = 0;

		mesh scaled_shape_;

	public:
		explicit target_obj(const math::matrix3d& location, const std::string& obj_file_location);

		auto shape() -> mesh& override;
		auto shape() const -> const mesh& override;

		auto tick(float elapsed_time, bool debug, draw_triangle_fn draw_triangle, draw_line_fn draw_line) -> void override;

		auto remove_on_collide(object& other) -> bool override;

		auto is_valid() const -> bool override;

	private:
		auto pulse(float elapsed_time) -> mesh;
		auto get_scale_matrix(float scaling) const -> std::unique_ptr<math::matrix>;
		auto scale(const math::matrix& scale_matrix) -> mesh;
		auto print_location(math::matrix& matrix_m) -> void override;
		auto approach_val(float current, float target, float speed) const -> float;
	};
}
