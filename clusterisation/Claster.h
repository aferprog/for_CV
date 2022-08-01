#pragma once
#include <vector>
#include "Entity.h"
namespace aca {
    class Claster : public std::vector<Entity> {
    public:
        Claster() = default;
        size_t getId() const;
        void unite(const Claster& claster);
        void unite(Claster&& claster);
    };
}
std::ostream& operator<<(std::ostream& out, const aca::Claster& claster);