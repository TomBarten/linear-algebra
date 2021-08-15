#include "bullet.h"

#include "matrix_helper_3d.h"
#include "target_obj.h"

namespace application
{
    bullet::bullet(const math::matrix3d& location, const axis& axis, const float movement_speed, const std::string& obj_file_location)
        : object(obj_file_location), bullet_life_time_(5.f), movement_speed_(movement_speed), current_life_time_(0.f)
    {
        axis_ = axis;
        location_.set_values(location);

        const auto translation_matrix = math::get_translation_matrix(location_.x(), location_.y(), location_.z());

        for (auto& [points, _0, _1, _2] : shape_.triangles())
        {
            for (auto& matrix : points)
            {
                const auto result = matrix.multiply_by_4X4(*translation_matrix);

                matrix.set_values(*result);
            }
        }
    }

    auto bullet::remove_on_collide(object& other) -> bool
    {
        if (dynamic_cast<const target_obj*>(&other) == nullptr)
        {
            return false;
        }

        other.remove_on_collide(*this);

        return true;
    }

    void bullet::tick(const float elapsed_time, const bool debug, const draw_triangle_fn draw_triangle, const draw_line_fn draw_line)
    {
        move(elapsed_time);

        object::tick(elapsed_time, debug, draw_triangle, draw_line);

        current_life_time_ += elapsed_time;

        should_be_removed_ = current_life_time_ >= bullet_life_time_;
    }

    bool bullet::is_valid() const
    {
        return !should_be_removed_;
    }

    auto bullet::move(const float elapsed_time) -> void
    {
        const auto v_movement = (*axis_.z() * movement_speed_);

        const auto move_translation = math::get_translation_matrix(v_movement->x(), v_movement->y(), v_movement->z());

        const auto new_location = location_.multiply_by_4X4(*move_translation);

        location_.set_values(*new_location);

        axis_.move(*move_translation);

        for (auto& [points, _0, _1, _2] : shape_.triangles())
        {
            for (auto& matrix : points)
            {
                const auto result = matrix.multiply_by_4X4(*move_translation);

                matrix.set_values(*result);
            }
        }
    }
}
