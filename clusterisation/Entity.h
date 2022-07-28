#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <stdexcept>
namespace aca {
    class Entity : public std::vector<double>
    {
    private:
        size_t id = -1;
    public:
        Entity(size_t id, size_t size);
        size_t getId() const;
        void setId(size_t new_id);
    };
    
}

std::istream& operator>>(std::istream& in, aca::Entity& ent);
std::ostream& operator<<(std::ostream& out, const aca::Entity& ent);