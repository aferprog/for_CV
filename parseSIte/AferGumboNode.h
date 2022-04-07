#pragma once
#include <gumbo.h>
#include <string_view>
#include <iostream>
#include <vector>
#include <map>
#include <memory>

class AferGumboNode {
private:
	GumboTag tag;
	GumboNodeType type;
	GumboNode* node;
	bool without_additions, simple_mode;
	

public:
	AferGumboNode(GumboNode* node, bool without_additions = false, bool simple_mode = true);
	AferGumboNode(const AferGumboNode& node);
	~AferGumboNode();
	GumboNodeType getType() const;
	GumboTag getTag() const;
	std::map<std::string_view, std::string_view> getAttributes();
	bool hasAttribute(const std::string_view& attr);
	std::string_view getAttribute(const std::string_view& attr);
	AferGumboNode getParent() const;
	size_t getIndex_within_parent() const;
	GumboParseFlags getParse_flags() const;
	std::string_view getText() const;
	std::vector<AferGumboNode> getChildren() const;
	bool hasChildren() const;
	AferGumboNode& operator=(const AferGumboNode& node);
	friend std::ostream& operator<<(std::ostream &out, AferGumboNode &node);

private:
	bool checkAttributes(const std::map<std::string_view, std::string_view> &attr);
	void loadAttributes();
	std::map<std::string_view, std::string_view> *attributes = nullptr;

};
