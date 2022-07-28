#include "Clasterisation.h"

aca::Clasterisation::Clasterisation(const std::vector<std::vector<double>>& data, claster_config config)
{
    if (config.distance_between_clusters == nullptr)
        throw std::runtime_error("No function to count distance");
    
    max_distance = 0;
    detales.assign(0, 0);
    aca::Clasterisation &res=*this;
    
    const size_t n = data.size();

    Matrix matr(config.distance_between_clusters);
    for (int i = 0; i < n; i++) {
        res.entities.push_back(Entity(i, data[0].size()));
        //en.fillRandomly();
        Claster cl;
        cl.push_back(res.entities[0]);
        matr.addEntity(cl);
    }

    while (matr.size() > 1) {
        
        struct { size_t i, j; } min = {0,1};

        for (size_t i=0; i+1<matr.size(); i++)
            for (size_t j = i+1; j < matr.size(); j++)
                if (matr[min.i][min.j] > matr[i][j]) {
                    min.i = i;
                    min.j = j;
                }

        main_history.push_back({min.i, min.j, matr[min.i][min.j]});

        /*for (const auto& el : matr.getClasters()[min.first])
            std::cout << "----" << el << std::endl;
        for (const auto& el : matr.getClasters()[min.second])
            std::cout << "----" << el << std::endl;*/

        matr.unite(min.i, min.j);
    }
    max_distance = main_history[main_history.size() - 1].distance;

}
const std::vector<aca::UnitingRecord>& aca::Clasterisation::get_result()
{
    return main_history;
}

const std::vector<aca::Matrix>& aca::Clasterisation::get_detales()
{
    return detales;
}

const std::vector<aca::Entity>& aca::Clasterisation::get_entities()
{
    return entities;
}

double aca::Clasterisation::get_max_distance()
{
    return max_distance;
}

std::vector <aca::Claster> aca::Clasterisation::devide_into_clasters_fraction(float fraction)
{
    if (fraction < 0 || fraction>1) throw std::runtime_error("Incorrect fraction");
    return devide_into_clasters_distance(max_distance*fraction);
}

std::vector <aca::Claster> aca::Clasterisation::devide_into_clasters_distance(double distace)
{
    std::vector <aca::Claster> clasters(entities.size());
    std::vector <bool> flags(entities.size());

    for (size_t i = 0; i < entities.size(); i++) {
        flags[i] = true;
    }
    
    double total_dist = 0;
    for (const UnitingRecord& rec : main_history) {
        total_dist += rec.distance;
        if (total_dist > distace) break;

        clasters[rec.claster_id_l].unite(clasters[rec.claster_id_r]);
        flags[rec.claster_id_r] = false;
    }

    std::vector <aca::Claster> res;
    for (size_t i = 0; i < entities.size(); i++)
        if (flags[i]) res.push_back(clasters[i]);

    return res;
}
