#include "ClasterDistances.h"

aca::DistClasterFunc::DistClasterFunc(const aca::DistElementFunc* element_distance)
{
    this->element_distance = element_distance;
}

double aca::DistClasterFunc::distance_once(const Claster& l, const Claster& r)
{
    return element_distance->distance(l[0], r[0]);
}

double aca::DistClasterFunc::distance_for_elements(const Entity& l, const Entity& r)
{
    return element_distance->distance(l, r);
}

aca::ClasterDistance::AVGLinks::AVGLinks(const aca::DistElementFunc* element_distance)
    :DistClasterFunc(element_distance)
{
}

double aca::ClasterDistance::AVGLinks::distance(const Claster& l, const Claster& r)
{
    double sum = 0;
    for (const Entity& el1 : l)
        for (const Entity& el2 : r)
            sum += distance_for_elements(el1, el2);
    return sum / (l.size() * r.size());
}

aca::Entity aca::ClasterDistance::WeightCenter::avgImage(const Claster& claster)
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

aca::ClasterDistance::WeightCenter::WeightCenter(const aca::DistElementFunc* element_distance)
    :DistClasterFunc(element_distance)
{
}

double aca::ClasterDistance::WeightCenter::distance(const Claster& l, const Claster& r)
{
    return distance_for_elements(avgImage(l), avgImage(r));
}
