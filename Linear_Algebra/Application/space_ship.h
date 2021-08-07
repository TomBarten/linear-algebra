#pragma once
#include "object.h"

namespace application
{
	class space_ship final : public object
	{
	private:
		float rotation_modifier_;
	
	public:
		explicit space_ship(const std::string& obj_file_location);

		auto get_pitch_matrix(bool up, float elapsed_time) const -> std::unique_ptr<math::matrix>;
		auto get_yaw_matrix(bool right, float elapsed_time) const -> std::unique_ptr<math::matrix>;
		auto get_roll_matrix(bool right, float elapsed_time) const -> std::unique_ptr<math::matrix>;
		auto move(float elapsed_time) -> void;
		auto calculate_rotation(const math::matrix& m_matrix) -> void;

	private:
		auto invert_modifier(bool invert) const -> float;
		auto print_location(math::matrix& matrix_m) -> void override;
	};
}
