#include "Claster.h"

size_t aca::Claster::getId() const {
    size_t id = (size_t)(-1);
    for (const auto& el : *this) {
        if (el.getId()< id) id = el.getId();
    }
    return id;
}
void aca::Claster::unite(const Claster& claster) {
    std::copy(claster.begin(), claster.end(), std::back_inserter(*this));
}
std::ostream& operator<<(std::ostream& out, const aca::Claster& claster) {
    for (int i = 0; i < claster.size(); ++i)
        out << claster[i] << ' ';
    return out;
}