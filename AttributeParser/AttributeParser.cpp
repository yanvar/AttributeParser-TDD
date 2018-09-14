#include "pch.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "AttributeParser.h"

#define LOG  std::cout << __FUNCTION__ << ":"  

bool AttributeParser::line_is_closing_tag(const std::string& line)
{
	if (line[1] == '/')
		return true;
	return false;
}


void AttributeParser::add_tags(const std::string& tags)
{
	std::istringstream iss(tags);
	std::vector<std::string> tokens;
	
	extract_tags_to_vector(iss, tokens);
	
	std::string open_tag = tokens[0];
	clear_unwanted_charecters(open_tag);

	if (nodes_are_uninitialized())
	{
		LOG << "Here1" << std::endl;
		initialize_node(tokens,ap_node);
		tags_stack.push_front(open_tag);
	}
	else
	{
		std::cout << __FUNCTION__ << "Here2" << std::endl;
		if (line_is_closing_tag(tags))
		{
			std::cout << __FUNCTION__ << "Here3" << std::endl;
			tags_stack.pop_front();
			current_father_node_ptr = current_father_node_ptr->parent;
		}
		else
		{
			AttributeParserNode attribute_parse_child;
			std::cout << __FUNCTION__ << "Here4" << std::endl;
			tags_stack.push_front(open_tag);
			initialize_node(tokens, attribute_parse_child, current_father_node_ptr);
			LOG << "Add to tag:" << current_father_node_ptr->open_tag << " child with tag:" << attribute_parse_child.open_tag << std::endl;
			current_father_node_ptr->child_vec.push_back(attribute_parse_child);
			current_father_node_ptr = &(current_father_node_ptr->child_vec[current_father_node_ptr->child_vec.size() - 1]);
			LOG << "Now currnt_node_ptr tag is: " << current_father_node_ptr->open_tag << std::endl;
		}
	}
	std::cout << __FUNCTION__ << " child_vec.size = " << ap_node.child_vec.size() << std::endl;
}

void AttributeParser::initialize_node(std::vector<std::string> &tokens,	AttributeParserNode &apn, AttributeParserNode* parent_ptr)
{
	apn.open_tag = tokens[0];
	apn.open_tag = apn.open_tag.substr(1); //remove "<"
	apn.parent = parent_ptr;
	unsigned int i;

	for (i = 1; i < tokens.size() - 1; i += 3)
	{
		std::string k = tokens[i];
		std::string v = tokens[i + 2];
		clear_unwanted_charecters(v);
		//std::cout << "--" << k << "->" << v << std::endl;
		AttributeParserItem item(k, v);
		apn.item_vec.push_back(item);
	}
}

void AttributeParser::extract_tags_to_vector(std::istringstream &iss, std::vector<std::string> &tokens)
{
	do
	{
		std::string subs;
		iss >> subs;
		tokens.push_back(subs);
	} while (iss);
}


void AttributeParser::clear_unwanted_charecters(std::string &k)
{
	k.erase(std::remove(k.begin(), k.end(), '/'), k.end());
	k.erase(std::remove(k.begin(), k.end(), '"'), k.end());
	k.erase(std::remove(k.begin(), k.end(), '>'), k.end());
}


AttributeParserNode* AttributeParserNode::find_node_by_tag_name(const std::string& tag_name)
{
	AttributeParserNode* node_ptr = NULL;
	unsigned int j;
	
	for (j = 0; j < child_vec.size(); ++j)
	{
//		LOG << "here!!!!" << curr_node_ptr->child_vec[j].open_tag << " : " << queried_tags_vec[i] << std::endl;
		if (child_vec[j].open_tag == tag_name)
		{
			node_ptr = &(child_vec[j]);
			break;
		}
	}
	return node_ptr;
}

bool AttributeParserNode::find_value_by_key(const std::string& key, std::string& value)
{
	unsigned int i;
	for (i = 0; i < item_vec.size(); ++i)
	{
		if (key == item_vec[i].get_key())
		{
			LOG << "Found final match, yesssss" << std::endl;
			value = item_vec[i].get_value();
			return true;
		}
	}
	return false;
}


bool AttributeParser::submit_query(const std::string& query, std::string &query_result)
{
	std::vector<std::string> queried_tags_vec;
	std::string quried_key;
	unsigned int i;
	query_result = "";

	parse_query(query, quried_key, queried_tags_vec);

	LOG << "quried_key=" << quried_key <<  std::endl;
	AttributeParserNode* curr_node_ptr = &ap_node;	
	if (queried_tags_vec[0] == ap_node.open_tag)
	{
		bool found_match = true;
		LOG << "Keep going....." << std::endl;
		for (i = 1; i < queried_tags_vec.size(); ++i)
		{
			curr_node_ptr = curr_node_ptr->find_node_by_tag_name(queried_tags_vec[i]);
			if (curr_node_ptr == NULL)
			{
				LOG << "No Match for: " << queried_tags_vec[i] << std::endl;
				found_match = false;
				break;
			}
		}
		if (found_match == false)
		{
			LOG << "No Match, retrun false" << std::endl;
			return false;
		}
		else
		{
			return curr_node_ptr->find_value_by_key(quried_key, query_result);
		}
	}
	else
		return false;
}


void AttributeParser::parse_query(const std::string & query, std::string &quried_key, std::vector<std::string> &queried_tags_vec)
{
	std::string queried_tag;
	std::size_t pos = query.find("~");
	quried_key = query.substr(pos + 1);
	queried_tag = query.substr(0, pos);;
	std::cout << "queried_tag= " << queried_tag << std::endl;


	while ((pos = queried_tag.find('.')) != std::string::npos)
	{
		std::string tag = queried_tag.substr(0, pos);
		queried_tag = queried_tag.substr(pos + 1);
		queried_tags_vec.push_back(tag);
		std::cout << "tag= " << tag << std::endl;
	}
	std::cout << "queried_tag= " << queried_tag << std::endl;
	queried_tags_vec.push_back(queried_tag);
}

