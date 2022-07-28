#pragma once
#include "Entity.h"

using DistElementFunc = double (*)(const aca::Entity&, const aca::Entity&);

namespace aca {
    class EntityDistance {
    public:
        static double distanceEvklid(const Entity& l, const Entity& r);
        static double distanceManhet(const Entity& l, const Entity& r);
        static double distanceChebish(const Entity& l, const Entity& r);
        template <float p>
        static double distanceMinkov(const Entity& l, const Entity& r);
    };
}
