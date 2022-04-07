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
	GumboOptions opt;
	GumboOutput* output;

public:
	//template <typename T>
	void get_formated_enteties(const std::string& source_path, AferGumboNode root);

private:
	void build_entity(std::map<std::string, std::string> &enity, std::vector <AferGumboNode> format, AferGumboNode& node);
	void go_by_entity_path(AferGumboNode &format, AferGumboNode &root);
	bool find_path_element(afer_search_options format, AferGumboNode& root);
	std::vector<AferGumboNode> find_all_by_recursion(afer_search_options format, AferGumboNode& root);
	void find_all_by_recursion_help(std::vector<AferGumboNode>& res, const afer_search_options& format, AferGumboNode& node, int deep = 0);
	void open_source(const std::string& source_path);
	void close_source();
	bool check_end_of_path(AferGumboNode &temp_format);

	std::vector<AferGumboNode> find_entities_roots(AferGumboNode& format, AferGumboNode& root);
};