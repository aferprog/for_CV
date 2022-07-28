#include "EntityDistances.h"

double aca::EntityDistance::distanceEvklid(const Entity& l, const Entity& r) {
    double sum = 0;
    for (int i = 0; i < l.size(); i++)
        sum += (l[i] - r[i]) * (l[i] - r[i]);
    return sqrt(sum);
}
template <float p>
double aca::EntityDistance::distanceMinkov(const Entity& l, const Entity& r) {
    double sum = 0;
    for (int i = 0; i < l.size(); i++)
        sum += pow(fabs(l[i] - r[i]), p);
    double res = pow(sum, 1/p);
    return res;
}
double aca::EntityDistance::distanceManhet(const Entity& l, const Entity& r) {
    double sum = 0;
    for (int i = 0; i < l.size(); i++)
        sum += fabs(l[i] - r[i]);
    return sum;
}
double aca::EntityDistance::distanceChebish(const Entity& l, const Entity& r) {
    double max = 0;
    for (size_t i = 0; i < l.size(); i++) {
        double t = abs(l[i] - r[i]);
        if (t > max)
            max = t;
    }
    return max;
}