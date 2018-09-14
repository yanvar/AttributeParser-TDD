#pragma once
#ifndef ATTRIBUTE_PARSER_H
#define ATTRIBUTE_PARSER_H

#include <iostream>
#include <vector>
#include <deque>

class AttributeParserItem
{
public:
	AttributeParserItem() {};
	AttributeParserItem(const std::string& k, const std::string& v)
	{
		key = k;
		value = v;
	}
	std::string get_key() { return key; }
	std::string get_value() { return value; }

private:
	std::string key;
	std::string value;
};

class AttributeParserNode
{
public:
	std::string open_tag;
//	std::string close_tag;
	std::vector<AttributeParserItem> item_vec;
	std::vector<AttributeParserNode> child_vec;
	AttributeParserNode* parent;
	AttributeParserNode* find_node_by_tag_name(const std::string& tag_name);
	bool find_value_by_key(const std::string& key, std::string& value);
};

class AttributeParser
{
public:
	AttributeParser() { num_of_ap_nodes = 0;}
	bool submit_query(const std::string& query, std::string &query_result);
	void add_tags(const std::string& tags);

private:
	void parse_query(const std::string & query, std::string &quried_key, std::vector<std::string> &queried_tags_vec);
	void clear_unwanted_charecters(std::string &k);
	void extract_tags_to_vector(std::istringstream &iss, std::vector<std::string> &tokens);
	void initialize_node(std::vector<std::string> &tokens, AttributeParserNode &apn, AttributeParserNode* parent = NULL);
	bool line_is_closing_tag(const std::string& line);
	bool nodes_are_uninitialized() { return tags_stack.empty(); }
	

	std::deque<std::string> tags_stack;
	AttributeParserNode* current_father_node_ptr;
	std::vector<AttributeParserNode> ap_node_vec;
	unsigned int num_of_ap_nodes;
};



#endif