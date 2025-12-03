// Copyright 2025 Ekaterina Ushnitskaya

#include <gtest/gtest.h>
#include "../lib_queue/queue.h"

#define EPSILON 0.000001
#define TRUE 1
#define FALSE 0

TEST(TestQueueLib, default_constructor_creates_empty_queue) {
	// Arrange
	Queue<int> queue;

	// Act & Assert
	EXPECT_TRUE(queue.is_empty());
	EXPECT_FALSE(queue.is_full());
	EXPECT_EQ(0, queue.size());
	EXPECT_EQ(Queue<int>::RESERVE_MEMORY, queue.capacity());
}

TEST(TestQueueLib, constructor_with_size) {
	// Arrange
	size_t size = 10;
	Queue<int> queue(size);

	// Act & Assert
	EXPECT_EQ(size, queue.capacity());
	EXPECT_TRUE(queue.is_empty());
	EXPECT_FALSE(queue.is_full());
}

TEST(TestQueueLib, copy_constructor_without_difficulties) {
	// Arrange
	size_t size = 10;
	Queue<int> queue1(size);

	// Act
	Queue<int> queue2(queue1);

	// Assert
	EXPECT_EQ(queue1.size(), queue2.size());
	EXPECT_EQ(queue1.is_empty(), queue2.is_empty());
	EXPECT_EQ(queue1.is_full(), queue2.is_full());
}

TEST(TestQueueLib, copy_constructor_with_overflow_head_and_tail) {
	// Arrange
	Queue<int> queue1(3);

	// Act
	queue1.push(1);
	queue1.push(2);
	queue1.push(3);
	queue1.pop();
	queue1.push(4);
	Queue<int> queue2(queue1);

	// Assert
	EXPECT_EQ(queue1.size(), queue2.size());
	EXPECT_EQ(queue1.head(), queue2.head());
	EXPECT_EQ(queue1.tail(), queue2.tail());
}

TEST(TestQueueLib, test_push_and_check_head_and_tail_without_an_overflowing_queue) {
	// Arrange
	Queue<int> queue;

	// Act
	queue.push(10);
	queue.push(20);
	queue.push(30);

	// Assert
	EXPECT_EQ(3, queue.size());
	EXPECT_EQ(10, queue.head());
	EXPECT_EQ(30, queue.tail());
	EXPECT_FALSE(queue.is_empty());
}

TEST(TestQueueLib, test_push_and_check_head_and_tail_with_an_overflowing_queue) {
	// Arrange
	Queue<int> queue(3);

	// Act
	queue.push(10);
	queue.push(20);
	queue.push(30);

	// Assert
	EXPECT_ANY_THROW(queue.push(40));
}

TEST(TestQueueLib, test_pop_without_an_underflowing_queue) {
	// Arrange
	Queue<int> queue;
	queue.push(1);
	queue.push(2);
	queue.push(3);

	// Act
	queue.pop();

	// Assert
	EXPECT_FALSE(queue.is_empty());
	EXPECT_EQ(2, queue.size());
	EXPECT_EQ(2, queue.head());
	EXPECT_EQ(3, queue.tail());
}

TEST(TestQueueLib, test_pop_all_elements_in_queue_without_an_underflowing_stack) {
	// Arrange
	Queue<int> queue;
	queue.push(1);

	// Act
	queue.pop();

	// Assert
	EXPECT_TRUE(queue.is_empty());
	EXPECT_EQ(0, queue.size());
}

TEST(TestQueueLib, test_pop_with_an_underflowing_queue) {
	// Arrange
	Queue<int> queue;

	// Act & Assert
	EXPECT_TRUE(queue.is_empty());
	EXPECT_ANY_THROW(queue.pop());
}

TEST(TestQueueLib, test_clear) {
	// Arrange
	Queue<int> queue;
	queue.push(1);
	queue.push(2);

	// Act
	queue.clear();

	// Assert
	EXPECT_TRUE(queue.is_empty());
	EXPECT_EQ(0, queue.size());
}

TEST(TestQueueLib, test_is_full_checking_for_a_full_queue) {
	// Arrange
	Queue<int> queue(3);
	queue.push(1);
	queue.push(2);
	queue.push(3);

	// Act & Assert
	EXPECT_TRUE(queue.is_full());
	EXPECT_ANY_THROW(queue.push(4));
}

TEST(TestQueueLib, test_is_full_checking_for_an_empty_queue) {
	// Arrange
	Queue<int> queue(3);

	// Act & Assert
	EXPECT_FALSE(queue.is_full());
	EXPECT_ANY_THROW(queue.pop());
}

TEST(TestQueueLib, test_is_empty_checking_for_a_full_queue) {
	// Arrange
	Queue<int> queue(3);
	queue.push(1);
	queue.push(2);
	queue.push(3);

	// Act & Assert
	EXPECT_FALSE(queue.is_empty());
	EXPECT_ANY_THROW(queue.push(4));
}

TEST(TestQueueLib, test_is_empty_checking_for_an_empty_queue) {
	// Arrange
	Queue<int> queue(3);

	// Act & Assert
	EXPECT_TRUE(queue.is_empty());
	EXPECT_ANY_THROW(queue.pop());
}

TEST(TestQueueLib, test_push_after_overflow_tail) {
	// Arrange
	Queue<int> queue(3);

	// Act
	queue.push(1);
	queue.push(2);
	queue.pop();
	queue.pop();
	queue.push(100);
	queue.push(200);

	// Assert
	EXPECT_EQ(2, queue.size());
	EXPECT_EQ(100, queue.head());
	EXPECT_EQ(200, queue.tail());
}

TEST(TestQueueLib, test_push_after_overflow_head) {
	// Arrange
	Queue<int> queue(3);

	// Act
	queue.push(1);
	queue.push(2);
	queue.push(3);
	queue.pop();
	queue.push(555);

	// Assert
	EXPECT_EQ(3, queue.size());
	EXPECT_EQ(2, queue.head());
	EXPECT_EQ(555, queue.tail());
}