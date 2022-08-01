#pragma once
#include "Entity.h"

// using DistElementFunc = double (*)(const aca::Entity&, const aca::Entity&);

namespace aca {
    class DistElementFunc {
    public:
        virtual double distance(const Entity& l, const Entity& r) const = 0;
    };

    namespace EntityDistance {
        class Evklid : public DistElementFunc {
        public:
            virtual double distance(const Entity& l, const Entity& r) const override;
        };

        class Manhet : public DistElementFunc {
        public:
            virtual double distance(const Entity& l, const Entity& r) const  override;
        };

        class Chebish : public DistElementFunc {
        public:
            virtual double distance(const Entity& l, const Entity& r) const  override;
        };

        class Minkov : public DistElementFunc {
            float p;
        public:
            Minkov(float p);
            virtual double distance(const Entity& l, const Entity& r) const  override;
        };
    }
}