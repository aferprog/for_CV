#pragma once

#include "Entity.h"
#include "Claster.h"
#include "ClasterDistances.h"

namespace aca {
    class Matrix {
    private:
        std::vector<std::vector<double>> matrix;
        std::vector<Claster> clasters;

        DistClasterFunc distance;

    public:
        Matrix(DistClasterFunc distance);
        size_t size() const;
        const std::vector<Claster>& getClasters() const;
        void addEntity(const Claster& ent);
        void rebuild(size_t x);
        const std::vector<double>& operator[](size_t i) const;
        void unite(size_t i, size_t j);
    };
}
