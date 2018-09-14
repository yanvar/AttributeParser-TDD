#include "pch.h"
#include <iostream>
#include"../AttributeParser/AttributeParser.h"

TEST(TestAttributeParser, HRMLIsEmpty_QueryForTag_QueryRetrurnFalse)
{
	AttributeParser aa;
	std::string query("tag1~name");
	std::string answer;
	bool is_query_exist = aa.submit_query(query, answer);

	EXPECT_FALSE(is_query_exist);
}

TEST(TestAttributeParser, HRMLIsEmpty_AddSingleTagSingleKeyThenQueryForTheKey_QueryRetrurnValue)
{
	AttributeParser aa;
	std::string line1("<tag1 value = \"Hello\">");
	std::string line2("</tag1>");
	std::string query("tag1~value");
	std::string answer;
	aa.add_tags(line1);
	aa.add_tags(line2);
	bool is_query_exsist = aa.submit_query(query, answer);

	EXPECT_TRUE(is_query_exsist);
	EXPECT_STREQ(answer.c_str(), "Hello");
}

TEST(TestAttributeParser, HRMLIsEmpty_AddSingleTagWithTwoKeysThenQueryForSecondKey_QueryRetrurnValue)
{
	AttributeParser aa;
	std::string line1("<tag1 value = \"Hello\" value2 = \"World\">");
	std::string line2("</tag1>");
	std::string query("tag1~value2");
	std::string answer;
	aa.add_tags(line1);
	aa.add_tags(line2);
	bool is_query_exsist = aa.submit_query(query, answer);

	EXPECT_TRUE(is_query_exsist);
	EXPECT_STREQ(answer.c_str(), "World");
}

TEST(TestAttributeParser, HRMLIsEmpty_AddSingleTagWithTwoKeysThenQueryForFirstKey_QueryRetrurnValue)
{
	AttributeParser aa;
	std::string line1("<tag1 value = \"Hello\" value2 = \"World\">");
	std::string line2("</tag1>");
	std::string query("tag1~value");
	std::string answer;
	aa.add_tags(line1);
	aa.add_tags(line2);
	bool is_query_exsist = aa.submit_query(query, answer);

	EXPECT_TRUE(is_query_exsist);
	EXPECT_STREQ(answer.c_str(), "Hello");
}

TEST(TestAttributeParser, HRMLIsEmpty_AddSingleTagWithTwoKeysThenQueryForMissingTag_QueryRetrurnValue)
{
	AttributeParser aa;
	std::string line1("<tag1 value = \"Hello\" value2 = \"World\">");
	std::string line2("</tag1>");
	std::string query("tag~value");
	std::string answer;
	aa.add_tags(line1);
	aa.add_tags(line2);
	bool is_query_exsist = aa.submit_query(query, answer);

	EXPECT_FALSE(is_query_exsist);
}

TEST(TestAttributeParser, HRMLWithOneTag_AddTagWithOneKeyInTheSameHirarchyAndQueryForIt_QueryRetrurnValue)
{
	AttributeParser ap;
	std::string line1("<tag1 value1 = \"Hello\" value2 = \"World\">");
	std::string line2("<tag2 value3 = \"WhatsUp\">");
	std::string line3("</tag2>");
	std::string line4("</tag1>");
	std::string query("tag1~value1");
	std::string answer;

	ap.add_tags(line1);
	ap.add_tags(line2);
	ap.add_tags(line3);
	ap.add_tags(line4);
	bool is_query_exsist = ap.submit_query(query, answer);

	EXPECT_TRUE(is_query_exsist);
	EXPECT_STREQ(answer.c_str(), "Hello");
}

TEST(TestAttributeParser, HRMLWithTwoTag_Add3rdTagWithOneKeyInTheSameHirarchyAndQueryForSecondTag_QueryRetrurnValue)
{
	AttributeParser ap;
	std::string line1("<tag1 value1 = \"Hello\" value2 = \"World\">");
	std::string line2("<tag2 value2 = \"WhatsUp\">");
	std::string line3("</tag2>");
	std::string line4("<tag3 value3 = \"Dude\">");
	std::string line5("</tag3>");
	std::string line6("</tag1>");
	std::string query("tag1.tag2~value2");
	std::string answer;

	ap.add_tags(line1);
	ap.add_tags(line2);
	ap.add_tags(line3);
	ap.add_tags(line4);
	ap.add_tags(line5);
	ap.add_tags(line6);

	bool is_query_exsist = ap.submit_query(query, answer);

	EXPECT_TRUE(is_query_exsist);
	EXPECT_STREQ(answer.c_str(), "WhatsUp");
}

TEST(TestAttributeParser, HRMLWithTwoTag_Add3rdTagWithOneKeyInTheSameHirarchyAndQueryForThirdTag_QueryRetrurnValue)
{
	AttributeParser ap;
	std::string line1("<tag1 value1 = \"Hello\" value2 = \"World\">");
	std::string line2("<tag2 value2 = \"WhatsUp\">");
	std::string line3("</tag2>");
	std::string line4("<tag3 value3 = \"Dude\">");
	std::string line5("</tag3>");
	std::string line6("</tag1>");
	std::string query("tag1.tag3~value3");
	std::string answer;

	ap.add_tags(line1);
	ap.add_tags(line2);
	ap.add_tags(line3);
	ap.add_tags(line4);
	ap.add_tags(line5);
	ap.add_tags(line6);

	bool is_query_exsist = ap.submit_query(query, answer);

	EXPECT_TRUE(is_query_exsist);
	EXPECT_STREQ(answer.c_str(), "Dude");
}

TEST(TestAttributeParser, HRMLWithTwoTag_Add3rdTagWithOneKeyInTheSameHirarchyAndQueryForFirstTag_QueryRetrurnValue)
{
	AttributeParser ap;
	std::string line1("<tag1 value1 = \"Hello\" value2 = \"World\">");
	std::string line2("<tag2 value2 = \"WhatsUp\">");
	std::string line3("</tag2>");
	std::string line4("<tag3 value3 = \"Dude\">");
	std::string line5("</tag3>");
	std::string line6("</tag1>");
	std::string query("tag1~value1");
	std::string answer;

	ap.add_tags(line1);
	ap.add_tags(line2);
	ap.add_tags(line3);
	ap.add_tags(line4);
	ap.add_tags(line5);
	ap.add_tags(line6);

	bool is_query_exsist = ap.submit_query(query, answer);

	EXPECT_TRUE(is_query_exsist);
	EXPECT_STREQ(answer.c_str(), "Hello");
}

TEST(TestAttributeParser, HRMLWithTwoTagsRootAndChild_AddCHildToTheChildWithOneKeyAndQueryForAddedTagKey_QueryRetrurnValue)
{
	AttributeParser ap;
	std::string line1("<tag1 value1 = \"Hello\" value2 = \"World\">");
	std::string line2("<tag2 value2 = \"WhatsUp\">");
	std::string line3("<tag3 value3 = \"Dude\" value4 = \"YoYo\">");
	std::string line4("</tag3>");
	std::string line5("</tag2>");
	std::string line6("</tag1>");
	std::string query("tag1.tag2.tag3~value4");
	std::string answer;

	ap.add_tags(line1);
	ap.add_tags(line2);
	ap.add_tags(line3);
	ap.add_tags(line4);
	ap.add_tags(line5);
	ap.add_tags(line6);

	bool is_query_exsist = ap.submit_query(query, answer);

	EXPECT_TRUE(is_query_exsist);
	EXPECT_STREQ(answer.c_str(), "YoYo");
}

TEST(TestAttributeParser, HRMLWithOneTag_AddTagOnNewHirarchyAndQueryForAddedTag_QueryRetrurnValue)
{
	AttributeParser ap;
	std::string line1("<tag1 value1 = \"Hello\" value2 = \"World\">");
	std::string line2("</tag1>");
	std::string line3("<tag2 value2 = \"WhatsUp\">");
	std::string line4("</tag2>");
	std::string query("tag2~value2");
	std::string answer;

	ap.add_tags(line1);
	ap.add_tags(line2);
	ap.add_tags(line3);
	ap.add_tags(line4);

	bool is_query_exsist = ap.submit_query(query, answer);

	EXPECT_TRUE(is_query_exsist);
	EXPECT_STREQ(answer.c_str(), "WhatsUp");
}

TEST(TestAttributeParser, HRMLWithThreeTags_QueryForNonEsistingTag_QueryRetrurnFalse)
{
	AttributeParser ap;
	std::string line1("<a>");
	std::string line2("<b name = \"tag_one\">");
	std::string line3("<c name = \"tag_two\" value = \"val_907\">");
	std::string line4("</c>");
	std::string line5("</b>");
	std::string line6("</a>");
	std::string query("a.b.c.d~name");
	std::string answer;

	ap.add_tags(line1);
	ap.add_tags(line2);
	ap.add_tags(line3);
	ap.add_tags(line4);
	ap.add_tags(line5);
	ap.add_tags(line6);

	bool is_query_exsist = ap.submit_query(query, answer);

	EXPECT_FALSE(is_query_exsist);
}



TEST(TestAttributeParser, HRMLWithFiveTags_QueryForNonEsistingTag_QueryRetrurnFalse)
{
	AttributeParser ap;
	std::string line1("a value = \"GoodVal\"");
	std::string line2("b value = \"BadVal\" size = \"10\"");
	std::string line3("</b>");
	std::string line4("<c height = \"auto\">");
	std::string line5("<d size = \"3\">");
	std::string line6("<e strength = \"2\">");
	std::string line7("</e>");
	std::string line8("</d>");
	std::string line9("</c>");
	std::string line10("</a>");
	std::string query("a.d.e~strength");
	std::string answer;
	ap.add_tags(line1);
	ap.add_tags(line2);
	ap.add_tags(line3);
	ap.add_tags(line4);
	ap.add_tags(line5);
	ap.add_tags(line6);
	ap.add_tags(line7);
	ap.add_tags(line8);
	ap.add_tags(line9);
	ap.add_tags(line10);

	bool is_query_exsist = ap.submit_query(query, answer);
	EXPECT_FALSE(is_query_exsist);
}




/*

a.b~size
a.b~value
a.b.c~height
a.c~height
a.d.e~strength
a.c.d.e~strength
d~sze
a.c.d~size
*/
/*
a.b~name
a.b.c~value
a.b.c~src
a.b.c.d~name
*/