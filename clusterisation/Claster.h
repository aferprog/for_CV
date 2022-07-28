#pragma once
#include <vector>
#include "Entity.h"
namespace aca {
    class Claster : public std::vector<Entity> {
    public:
        int getId() const;
        void unite(const Claster& claster);
    };
}
