#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length){
ASSERT_NO_THROW(TStack<int> st(10));
}

TEST(TStack, throws_when_create_stack_with_negative_length){
	ASSERT_ANY_THROW(TStack<int> st(-10));
}

TEST(TStack, cannot_create_too_large_stack){
	ASSERT_ANY_THROW(TStack<int> st(MaxStackSize + 1));
}

TEST(TStack, cannot_pop_when_stack_is_empty) {
	TStack <int> st(10);
	ASSERT_ANY_THROW(st.Pop());
}

TEST(TStack, can_create_copied_stack){
	TStack<int> st(10);
	ASSERT_NO_THROW(TStack<int> st1(st));
}

TEST(TStack, copied_stack_has_its_own_memory){
	TStack<int> st0(4);
	TStack<int> st1(st0);
	st1.Push(4);
	st0.Push(8);
	EXPECT_NE(st0.Get(), st1.Get());
}

TEST(TStack, cannot_push_when_stack_is_full) {
	TStack<int> st(10);
	for (int i = 0; i < 10; i++) {
		st.Push(i);
	}
	ASSERT_ANY_THROW(st.Push(11));
}

TEST(TSack, can_push_and_pop_element) {
	TStack <int> st(10);
	st.Push(11);
	EXPECT_EQ(11, st.Pop());
}
TEST(TStack, throws_when_add_element_to_full_stack){
	TStack<int> st(1);
	st.Push(1);
	ASSERT_ANY_THROW(st.Push(1));
}

TEST(TStack, can_add_and_get_element){
	TStack<int> st(4);
	st.Push(5);
	EXPECT_EQ(5, st.Get());
}

TEST(TStack, throws_when_full_stack){
	TStack<int> st(1);
	st.Push(1);
	EXPECT_EQ(true, st.Full());
}

TEST(TStack, EMPTY_is_right) {
	TStack<int> st(2);
	EXPECT_EQ(st.Empty(), true);
	st.Push(1);
	EXPECT_EQ(st.Empty(), false);
}
TEST(TStack, FUUL_is_right) {
	TStack<int> st(2);
	EXPECT_EQ(st.Full(), false);
	for (int i = 0; i < 2; i++) {
		st.Push(i);
	}
	EXPECT_EQ(st.Full(), true);
}

TEST(TStack, can_delete_and_get_element) {
	TStack<int> st(4);
	st.Push(5);
	EXPECT_EQ(5, st.Pop());
}

TEST(TStack, throws_when_delete_element_from_empty_stack) {
	TStack<int> st(1);
	ASSERT_ANY_THROW(st.Pop());
}