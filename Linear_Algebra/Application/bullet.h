#pragma once
#include "object.h"

namespace application
{
    class bullet final : public object
    {
    private:
        // When a bullet 'dies' or 'drops'
        float bullet_life_time_;
        float movement_speed_;

        float current_life_time_;

    public:
        explicit bullet(const math::matrix3d& location, const axis& axis, float movement_speed, const std::string& obj_file_location);

        auto remove_on_collide(object& other) -> bool override;

        auto tick(float elapsed_time, bool debug, draw_triangle_fn draw_triangle, draw_line_fn draw_line) -> void override;
        auto is_valid() const -> bool override;

    private:
        auto move(float elapsed_time) -> void;
    };
}
