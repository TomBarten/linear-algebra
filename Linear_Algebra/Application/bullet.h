#pragma once
#include "object.h"

namespace application
{
    class bullet final : public object
    {
    public:
        auto remove_on_collide(const object& other) -> bool override;
    };
}
