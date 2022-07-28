#include "ClasterDistances.h"

aca::Entity aca::ClasterDistance::avgImage(const Claster& claster)
{
    const size_t ENTITY_LENGHT = claster[0].size();
    Entity res(claster.getId(), ENTITY_LENGHT);

    for (const Entity& ent : claster) {
        for (size_t i = 0; i < ENTITY_LENGHT; i++) {
            res[i] += ent[i];
        }
    }
    for (size_t i = 0; i < ENTITY_LENGHT; i++)
        res[i] /= claster.size();
    return res;
}

template<DistElementFunc distance>
double aca::ClasterDistance::ClasterAsElementDistance(const Claster& l, const Claster& r)
{
    return distance(l[0], r[0]);
}

template <DistElementFunc distance>
double aca::ClasterDistance::weigthCenter(const Claster& l, const Claster& r) {
    return distance(avgImage(l), avgImage(r));
}

template <DistElementFunc distance>
double aca::ClasterDistance::avgLinks(const Claster& l, const Claster& r) {
    double sum = 0;
    for (const Entity& el1 : l)
        for (const Entity& el2 : r)
            sum += distance(el1, el2);
    return sum / (l.size() + r.size());
}