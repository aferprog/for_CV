#include <iostream>
#include "AferClasterisation.h"

using namespace std;

int main()
{
    const size_t LEN = 3;
    const size_t COUNT = 8;

    vector<vector<double>> data;

    for (int i = 0; i < COUNT; i++) {
        data.push_back(vector<double>());
        data[i].resize(LEN);
        for (int j = 0; j < LEN; j++) {
            cin >> data[i][j];
        }
    }

    aca::claster_config config;
    config.distance_between_clusters = aca::ClasterDistance::weigthCenter<aca::EntityDistance::distanceManhet>;

    aca::Clasterisation clasterisation(data, config);
    
    vector<aca::Claster> clasters = clasterisation.devide_into_clasters_fraction(0.5);

    /* 
        Working with clasters...
    */
}