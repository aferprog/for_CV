#pragma once
#include "EntityDistances.h"
#include "ClasterDistances.h"
namespace aca {
	struct claster_config {
		bool safe_detales = false;
		DistClasterFunc *distance_between_clusters = nullptr;
		float additional_parameter = 0;
	};
}