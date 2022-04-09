#pragma once
#include <string_view>
#include <fstream>
#include <stdexcept>
#include <gumbo.h>
#include <map>
#include <string>
#include <vector>
#include "afer_search_options.h"
#include "AferGumboNode.h"


class AferFormat{
private:
	std::vector<std::map<std::string, std::string>> temp_entities;

public:
	std::vector<std::map<std::string, std::string>> get_formated_enteties(GumboOutput* source_path, GumboOutput* root, bool not_return=false);
	std::vector<std::map<std::string, std::string>> get_formated_enteties(std::string_view format, std::string_view html_page);

private:
	void build_entity(std::map<std::string, std::string> &enity, std::vector <AferGumboNode> format, AferGumboNode& node);
	std::vector<AferGumboNode> find_all_by_recursion(afer_search_options format, AferGumboNode& root);
	void find_all_by_recursion_help(std::vector<AferGumboNode>& res, const afer_search_options& format, AferGumboNode& node, int deep = 0);
	GumboOutput* open_source(std::string_view source_path);
	void close_source(GumboOutput*);
	int count_of_parameters(AferGumboNode& format_entity_root);
	bool check_end_of_path(AferGumboNode &temp_format);

	std::vector<AferGumboNode> find_entities_roots(AferGumboNode& format, AferGumboNode& root);
};