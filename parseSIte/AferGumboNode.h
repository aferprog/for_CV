#pragma once
#include <gumbo.h>
#include <string>
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
	std::map<std::string, std::string> getAttributes();
	bool hasAttribute(const std::string& attr);
	std::string getAttribute(const std::string& attr);
	AferGumboNode getParent() const;
	size_t getIndex_within_parent() const;
	GumboParseFlags getParse_flags() const;
	std::string getText() const;
	std::vector<AferGumboNode> getChildren() const;
	bool hasChildren() const;
	AferGumboNode& operator=(const AferGumboNode& node);
	friend std::ostream& operator<<(std::ostream &out, AferGumboNode &node);

private:
	bool checkAttributes(const std::map<std::string, std::string> &attr);
	void loadAttributes();
	std::map<std::string, std::string> *attributes = nullptr;

};
