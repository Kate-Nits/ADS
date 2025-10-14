// Copyright 2025 Ekaterina Ushnitskaya

#include <gtest/gtest.h>
#include "../lib_stack/stack.h"

#define EPSILON 0.000001
#define TRUE 1
#define FALSE 0

TEST(TestStackLib, default_constructor_creates_empty_stack) {
	// Arrange
	Stack<int> stack;

	// Act & Assert
	EXPECT_EQ(0, stack.size());
	EXPECT_TRUE(stack.is_empty());
	EXPECT_FALSE(stack.is_full());
}

TEST(TestStackLib, constructor_with_capacity) {
	// Arrange
	size_t capacity = 10;
	Stack<int> stack(capacity);

	// Act & Assert
	EXPECT_EQ(0, stack.size());
	EXPECT_TRUE(stack.is_empty());
	EXPECT_FALSE(stack.is_full());
}

TEST(TestStackLib, copy_constructor) {
	// Arrange
	size_t capacity = 10;
	Stack<int> stack1(capacity);

	// Act
	Stack<int> stack2(stack1);

	// Assert
	EXPECT_EQ(stack1.size(), stack2.size());
	EXPECT_EQ(stack1.is_empty(), stack2.is_empty());
	EXPECT_EQ(stack1.is_full(), stack2.is_full());
}

TEST(TestStackLib, test_push_without_an_overflowing_stack) {
	// Arrange
	Stack<int> stack;

	// Act
	stack.push(10);
	stack.push(20);

	// Assert
	EXPECT_FALSE(stack.is_empty());
	EXPECT_EQ(2, stack.size());
	EXPECT_EQ(20, stack.top());
}

TEST(TestStackLib, test_push_with_an_overflowing_stack) {
	// Arrange
	Stack<int> stack(2);

	// Act
	stack.push(10);
	stack.push(20);

	// Assert
	EXPECT_ANY_THROW(stack.push(30));
}