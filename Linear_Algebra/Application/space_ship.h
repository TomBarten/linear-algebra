#pragma once
#include "bullet.h"
#include "object.h"

namespace application
{
	class space_ship final : public object
	{
	private:
		float movement_speed_;
		float rotation_modifier_;
	
	public:
		explicit space_ship(const std::string& obj_file_location);

		auto get_pitch_matrix(bool up, float elapsed_time) const -> std::unique_ptr<math::matrix>;
		auto get_yaw_matrix(bool right, float elapsed_time) const -> std::unique_ptr<math::matrix>;
		auto get_roll_matrix(bool right, float elapsed_time) const -> std::unique_ptr<math::matrix>;
		auto move(float elapsed_time) -> void;
		auto calculate_rotation(const math::matrix& m_matrix) -> void;
		auto shoot() -> std::unique_ptr<bullet>;

		auto remove_on_collide(object& other) -> bool override;

	private:
		auto get_offset_translation_matrix() -> std::unique_ptr<math::matrix>;
		auto invert_modifier(bool invert) const -> float;
		auto print_location(math::matrix& matrix_m) -> void override;
	};
}
