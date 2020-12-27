#include "postfix.h"
#include <gtest.h>
TEST(TPostfix, can_create_postfix)
{
	ASSERT_NO_THROW(TPostfix p);
}
TEST(TPostfix, cant_create_postfix_with_bad_symbols)
{
	ASSERT_ANY_THROW(TPostfix p("a+b&c!d"));
}

TEST(TPostfix, throws_when_infix_with_spaces_only)
{
	ASSERT_ANY_THROW(TPostfix p("      "));
}

TEST(TPostfix, throws_when_operation_behind)
{
	ASSERT_ANY_THROW(TPostfix p("a-b*"));
}

TEST(TPostfix, throws_when_operation_ahead)
{
	ASSERT_ANY_THROW(TPostfix p("+a-b"));
}

TEST(TPostfix, throws_when_too_many_left_brackets)
{
	ASSERT_ANY_THROW(TPostfix p("(a+(b*c)"));
}

TEST(TPostfix, throws_when_too_many_right_brackets)
{
	ASSERT_ANY_THROW(TPostfix p("(a+(b*c))+d))"));
}

TEST(TPostfix, cant_create_postfix_with_long_names)
{
	ASSERT_ANY_THROW(TPostfix p("a+bcd"));
}

TEST(TPostfix, convert_infix_with_brackets)
{
	TPostfix p("(a+b)*c");
	p.ToPostfix();
	EXPECT_EQ(p.GetPostfix(), "ab+c*");
}

TEST(TPostfix, convert_equal_expression)
{
	TPostfix p1("(a+b)");
	p1.ToPostfix();
	TPostfix p2("a+b");
	p2.ToPostfix();
	EXPECT_EQ(p1.GetPostfix(), p2.GetPostfix());
}

TEST(TPostfix, can_create_postfix_with_a_given_string){
	ASSERT_NO_THROW(TPostfix p("a+b"));
}

TEST(TPostfix, can_get_infix){
	TPostfix p("a+b");
	cout << p.GetInfix();
	EXPECT_EQ("a+b", p.GetInfix());
}


TEST(TPostfix, can_get_operations){
	TPostfix p("a+b");
	string tmp;
	tmp = p.GetInfix();
	EXPECT_EQ(true, p.CheckOper(tmp[1]));
}

TEST(TPostfix, can_get_operand){
	TPostfix p("a+b");
	string tmp;
	tmp = p.GetInfix();
	EXPECT_EQ(false, p.CheckOper(tmp[0]));
}

TEST(TPostfix, can_get_priority){
	TPostfix p("a+b");
	string tmp;
	tmp = p.GetInfix();
	EXPECT_EQ(1, p.Priority(tmp[1]));
}

