#pragma once
#include <memory>
#include "Claster.h"
#include "EntityDistances.h"

using DistClasterFunc = double (*)(const aca::Claster&, const aca::Claster&);

namespace aca {

    class DistClasterFunc {
        std::shared_ptr<const aca::DistElementFunc> element_distance;
    public:
        DistClasterFunc(const std::shared_ptr<const aca::DistElementFunc> element_distance);
        virtual double distance_once(const Claster& l, const Claster& r) const;
        virtual double distance_for_elements(const Entity& l, const Entity& r) const;
        virtual double distance(const Claster& l, const Claster& r) const = 0;
    };

    namespace ClasterDistance {
        class AVGLinks : public DistClasterFunc {
        public:
            AVGLinks(const std::shared_ptr<const aca::DistElementFunc> element_distance);
            virtual double distance(const Claster& l, const Claster& r) const override;
        };

        class WeightCenter : public DistClasterFunc {
        private:
            aca::Entity avgImage(const Claster& claster) const;
        public:
            WeightCenter(const std::shared_ptr<const aca::DistElementFunc> element_distance);
            virtual double distance(const Claster& l, const Claster& r) const override;
        };
    }

    //class ClasterDistance {
    //private:
    //    template <DistElementFunc distance>
    //    static double ClasterAsElementDistance(const Claster& l, const Claster& r);
    //    static Entity avgImage(const Claster& claster);

    //public:
    //    template <DistElementFunc distance>
    //    static double weigthCenter(const Claster& l, const Claster& r);

    //    template <DistElementFunc distance>
    //    static double avgLinks(const Claster& l, const Claster& r);
    //    /*double closest_manhet(const Claster& l, const Claster& r) {
    //        if (l.size() == 0 || r.size() == 0)
    //            throw std::runtime_error("there is empty claster");

    //        Matrix matr(distanceManhet);
    //        for (const Entity& el : l) {
    //            Claster t;
    //            t.push_back(el);
    //            matr.addEntity(t);
    //        }
    //        for (const Entity& el : r) {
    //            Claster t;
    //            t.push_back(el);
    //            matr.addEntity(t);
    //        };

    //        int mini = l.size();
    //        int minj = 0;
    //        double min = matr[l.size()][0];
    //        for (int i = l.size(); i < matr.size(); i++)
    //            for (int j = 0; j < l.size(); j++)
    //                if (matr[i][j] < min) {
    //                    mini = i;
    //                    minj = j;
    //                    min = matr[i][j];
    //                }

    //        printf("%i/%i = %i/%i = %.0lf\n", r.getId(), l.getId(), matr.getClasters()[mini].getId(), matr.getClasters()[minj].getId(), min);
    //        return min;
    //    }
    //    double farest_evkl(const Claster& l, const Claster& r) {
    //        if (l.size() == 0 || r.size() == 0)
    //            throw std::runtime_error("there is empty claster");

    //        Matrix matr(distanceEvklid);
    //        for (const Entity& el : l) {
    //            Claster t;
    //            t.push_back(el);
    //            matr.addEntity(t);
    //        }
    //        for (const Entity& el : r) {
    //            Claster t;
    //            t.push_back(el);
    //            matr.addEntity(t);
    //        };

    //        double max = matr[l.size()][0];
    //        for (int i = l.size(); i < matr.size(); i++)
    //            for (int j = 0; j < l.size(); j++)
    //                if (matr[i][j] > max)
    //                    max = matr[i][j];
    //        return max;
    //    }*/

    //};
}