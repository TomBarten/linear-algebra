#pragma once
#include "vector2d.h"

namespace math
{
    class vector3d final : public vector2d
    {
    public:
        vector3d(float x, float y, float z);
        explicit vector3d(std::unique_ptr<matrix> matrix_init);

        auto z() const -> const float&;
    };
}


