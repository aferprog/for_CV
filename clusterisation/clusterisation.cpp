#include <iostream>
#include "AferClasterisation.h"

using namespace std;

int main()
{
    constexpr size_t LEN = 3;
    constexpr size_t COUNT = 7;

    vector<vector<double>> data;

    for (int i = 0; i < COUNT; i++) {
        data.push_back(vector<double>());
        data[i].resize(LEN);
        for (int j = 0; j < LEN; j++) {
            cin >> data[i][j];
            cout << data[i][j]<< endl;
        }
        cout << endl;
    }

    aca::claster_config config;
    config.distance_between_clusters = new aca::ClasterDistance::AVGLinks(new aca::EntityDistance::Manhet());

    aca::Clasterisation clasterisation(data, config);
    
    for (const aca::UnitingRecord& el : clasterisation.get_result()) {
        printf("(%lu; %lu) = %.3lf\n", el.claster_id_l+1, el.claster_id_r+1, el.distance);
    }

    for (const auto& clast : clasterisation.devide_into_clasters_distance(200)) {
        cout<<clast<<endl;
    }

    // vector<aca::Claster> clasters = clasterisation.devide_into_clasters_fraction(0.5);

    /* 
        Working with clasters...
    */
}