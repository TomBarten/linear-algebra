#pragma once
#include "vector_base.h"

namespace math
{
    class vector3d final : public base::vector_base<vector3d>
    {
    public:
        vector3d(float x, float y, float z);
        explicit vector3d(std::unique_ptr<matrix> matrix_init);

        auto scale(const matrix& m_matrix) const -> std::unique_ptr<vector3d>;

        auto x() const -> const float&;
        auto y() const -> const float&;
        auto z() const -> const float&;
    };
}


