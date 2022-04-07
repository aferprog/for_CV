#include "AferFormat.h"
#include <algorithm>
#include <iostream>

bool AferFormat::find_path_element(afer_search_options format, AferGumboNode& root) {

    if (format.check(root)) return true;

    // vector of vectors with nodes, wich must be checked
    std::vector<std::vector<AferGumboNode>> vect0 = { root.getChildren() };
    std::vector<std::vector<AferGumboNode>> vect1;


    auto* temp_vect = &vect0;
    auto* next_vect = &vect1;

    while (temp_vect->size()>0) {
        for (auto& vect : *temp_vect)
            for (auto& node : vect) {
                if (format.check(node)) {
                    root = node;
                    afer_search_options test(root);
                    return true;
                }
                else if (node.hasChildren())
                    next_vect->push_back(node.getChildren());
            }

        std::swap(temp_vect, next_vect);
        next_vect->clear();
    }
}

void AferFormat::find_all_by_recursion_help(std::vector<AferGumboNode>& res, const afer_search_options& format, AferGumboNode& node, int deep) {
    /*for (int i = 0; i < deep; ++i)
        std::cout << "  ";
    std::cout << node << std::endl;*/
    if (format.check(node)) res.push_back(node);
    else {
        for (auto& el : node.getChildren())
            find_all_by_recursion_help(res, format, el, deep+1);
    }
}

std::vector<AferGumboNode> AferFormat::find_all_by_recursion(afer_search_options format, AferGumboNode& root)
{
    std::vector<AferGumboNode> res;
    find_all_by_recursion_help(res, format, root);
    return res;
}

void AferFormat::build_entity(std::map<std::string, std::string>& entity, std::vector<AferGumboNode> whatFind, AferGumboNode& node)
{
    bool is_node_found = false;
    for (auto& format : whatFind) {
        afer_search_options opt(format);
        if (opt.check(node)) {
            is_node_found = true;
            switch (opt.type)
            {
            case GumboNodeType::GUMBO_NODE_TEXT:
                if (opt.type == GumboNodeType::GUMBO_NODE_TEXT) {
                    if (opt.to_get.size() > 0) {
                        std::string key(opt.to_get["text"]);
                        entity[key] = node.getText();
                    }
                }
                break;
            case GumboNodeType::GUMBO_NODE_ELEMENT:
                for (auto& el : opt.to_get) {
                    entity[std::string(el.second)] = std::string(node.getAttribute(el.first));
                }
                for (auto& child : node.getChildren()) {
                    auto children = format.getChildren();
                    build_entity(entity, children, child);
                }
                break;
            default:
                throw std::runtime_error("MISTIKA. YA NE ZNAU, CHTO PROIZOSHLO");
            }

            break;
        }
    }
    if (!is_node_found) {
        for (auto& child : node.getChildren())
            build_entity(entity, whatFind, child);
    }
}

void AferFormat::go_by_entity_path(AferGumboNode &format, AferGumboNode &root)
{
    while (!check_end_of_path(format)) {
        if (find_path_element(format, root)) {
            auto t= format.getChildren();
            format = t[0];
        }
        else throw std::runtime_error("Not found path to root of entyties");
    }

}

void AferFormat::open_source(const std::string& source_path)
{
    std::ifstream in(&source_path[0], std::ios::in | std::ios::binary);
    if (!in) {
        throw std::invalid_argument("Can't find the source-file with name '"+ std::string(source_path)+"'");
    }

    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();

    opt = kGumboDefaultOptions;

    output = gumbo_parse_with_options(
        &kGumboDefaultOptions, contents.data(), contents.length());
}
void AferFormat::close_source()
{
    gumbo_destroy_output(&opt, output);
}

bool AferFormat::check_end_of_path(AferGumboNode& format)
{
    afer_search_options opt(format);
    if (opt.additional_options[AferProperties::ENTITY_START] == 1)
        return true;

    auto children = format.getChildren();
    if (children.size() != 1) {
        std::cout << format;
        throw std::runtime_error("Wrong path to enities: every node in path must have only one child.");
    }
    return false;

}

std::vector<AferGumboNode> AferFormat::find_entities_roots(AferGumboNode& format, AferGumboNode& root)
{
    std::vector<AferGumboNode> vect0 = { root };
    std::vector<AferGumboNode> vect1;


    auto* temp_vect = &vect0;
    auto* next_vect = &vect1;

    while (!check_end_of_path(format)) {
        
        for (auto& node : *temp_vect) {
            auto temp_roots = find_all_by_recursion(format, root);
            next_vect->insert(next_vect->end(), temp_roots.begin(), temp_roots.end());
        }

        std::swap(temp_vect, next_vect);
        next_vect->clear();
    }
    for (auto& node : *temp_vect) {
        auto temp_roots = find_all_by_recursion(format, root);
        next_vect->insert(next_vect->end(), temp_roots.begin(), temp_roots.end());
    }
    return *next_vect;
}

void AferFormat::get_formated_enteties(const std::string& source_path, AferGumboNode root)
{

    open_source(source_path);
    
    AferGumboNode format_root(output->root, true);
    go_by_entity_path(format_root, root);
    // find_all_by_recursion(format_root, root);
    //std::vector<AferGumboNode> entities = find_entities_roots(format_root, root);
    std::vector<AferGumboNode> entities = find_all_by_recursion(format_root, root);
    std::cout << format_root<< std::endl;
    std::cout << root<< std::endl<< std::endl;
    std::cout << entities.size()<<"\n";

    temp_entities.resize(entities.size());
    for (int i = 0; i < entities.size(); ++i)
        build_entity(temp_entities[i], { format_root }, entities[i]);
    
    for (auto& ent : temp_entities) {
        for (auto& pair : ent) {
            std::cout << pair.first << " = " << pair.second << std::endl;
        }
        std::cout << std::endl;
    }

    close_source();
}
