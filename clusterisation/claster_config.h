#pragma once
#include "EntityDistances.h"
#include "ClasterDistances.h"
namespace aca {
	struct claster_config {
		bool safe_detales = false;
		DistElementFunc distance_between_elements = nullptr;
		DistClasterFunc distance_between_clusters = nullptr;
		float additional_parameter = 0;
	};
}