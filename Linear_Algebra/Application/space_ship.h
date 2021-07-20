#pragma once
#include "object.h"

namespace application
{
	class space_ship final : public object
	{
	private:
		math::matrix3d velocity_;

		float rotation_modifier;
	
	public:
		explicit space_ship(const std::string& obj_file_location);

		auto pitch(const bool up, const float elapsed_time) -> void;
		auto yaw(const bool right, const float elapsed_time) -> void;
		auto roll(const bool right, const float elapsed_time) -> void;

	private:
		auto invert_modifier(bool invert) const -> float;
		auto calculate(const math::matrix& m_matrix) -> void;
	};
}
