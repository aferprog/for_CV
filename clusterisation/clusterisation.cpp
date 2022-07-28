#include <iostream>
#include "AferClasterisation.h"

using namespace std;

template <int x>
void test() {
    cout << x << endl;
}

int main()
{
    test<5>();
    /*const size_t LEN = 3;
    const size_t COUNT = 8;

    vector<vector<double>> data;

    for (int i = 0; i < COUNT; i++) {
        data.push_back(vector<double>());
        for (int j = 0; j < LEN; j++) {
            data[i].resize(LEN);
            cin >> data[i][j];
        }
    }

    aca::claster_config config;
    aca::EntityDistance::distanceManhet(aca::Entity(2, 2), aca::Entity(3, 2));
    aca::EntityDistance::distanceMinkov<(float)3>(aca::Entity(2, 2), aca::Entity(3, 2));
    */

    // std::cout << (size_t)(-1) << std::endl;
}