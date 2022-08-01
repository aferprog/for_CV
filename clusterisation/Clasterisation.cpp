#include "Clasterisation.h"

aca::Clasterisation::Clasterisation(const std::vector<std::vector<double>>& data, claster_config config) //: detales(0)
{
    if (config.distance_between_clusters == nullptr)
        throw std::runtime_error("No function to count distance");
    
    max_distance = 0;
    aca::Clasterisation &res=*this;
    
    const size_t n = data.size();

    Matrix matr(config.distance_between_clusters);
    for (int i = 0; i < n; i++) {
        res.entities.push_back(Entity(i, data[i].size()));
        std::copy(data[i].begin(), data[i].end(), res.entities[i].begin());
        //en.fillRandomly();
        Claster cl;
        cl.push_back(res.entities[i]);
        matr.addEntity(cl);
    }

    while (matr.size() > 1) {
        
        std::cout << matr;

        struct { size_t i, j; } min = {0,1};

        for (size_t i=0; i+1<matr.size(); i++)
            for (size_t j = i+1; j < matr.size(); j++)
                if (matr[min.i][min.j] > matr[i][j]) {
                    min.i = i;
                    min.j = j;
                }

        main_history.push_back({
            matr.getClasters()[min.i].getId(), matr.getClasters()[min.j].getId(), matr[min.i][min.j]
            });
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
    //return detales;
    throw 1;
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
        clasters[i].push_back(entities[i]);
    }
    
    // double total_dist = 0;
    for (const UnitingRecord& rec : main_history) {
        // total_dist += rec.distance;
        if (rec.distance > distace) break;

        clasters[rec.claster_id_l].unite(clasters[rec.claster_id_r]);
        flags[rec.claster_id_r] = false;
    }

    std::vector <aca::Claster> res;
    for (size_t i = 0; i < entities.size(); i++)
        if (flags[i]) res.push_back(clasters[i]);

    return res;
}
