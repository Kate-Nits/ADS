// Copyright 2025 Ekaterina Ushnitskaya

#include <gtest/gtest.h>
#include "../lib_stack_list/stack_list.h"

#define EPSILON 0.000001
#define TRUE 1
#define FALSE 0

TEST(TestStackListLib, default_constructor_creates_empty_stack) {
	// Arrange
	StackList<int> stack;

	// Act & Assert
	EXPECT_EQ(0, stack.count());
	EXPECT_EQ(StackList<int>::RESERVE_MEMORY, stack.capacity());
	EXPECT_TRUE(stack.is_empty());
	EXPECT_FALSE(stack.is_full());
}

TEST(TestStackListLib, constructor_with_capacity) {
	// Arrange
	size_t capacity = 10;
	StackList<int> stack(capacity);

	// Act & Assert
	EXPECT_EQ(0, stack.count());
	EXPECT_EQ(capacity, stack.capacity());
	EXPECT_TRUE(stack.is_empty());
	EXPECT_FALSE(stack.is_full());
}

TEST(TestStackListLib, copy_constructor) {
	// Arrange
	size_t capacity = 10;
	StackList<int> stack1(capacity);
	stack1.push(10);
	stack1.push(20);

	// Act
	StackList<int> stack2(stack1);

	// Assert
	EXPECT_EQ(stack1.count(), stack2.count());
	EXPECT_EQ(stack1.capacity(), stack2.capacity());
	EXPECT_EQ(stack1.is_empty(), stack2.is_empty());
	EXPECT_EQ(stack1.is_full(), stack2.is_full());
}

TEST(TestStackListLib, test_push_and_top_without_an_overflowing_stack) {
	// Arrange
	StackList<int> stack;

	// Act
	stack.push(10);
	stack.push(20);

	// Assert
	EXPECT_FALSE(stack.is_empty());
	EXPECT_EQ(2, stack.count());
	EXPECT_EQ(20, stack.top());
}

TEST(TestStackListLib, test_push_with_an_overflowing_stack) {
	// Arrange
	StackList<int> stack(2);

	// Act
	stack.push(10);
	stack.push(20);

	// Assert
	EXPECT_TRUE(stack.is_full());
	EXPECT_ANY_THROW(stack.push(30));
}

TEST(TestStackListLib, test_top_with_empty_stack) {
	// Arrange
	StackList<int> stack;

	// Act & Assert
	EXPECT_TRUE(stack.is_empty());
	EXPECT_ANY_THROW(stack.top());
}

TEST(TestStackListLib, test_pop_not_all_elements_in_stack_and_top_without_an_underflowing_stack) {
	// Arrange
	StackList<int> stack;
	stack.push(1);
	stack.push(2);
	stack.push(3);

	// Act
	stack.pop();

	// Assert
	EXPECT_FALSE(stack.is_empty());
	EXPECT_EQ(2, stack.count());
	EXPECT_EQ(2, stack.top());
}

TEST(TestStackListLib, test_pop_all_elements_in_stack_and_top_without_an_underflowing_stack) {
	// Arrange
	StackList<int> stack;
	stack.push(1);

	// Act
	stack.pop();

	// Assert
	EXPECT_TRUE(stack.is_empty());
	EXPECT_EQ(0, stack.count());
	EXPECT_ANY_THROW(stack.top());
}

TEST(TestStackListLib, test_pop_with_an_underflowing_stack) {
	// Arrange
	StackList<int> stack;

	// Act & Assert
	EXPECT_TRUE(stack.is_empty());
	EXPECT_ANY_THROW(stack.pop());
}

TEST(TestStackListLib, test_clear) {
	// Arrange
	StackList<int> stack;
	stack.push(1);
	stack.push(2);
	stack.push(3);

	// Act
	stack.clear();

	// Assert
	EXPECT_TRUE(stack.is_empty());
	EXPECT_EQ(0, stack.count());
	EXPECT_ANY_THROW(stack.top());
	EXPECT_NO_THROW(stack.push(10));
}

TEST(TestStackListLib, test_is_full_checking_for_a_full_stack) {
	// Arrange
	StackList<int> stack(3);
	stack.push(1);
	stack.push(2);
	stack.push(3);

	// Act & Assert
	EXPECT_TRUE(stack.is_full());
	EXPECT_ANY_THROW(stack.push(4));
}

TEST(TestStackListLib, test_is_full_checking_for_an_empty_stack) {
	// Arrange
	StackList<int> stack(3);

	// Act & Assert
	EXPECT_FALSE(stack.is_full());
	EXPECT_ANY_THROW(stack.pop());
}

TEST(TestStackListLib, test_is_empty_checking_for_a_full_stack) {
	// Arrange
	StackList<int> stack(3);
	stack.push(1);
	stack.push(2);
	stack.push(3);

	// Act & Assert
	EXPECT_FALSE(stack.is_empty());
	EXPECT_ANY_THROW(stack.push(4));
}

TEST(TestStackListLib, test_is_empty_checking_for_an_empty_stack) {
	// Arrange
	StackList<int> stack(3);

	// Act & Assert
	EXPECT_TRUE(stack.is_empty());
	EXPECT_ANY_THROW(stack.pop());
}