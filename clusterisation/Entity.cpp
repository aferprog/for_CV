#include "Entity.h"



aca::Entity::Entity(size_t id, size_t size) 
    :id(id) {
    assign(size, 0);
}

size_t aca::Entity::getId() const
{
	return id;
}

void aca::Entity::setId(size_t new_id)
{
	id = new_id;
}

std::istream& operator>>(std::istream& in, aca::Entity& ent) {
    for (int i = 0; i < ent.size(); ++i)
        in >> ent[i];
    return in;
}
std::ostream& operator<<(std::ostream& out, const aca::Entity& ent) {
    //if (ent.size() == 0) {
    //    //char msg[50] = "Empty entity with id ";
    //    throw std::exception("Empty entity");
    //}
    out << ent.getId()<<':';
    out << '(';
    if (ent.size() > 0) {
        for (int i = 0; i < ent.size() - 1; ++i)
            out << std::setprecision(3) << ent[i] << ' ';
        out << std::setprecision(3) << ent[ent.size() - 1] << ' ';
    }
    out << ')';
    return out;
}