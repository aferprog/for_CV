#include "EntityDistances.h"

double aca::EntityDistance::Evklid::distance(const Entity& l, const Entity& r) const
{
    double sum = 0;
    for (int i = 0; i < l.size(); i++)
        sum += (l[i] - r[i]) * (l[i] - r[i]);
    return sqrt(sum);
}

double aca::EntityDistance::Manhet::distance(const Entity& l, const Entity& r) const
{
    double sum = 0;
    for (int i = 0; i < l.size(); i++)
        sum += fabs(l[i] - r[i]);
    return sum;
}

double aca::EntityDistance::Chebish::distance(const Entity& l, const Entity& r) const
{
    double max = 0;
    for (size_t i = 0; i < l.size(); i++) {
        double t = abs(l[i] - r[i]);
        if (t > max)
            max = t;
    }
    return max;
}

aca::EntityDistance::Minkov::Minkov(float p)
{
    this->p = p;
}

double aca::EntityDistance::Minkov::distance(const Entity& l, const Entity& r) const
{
    double sum = 0;
    for (int i = 0; i < l.size(); i++)
        sum += pow(fabs(l[i] - r[i]), p);
    double res = pow(sum, 1 / p);
    return res;
}