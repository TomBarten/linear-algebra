#include "bullet.h"

namespace application
{
    auto bullet::remove_on_collide(const object& other) -> bool
    {
        // no wall banging (:
        return true;
    }
}
