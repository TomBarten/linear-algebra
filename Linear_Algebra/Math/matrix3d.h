#pragma once
#include "dimensional_matrix.h"

namespace math
{
    class matrix3d final : public base::dimensional_matrix<matrix3d>
    {
    public:
        matrix3d(float x, float y, float z);
        explicit matrix3d(std::unique_ptr<matrix> matrix_init);

        auto scale(const matrix& m_matrix) -> std::unique_ptr<matrix3d>;

        auto x() const -> const float&;
        auto y() const -> const float&;
        auto z() const -> const float&;
    };
}


