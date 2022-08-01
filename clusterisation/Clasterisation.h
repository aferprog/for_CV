#pragma once
#include <vector>
#include <algorithm>
#include "Claster.h"
#include "Entity.h"
#include "Matrix.h"
#include "UnitingRecord.h"
#include "claster_config.h"
namespace aca {
	class Clasterisation
	{
	private:
		double max_distance;
		std::vector<UnitingRecord> main_history;
		//std::vector<Matrix> detales;
		std::vector<Entity> entities;
	public:
		Clasterisation(const std::vector<std::vector<double>>& data, claster_config config);
		const std::vector<UnitingRecord>& get_result();
		const std::vector<Matrix>& get_detales();
		const std::vector<Entity>& get_entities();
		double get_max_distance();
		std::vector <Claster> devide_into_clasters_fraction(float fraction);
		std::vector <Claster> devide_into_clasters_distance(double distace);
	};
}