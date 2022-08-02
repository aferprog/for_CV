#pragma once
#include "EntityDistances.h"
#include "ClasterDistances.h"
namespace aca {
	struct claster_config {
		// bool safe_detales = false;
		std::shared_ptr<DistClasterFunc> distance_between_clusters;
		// float additional_parameter = 0;
	};
}