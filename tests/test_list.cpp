// Copyright 2025 Ekaterina Ushnitskaya

#include <gtest/gtest.h>
#include "../lib_list/list.h"

#define EPSILON 0.000001
#define TRUE 1
#define FALSE 0

TEST(TestListLib, default_constructor) {
	// Arrange & Act
	List<int> list;

	// Assert
	EXPECT_EQ(nullptr, list.head());
	EXPECT_EQ(nullptr, list.tail());
	EXPECT_TRUE(list.is_empty());
}

TEST(TestListLib, copy_constructor_with_empty_list) {
	// Arrange
	List<int> list1;

	// Act
	List<int> list2(list1);

	// Assert
	EXPECT_TRUE(list2.is_empty());
	EXPECT_EQ(list1.head(), list2.head());
	EXPECT_EQ(list1.tail(), list2.tail());
	EXPECT_EQ(nullptr, list2.head());
	EXPECT_EQ(nullptr, list2.tail());
}

TEST(TestListLib, copy_constructor_with_not_empty_list) {
	// Arrange
	List<int> list1;
	list1.push_back(1);
	list1.push_back(2);
	list1.push_back(3);

	// Act
	List<int> list2(list1);

	// Assert
	EXPECT_FALSE(list2.is_empty());
	EXPECT_EQ(list1.head()->value, list2.head()->value);
	EXPECT_EQ(list1.tail()->value, list2.tail()->value);
	EXPECT_EQ(1, list2.head()->value);
	EXPECT_EQ(3, list2.tail()->value);
}

TEST(TestListLib, push_front_to_empty_list_one_element) {
	// Arrange
	List<int> list;

	// Act
	list.push_front(678);

	// Assert
	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ(678, list.head()->value);
	EXPECT_EQ(678, list.tail()->value);
	EXPECT_EQ(list.head(), list.tail());
}

TEST(TestListLib, push_front_to_empty_list_multiple_elements) {
	// Arrange
	List<int> list;

	// Act
	list.push_front(1);
	list.push_front(2);
	list.push_front(3);

	// Assert
	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ(3, list.head()->value);
	EXPECT_EQ(1, list.tail()->value);
	Node<int>* cur = list.head();
	EXPECT_EQ(3, cur->value);
	cur = cur->next;
	EXPECT_EQ(2, cur->value);
	cur = cur->next;
	EXPECT_EQ(1, cur->value);
	EXPECT_EQ(nullptr, cur->next);
}

TEST(TestListLib, push_back_to_empty_list_one_element) {
	// Arrange
	List<int> list;

	// Act
	list.push_back(678);

	// Assert
	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ(678, list.head()->value);
	EXPECT_EQ(678, list.tail()->value);
	EXPECT_EQ(list.head(), list.tail());
}

TEST(TestListLib, push_back_to_empty_list_multiple_elements) {
	// Arrange
	List<int> list;

	// Act
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	// Assert
	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ(1, list.head()->value);
	EXPECT_EQ(3, list.tail()->value);
	Node<int>* cur = list.head();
	EXPECT_EQ(1, cur->value);
	cur = cur->next;
	EXPECT_EQ(2, cur->value);
	cur = cur->next;
	EXPECT_EQ(3, cur->value);
	EXPECT_EQ(nullptr, cur->next);
}

TEST(TestListLib, insert_with_position_at_beginning) {
	// Arrange
	List<int> list;
	list.push_back(2);
	list.push_back(3);

	// Act
	list.insert((size_t)0, 345);

	// Assert
	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ(345, list.head()->value);
	EXPECT_EQ(2, list.head()->next->value);
	EXPECT_EQ(3, list.tail()->value);
}

TEST(TestListLib, insert_with_position_in_middle) {
	// Arrange
	List<int> list;
	list.push_back(1);
	list.push_back(3);
	list.push_back(4);

	// Act
	list.insert((size_t)1, 2);

	// Assert
	EXPECT_FALSE(list.is_empty());
	Node<int>* cur = list.head();
	EXPECT_EQ(1, cur->value);
	cur = cur->next;
	EXPECT_EQ(2, cur->value);
	cur = cur->next;
	EXPECT_EQ(3, cur->value);
	cur = cur->next;
	EXPECT_EQ(4, cur->value);
	EXPECT_EQ(nullptr, cur->next);
}

TEST(TestListLib, insert_with_position_at_end) {
	// Arrange
	List<int> list;
	list.push_back(1);
	list.push_back(2);

	// Act
	list.insert((size_t)2, 3);

	// Assert
	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ(1, list.head()->value);
	EXPECT_EQ(2, list.head()->next->value);
	EXPECT_EQ(3, list.tail()->value);
}

TEST(TestListLib, insert_with_throw_out_of_range) {
	// Arrange
	List<int> list;
	list.push_back(1);
	list.push_back(2);

	// Act & Assert
	EXPECT_ANY_THROW(list.insert((size_t)7, 3));
}

TEST(TestListLib, insert_after_node_in_middle) {
	// Arrange
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(4);
	Node<int>* node = list.head()->next;

	// Act
	list.insert(node, 3);

	// Assert
	EXPECT_FALSE(list.is_empty());
	Node<int>* cur = list.head();
	EXPECT_EQ(1, cur->value);
	cur = cur->next;
	EXPECT_EQ(2, cur->value);
	cur = cur->next;
	EXPECT_EQ(3, cur->value);
	cur = cur->next;
	EXPECT_EQ(4, cur->value);
	EXPECT_EQ(nullptr, cur->next);
}

TEST(TestListLib, insert_after_tail_node) {
	// Arrange
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	Node<int>* node = list.tail();

	// Act
	list.insert(node, 4);

	// Assert
	EXPECT_FALSE(list.is_empty());
	Node<int>* cur = list.head();
	EXPECT_EQ(1, cur->value);
	cur = cur->next;
	EXPECT_EQ(2, cur->value);
	cur = cur->next;
	EXPECT_EQ(3, cur->value);
	cur = cur->next;
	EXPECT_EQ(4, cur->value);
	EXPECT_EQ(nullptr, cur->next);
}

TEST(TestListLib, insert_after_nullptr) {
	// Arrange
	List<int> list;
	list.push_back(1);
	list.push_back(2);

	// Act & Assert
	EXPECT_ANY_THROW(list.insert(nullptr, 3));
}

TEST(TestListLib, insert_after_node_not_in_list) {
	// Arrange
	List<int> list;
	list.push_back(1);
	Node<int>* foreign_node = new Node<int>(888);

	// Act & Assert
	EXPECT_ANY_THROW(list.insert(foreign_node, 2));

	// Cleanup
	delete foreign_node;
}

TEST(TestListLib, pop_front_single_element) {
	// Arrange
	List<int> list;
	list.push_back(456);

	// Act
	list.pop_front();

	// Assert
	EXPECT_TRUE(list.is_empty());
	EXPECT_EQ(nullptr, list.head());
	EXPECT_EQ(nullptr, list.tail());
}

TEST(TestListLib, pop_front_multiple_elements) {
	// Arrange
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	// Act
	list.pop_front();

	// Assert
	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ(2, list.head()->value);
	EXPECT_EQ(3, list.tail()->value);
	EXPECT_EQ(nullptr, list.tail()->next);
}

TEST(TestListLib, pop_front_in_empty_list) {
	// Arrange
	List<int> list;

	// Act & Assert
	EXPECT_ANY_THROW(list.pop_front());
}

TEST(TestListLib, pop_back_single_element) {
	// Arrange
	List<int> list;
	list.push_back(456);

	// Act
	list.pop_back();

	// Assert
	EXPECT_TRUE(list.is_empty());
	EXPECT_EQ(nullptr, list.head());
	EXPECT_EQ(nullptr, list.tail());
}

TEST(TestListLib, pop_back_multiple_elements) {
	// Arrange
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	// Act
	list.pop_back();

	// Assert
	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ(1, list.head()->value);
	EXPECT_EQ(2, list.tail()->value);
	EXPECT_EQ(nullptr, list.tail()->next);
}

TEST(TestListLib, pop_back_in_empty_list) {
	// Arrange
	List<int> list;

	// Act & Assert
	EXPECT_ANY_THROW(list.pop_back());
}

TEST(TestListLib, erase_with_position_at_beggining) {
	// Arrange
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	// Act 
	list.erase((size_t)0);

	// Assert
	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ(2, list.head()->value);
	EXPECT_EQ(3, list.tail()->value);
}

TEST(TestListLib, erase_with_position_in_middle) {
	// Arrange
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	// Act 
	list.erase((size_t)1);

	// Assert
	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ(1, list.head()->value);
	EXPECT_EQ(3, list.tail()->value);
}

TEST(TestListLib, erase_with_position_at_end) {
	// Arrange
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	// Act 
	list.erase((size_t)2);

	// Assert
	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ(1, list.head()->value);
	EXPECT_EQ(2, list.tail()->value);
}

TEST(TestListLib, erase_with_position_in_empty_list) {
	// Arrange
	List<int> list;

	// Act & Assert
	EXPECT_ANY_THROW(list.erase((size_t)0));
}

TEST(TestListLib, erase_with_position_more_than_list) {
	// Arrange
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	// Act & Assert
	EXPECT_ANY_THROW(list.erase((size_t)8));
}

TEST(TestListLib, erase_first_node) {
	// Arrange
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	Node<int>* node = list.head();

	// Act
	list.erase(node);

	// Assert
	EXPECT_EQ(2, list.head()->value);
	EXPECT_EQ(3, list.tail()->value);
}

TEST(TestListLib, erase_with_node_in_middle) {
	// Arrange
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	Node<int>* node = list.head();

	// Act 
	list.erase(node);

	// Assert
	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ(2, list.head()->value);
	EXPECT_EQ(3, list.tail()->value);
}

TEST(TestListLib, erase_with_node_at_end) {
	// Arrange
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	Node<int>* node = list.tail();

	// Act 
	list.erase(node);

	// Assert
	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ(1, list.head()->value);
	EXPECT_EQ(2, list.tail()->value);
}

TEST(TestListLib, erase_after_node_not_in_list) {
	// Arrange
	List<int> list;
	list.push_back(1);
	Node<int>* foreign_node = new Node<int>(888);

	// Act & Assert
	EXPECT_ANY_THROW(list.erase(foreign_node));

	// Cleanup
	delete foreign_node;
}

TEST(TestListLib, erase_nullptr) {
	// Arrange
	List<int> list;
	list.push_back(1);

	// Act & Assert
	ASSERT_ANY_THROW(list.erase(nullptr));
}

TEST(TestListLib, operator_assign_empty_to_empty) {
	// Arrange
	List<int> list1;
	List<int> list2;

	// Act
	list1 = list2;

	// Assert
	EXPECT_TRUE(list1.is_empty());
	EXPECT_TRUE(list2.is_empty());
}

TEST(TestListLib, operator_assign_empty_to_not_empty) {
	// Arrange
	List<int> list1;
	list1.push_front(1);
	list1.push_front(2);
	list1.push_front(3);
	List<int> list2;

	// Act
	list2 = list1;

	// Assert
	EXPECT_FALSE(list2.is_empty());
	EXPECT_EQ(3, list2.head()->value);
	EXPECT_EQ(2, list2.head()->next->value);
	EXPECT_EQ(1, list2.tail()->value);
}

TEST(TestListLib, operator_assign_not_empty_to_empty) {
	// Arrange
	List<int> list1;
	list1.push_back(1);
	list1.push_back(2);
	List<int> list2;

	// Act
	list1 = list2;

	// Assert
	EXPECT_TRUE(list1.is_empty());
	EXPECT_TRUE(list2.is_empty());
}

TEST(TestListLib, operator_assign_self_assignment) {
	// Arrange
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	// Act
	list = list;

	// Assert
	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ(1, list.head()->value);
	EXPECT_EQ(3, list.tail()->value);
}

TEST(TestListLib, operator_assign_chain_of_assignment) {
	// Arrange
	List<int> list1;
	list1.push_back(1);
	List<int> list2;
	list2.push_back(2);
	List<int> list3;
	list3.push_back(3);

	// Act
	list1 = list2 = list3;

	// Assert
	EXPECT_EQ(3, list1.head()->value);
	EXPECT_EQ(3, list2.head()->value);
	EXPECT_EQ(3, list3.head()->value);
}

TEST(TestListLib, test_complex_of_operations) {
	// Arrange
	List<int> list;

	// Act
	list.push_back(1);
	list.push_front(0);
	list.push_back(3);
	list.insert(2, 2);
	list.push_back(4);
	list.pop_front();
	list.pop_back();

	// Assert
	EXPECT_EQ(1, list.head()->value);
	EXPECT_EQ(3, list.tail()->value);
	const Node<int>* cur = list.head();
	EXPECT_EQ(1, cur->value);
	cur = cur->next;
	EXPECT_EQ(2, cur->value);
	cur = cur->next;
	EXPECT_EQ(3, cur->value);
	EXPECT_EQ(nullptr, cur->next);
}

TEST(TestListLib, test_double_list) {
	// Arrange
	List<double> list;

	// Act
	list.push_back(1.1);
	list.push_back(2.2);
	list.push_back(3.3);

	// Assert
	EXPECT_NEAR(1.1, list.head()->value, EPSILON);
	EXPECT_NEAR(3.3, list.tail()->value, EPSILON);

	// Act
	list.erase((size_t)1);

	// Assert
	EXPECT_NEAR(1.1, list.head()->value, EPSILON);
	EXPECT_NEAR(3.3, list.tail()->value, EPSILON);
	EXPECT_NEAR(3.3, list.head()->next->value, EPSILON);
}

TEST(TestListLib, test_string_list) {
	// Arrange
	List<std::string> list;

	// Act
	list.push_back("Hello");
	list.push_back("World");
	list.push_front("Start");

	// Assert
	EXPECT_EQ("Start", list.head()->value);
	EXPECT_EQ("World", list.tail()->value);

	// Act
	list.pop_front();

	// Assert
	EXPECT_EQ("Hello", list.head()->value);
}