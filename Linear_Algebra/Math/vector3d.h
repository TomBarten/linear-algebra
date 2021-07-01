#pragma once
#include "vector2d.h"

namespace math
{
    class vector3d : public vector2d
    {
    protected:
        float z_;

    public:
        vector3d(float x, float y, float z);
    };
}


