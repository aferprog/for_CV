#pragma once
#include <gumbo.h>
#include "AferGumboNode.h"
#include <map>
#include <string>
#include <sstream>
#include <vector>

#define COUNT_OF_AFER_FLAGS 3
enum AferProperties{
	ENTITY_START,
	ENTITY_COMLATED,
	FLOAT_DEEP
};

struct afer_search_options {
	GumboTag tag;
	GumboNodeType type;
	std::map<std::string, std::string> attributes;
	// what get where write it to
	std::map<std::string, std::string> to_get;
	std::vector<char> additional_options;
	afer_search_options(AferGumboNode& node);
	bool check(AferGumboNode& node) const;
};
