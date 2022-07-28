#include "Claster.h"
int aca::Claster::getId() const {
    int id = (size_t)(-1);
    for (const auto& el : *this) {
        if (el.getId()< id) id = el.getId();
    }
    return id;
}
void aca::Claster::unite(const Claster& claster) {
    std::copy(claster.begin(), claster.end(), std::back_inserter(*this));
}