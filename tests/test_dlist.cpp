// Copyright 2025 Ekaterina Ushnitskaya

#include <gtest/gtest.h>
#include "../lib_dlist/dlist.h"

#define EPSILON 0.000001
#define TRUE 1
#define FALSE 0


TEST(TestDListLib, default_constructor) {
	// Arrange & Act
	DList<int> list;

	// Assert
	EXPECT_EQ(nullptr, list.head());
	EXPECT_EQ(nullptr, list.tail());
	EXPECT_TRUE(list.is_empty());
}

TEST(TestDListLib, copy_constructor_with_empty_list) {
	// Arrange
	DList<int> list1;

	// Act
	DList<int> list2(list1);

	// Assert
	EXPECT_TRUE(list2.is_empty());
	EXPECT_EQ(list1.head(), list2.head());
	EXPECT_EQ(list1.tail(), list2.tail());
	EXPECT_EQ(nullptr, list2.head());
	EXPECT_EQ(nullptr, list2.tail());
}

TEST(TestDListLib, copy_constructor_with_not_empty_list) {
	// Arrange
	DList<int> list1;
	list1.push_back(1);
	list1.push_back(2);
	list1.push_back(3);

	// Act
	DList<int> list2(list1);

	// Assert
	EXPECT_FALSE(list2.is_empty());
	EXPECT_EQ(list1.head()->value, list2.head()->value);
	EXPECT_EQ(list1.tail()->value, list2.tail()->value);
	EXPECT_EQ(1, list2.head()->value);
	EXPECT_EQ(3, list2.tail()->value);
}

TEST(TestDListLib, push_front_to_empty_list_one_element) {
	// Arrange
	DList<int> list;

	// Act
	list.push_front(678);

	// Assert
	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ(678, list.head()->value);
	EXPECT_EQ(678, list.tail()->value);
	EXPECT_EQ(list.head(), list.tail());
}

TEST(TestDListLib, push_front_to_empty_list_multiple_elements) {
	// Arrange
	DList<int> list;

	// Act
	list.push_front(1);
	list.push_front(2);
	list.push_front(3);

	// Assert
	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ(3, list.head()->value);
	EXPECT_EQ(1, list.tail()->value);
	NodeD<int>* cur = list.head();
	EXPECT_EQ(3, cur->value);
	cur = cur->next;
	EXPECT_EQ(2, cur->value);
	cur = cur->next;
	EXPECT_EQ(1, cur->value);
	EXPECT_EQ(nullptr, cur->next);
}

TEST(TestDListLib, push_back_to_empty_list_one_element) {
	// Arrange
	DList<int> list;

	// Act
	list.push_back(678);

	// Assert
	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ(678, list.head()->value);
	EXPECT_EQ(678, list.tail()->value);
	EXPECT_EQ(list.head(), list.tail());
}

TEST(TestDListLib, push_back_to_empty_list_multiple_elements) {
	// Arrange
	DList<int> list;

	// Act
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	// Assert
	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ(1, list.head()->value);
	EXPECT_EQ(3, list.tail()->value);
	NodeD<int>* cur = list.head();
	EXPECT_EQ(1, cur->value);
	cur = cur->next;
	EXPECT_EQ(2, cur->value);
	cur = cur->next;
	EXPECT_EQ(3, cur->value);
	EXPECT_EQ(nullptr, cur->next);
}

TEST(TestDListLib, insert_with_position_at_beginning) {
	// Arrange
	DList<int> list;
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

TEST(TestDListLib, insert_with_position_in_middle) {
	// Arrange
	DList<int> list;
	list.push_back(1);
	list.push_back(3);
	list.push_back(4);

	// Act
	list.insert((size_t)1, 2);

	// Assert
	EXPECT_FALSE(list.is_empty());
	NodeD<int>* cur = list.head();
	EXPECT_EQ(1, cur->value);
	cur = cur->next;
	EXPECT_EQ(2, cur->value);
	cur = cur->next;
	EXPECT_EQ(3, cur->value);
	cur = cur->next;
	EXPECT_EQ(4, cur->value);
	EXPECT_EQ(nullptr, cur->next);
}

TEST(TestDListLib, insert_with_position_at_end) {
	// Arrange
	DList<int> list;
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

TEST(TestDListLib, insert_with_throw_out_of_range) {
	// Arrange
	DList<int> list;
	list.push_back(1);
	list.push_back(2);

	// Act & Assert
	EXPECT_ANY_THROW(list.insert((size_t)7, 3));
}

TEST(TestDListLib, insert_after_node_in_middle) {
	// Arrange
	DList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(4);
	NodeD<int>* node = list.head()->next;

	// Act
	list.insert_after(node, 3);

	// Assert
	EXPECT_FALSE(list.is_empty());
	NodeD<int>* cur = list.head();
	EXPECT_EQ(1, cur->value);
	cur = cur->next;
	EXPECT_EQ(2, cur->value);
	cur = cur->next;
	EXPECT_EQ(3, cur->value);
	cur = cur->next;
	EXPECT_EQ(4, cur->value);
	EXPECT_EQ(nullptr, cur->next);
}

TEST(TestDListLib, insert_after_tail_node) {
	// Arrange
	DList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	NodeD<int>* node = list.tail();

	// Act
	list.insert_after(node, 4);

	// Assert
	EXPECT_FALSE(list.is_empty());
	NodeD<int>* cur = list.head();
	EXPECT_EQ(1, cur->value);
	cur = cur->next;
	EXPECT_EQ(2, cur->value);
	cur = cur->next;
	EXPECT_EQ(3, cur->value);
	cur = cur->next;
	EXPECT_EQ(4, cur->value);
	EXPECT_EQ(nullptr, cur->next);
}

TEST(TestDListLib, insert_after_nullptr) {
	// Arrange
	DList<int> list;
	list.push_back(1);
	list.push_back(2);

	// Act & Assert
	EXPECT_ANY_THROW(list.insert_after(nullptr, 3));
}

TEST(TestDListLib, insert_after_node_not_in_list) {
	// Arrange
	DList<int> list;
	list.push_back(1);
	NodeD<int>* foreign_node = new NodeD<int>(888);

	// Act & Assert
	EXPECT_ANY_THROW(list.insert_after(foreign_node, 2));

	// Cleanup
	delete foreign_node;
}

TEST(TestDListLib, insert_before_head) {
	// Arrange
	DList<int> list;
	list.push_back(2);
	list.push_back(3);

	// Act
	list.insert_before(list.head(), 1);

	// Assert
	EXPECT_EQ(1, list.head()->value);
	EXPECT_EQ(2, list.head()->next->value);
	EXPECT_EQ(3, list.tail()->value);
	EXPECT_EQ(nullptr, list.head()->prev);
}

TEST(TestDListLib, insert_before_middle) {
	// Arrange
	DList<int> list;
	list.push_back(1);
	list.push_back(3);
	list.push_back(4);
	NodeD<int>* middle_node = list.head()->next;

	// Act
	list.insert_before(middle_node, 2);

	// Assert
	EXPECT_EQ(1, list.head()->value);
	EXPECT_EQ(4, list.tail()->value);
	NodeD<int>* cur = list.head();
	EXPECT_EQ(1, cur->value);
	cur = cur->next;
	EXPECT_EQ(2, cur->value);
	cur = cur->next;
	EXPECT_EQ(3, cur->value);
	cur = cur->next;
	EXPECT_EQ(4, cur->value);
	EXPECT_EQ(nullptr, cur->next);
}

TEST(TestDListLib, insert_before_tail) {
	// Arrange
	DList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(4);
	NodeD<int>* tail_node = list.tail();

	// Act
	list.insert_before(tail_node, 3);

	// Assert
	EXPECT_EQ(1, list.head()->value);
	EXPECT_EQ(4, list.tail()->value);
	NodeD<int>* cur = list.head();
	EXPECT_EQ(1, cur->value);
	cur = cur->next;
	EXPECT_EQ(2, cur->value);
	cur = cur->next;
	EXPECT_EQ(3, cur->value);
	cur = cur->next;
	EXPECT_EQ(4, cur->value);
	EXPECT_EQ(nullptr, cur->next);
	EXPECT_EQ(3, list.tail()->prev->value);
	EXPECT_EQ(4, list.tail()->value);
}

TEST(TestDListLib, insert_before_in_empty_list) {
	// Arrange
	DList<int> list;
	NodeD<int>* foreign_node = new NodeD<int>(999);

	// Act & Assert
	EXPECT_ANY_THROW(list.insert_before(foreign_node, 1));

	// Cleanup
	delete foreign_node;
}

TEST(TestDListLib, insert_before_nullptr) {
	// Arrange
	DList<int> list;
	list.push_back(1);
	list.push_back(2);

	// Act & Assert
	EXPECT_ANY_THROW(list.insert_before(nullptr, 3));
}

TEST(TestDListLib, insert_before_foreign_node) {
	// Arrange
	DList<int> list1;
	list1.push_back(1);
	list1.push_back(2);
	DList<int> list2;
	list2.push_back(10);
	list2.push_back(20);
	NodeD<int>* foreign_node = list2.head();

	// Act & Assert
	EXPECT_ANY_THROW(list1.insert_before(foreign_node, 3));
}

TEST(TestDListLib, pop_front_single_element) {
	// Arrange
	DList<int> list;
	list.push_back(456);

	// Act
	list.pop_front();

	// Assert
	EXPECT_TRUE(list.is_empty());
	EXPECT_EQ(nullptr, list.head());
	EXPECT_EQ(nullptr, list.tail());
}

TEST(TestDListLib, pop_front_multiple_elements) {
	// Arrange
	DList<int> list;
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

TEST(TestDListLib, pop_front_in_empty_list) {
	// Arrange
	DList<int> list;

	// Act & Assert
	EXPECT_ANY_THROW(list.pop_front());
}

TEST(TestDListLib, pop_back_single_element) {
	// Arrange
	DList<int> list;
	list.push_back(456);

	// Act
	list.pop_back();

	// Assert
	EXPECT_TRUE(list.is_empty());
	EXPECT_EQ(nullptr, list.head());
	EXPECT_EQ(nullptr, list.tail());
}

TEST(TestDListLib, pop_back_multiple_elements) {
	// Arrange
	DList<int> list;
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

TEST(TestDListLib, pop_back_in_empty_list) {
	// Arrange
	DList<int> list;

	// Act & Assert
	EXPECT_ANY_THROW(list.pop_back());
}

TEST(TestDListLib, erase_with_position_at_beggining) {
	// Arrange
	DList<int> list;
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

TEST(TestDListLib, erase_with_position_in_middle) {
	// Arrange
	DList<int> list;
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

TEST(TestDListLib, erase_with_position_at_end) {
	// Arrange
	DList<int> list;
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

TEST(TestDListLib, erase_with_position_in_empty_list) {
	// Arrange
	DList<int> list;

	// Act & Assert
	EXPECT_ANY_THROW(list.erase((size_t)0));
}

TEST(TestDListLib, erase_with_position_more_than_list) {
	// Arrange
	DList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	// Act & Assert
	EXPECT_ANY_THROW(list.erase((size_t)8));
}

TEST(TestDListLib, erase_first_node) {
	// Arrange
	DList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	NodeD<int>* node = list.head();

	// Act
	list.erase(node);

	// Assert
	EXPECT_EQ(2, list.head()->value);
	EXPECT_EQ(3, list.tail()->value);
}

TEST(TestDListLib, erase_with_node_in_middle) {
	// Arrange
	DList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	NodeD<int>* node = list.head();

	// Act 
	list.erase(node);

	// Assert
	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ(2, list.head()->value);
	EXPECT_EQ(3, list.tail()->value);
}

TEST(TestDListLib, erase_with_node_at_end) {
	// Arrange
	DList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	NodeD<int>* node = list.tail();

	// Act 
	list.erase(node);

	// Assert
	EXPECT_FALSE(list.is_empty());
	EXPECT_EQ(1, list.head()->value);
	EXPECT_EQ(2, list.tail()->value);
}

TEST(TestDListLib, erase_after_node_not_in_list) {
	// Arrange
	DList<int> list;
	list.push_back(1);
	NodeD<int>* foreign_node = new NodeD<int>(888);

	// Act & Assert
	EXPECT_ANY_THROW(list.erase(foreign_node));

	// Cleanup
	delete foreign_node;
}

TEST(TestDListLib, erase_nullptr) {
	// Arrange
	DList<int> list;
	list.push_back(1);

	// Act & Assert
	ASSERT_ANY_THROW(list.erase(nullptr));
}

TEST(TestDListLib, operator_assign_empty_to_empty) {
	// Arrange
	DList<int> list1;
	DList<int> list2;

	// Act
	list1 = list2;

	// Assert
	EXPECT_TRUE(list1.is_empty());
	EXPECT_TRUE(list2.is_empty());
}

TEST(TestDListLib, operator_assign_empty_to_not_empty) {
	// Arrange
	DList<int> list1;
	list1.push_front(1);
	list1.push_front(2);
	list1.push_front(3);
	DList<int> list2;

	// Act
	list2 = list1;

	// Assert
	EXPECT_FALSE(list2.is_empty());
	EXPECT_EQ(3, list2.head()->value);
	EXPECT_EQ(2, list2.head()->next->value);
	EXPECT_EQ(1, list2.tail()->value);
}

TEST(TestDListLib, operator_assign_not_empty_to_empty) {
	// Arrange
	DList<int> list1;
	list1.push_back(1);
	list1.push_back(2);
	DList<int> list2;

	// Act
	list1 = list2;

	// Assert
	EXPECT_TRUE(list1.is_empty());
	EXPECT_TRUE(list2.is_empty());
}

TEST(TestDListLib, operator_assign_self_assignment) {
	// Arrange
	DList<int> list;
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

TEST(TestDListLib, operator_assign_chain_of_assignment) {
	// Arrange
	DList<int> list1;
	list1.push_back(1);
	DList<int> list2;
	list2.push_back(2);
	DList<int> list3;
	list3.push_back(3);

	// Act
	list1 = list2 = list3;

	// Assert
	EXPECT_EQ(3, list1.head()->value);
	EXPECT_EQ(3, list2.head()->value);
	EXPECT_EQ(3, list3.head()->value);
}

TEST(TestDListLib, test_complex_of_operations) {
	// Arrange
	DList<int> list;

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
	const NodeD<int>* cur = list.head();
	EXPECT_EQ(1, cur->value);
	cur = cur->next;
	EXPECT_EQ(2, cur->value);
	cur = cur->next;
	EXPECT_EQ(3, cur->value);
	EXPECT_EQ(nullptr, cur->next);
}

TEST(TestDListLib, test_double_list) {
	// Arrange
	DList<double> list;

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

TEST(TestDListLib, test_string_list) {
	// Arrange
	DList<std::string> list;

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

TEST(TestDListLib, iterator_read) {
	// Arrange
	DList<int> list;
	for (int i = 0; i < 5; i++) {
		list.push_back(i);
	}
	int i = 0;

	// Act & Assert
	for (DList<int>::Iterator it = list.begin(); it != list.end(); it++) {
		EXPECT_EQ(i, *it);
		i++;
	}
}

TEST(TestDListLib, iterator_write) {
	// Arrange
	DList<int> list;
	for (int i = 0; i < 5; i++) {
		list.push_back(0);
	}
	int i = 1;
	int j = 10;

	// Act
	for (DList<int>::Iterator it = list.begin(); it != list.end(); it++) {
		*it = i * 10;
		i++;
	}

	// Assert
	for (DList<int>::Iterator it = list.begin(); it != list.end(); it++) {
		EXPECT_EQ(j, *it);
		j += 10;
	}
}

TEST(TestDListLib, back_iterator_write) {
	// Arrange
	DList<int> list;
	for (int i = 0; i < 5; i++) {
		list.push_back(0);
	}
	int i = 1;

	// Act
	for (DList<int>::Iterator it = list.rbegin(); it != list.rend(); it--) {
		*it = i;
		i++;
	}

	// Assert
	for (DList<int>::Iterator it = list.begin(); it != list.end(); it++) {
		EXPECT_EQ(--i, *it);
	}
}

TEST(TestDListLib, iterator_in_empty_list) {
	// Arrange
	DList<int> list;

	// Act
	int iterator_count = 0;
	for (DList<int>::Iterator it = list.begin(); it != list.end(); it++) {
		iterator_count++;
	}

	// Assert
	EXPECT_EQ(0, iterator_count);
	EXPECT_TRUE(list.begin() == list.end());
	EXPECT_FALSE(list.begin() != list.end());
}

TEST(TestDListLib, iterator_operator_assigment) {
	// Arrange
	DList<int> list;
	list.push_back(76);
	list.push_back(32);

	// Act
	DList<int>::Iterator it1 = list.begin();
	DList<int>::Iterator it2 = it1;

	// Assert
	EXPECT_EQ(*it1, *it2);
	EXPECT_TRUE(it1 == it2);
	++it1;
	EXPECT_EQ(32, *it1);
	EXPECT_EQ(76, *it2);
	EXPECT_FALSE(it1 == it2);
}

TEST(TestDListLib, iterator_operator_prefix_plus_plus) {
	// Arrange
	DList<int> list;
	list.push_back(765);
	list.push_back(324);
	list.push_back(456);

	// Act
	DList<int>::Iterator it = list.begin();

	// Assert
	EXPECT_EQ(765, *it);
	EXPECT_EQ(324, *++it);
	EXPECT_EQ(324, *it);
	EXPECT_EQ(456, *++it);
}

TEST(TestDListLib, iterator_operator_postfix_plus_plus) {
	// Arrange
	DList<int> list;
	list.push_back(765);
	list.push_back(324);
	list.push_back(456);

	// Act
	DList<int>::Iterator it = list.begin();

	// Assert
	EXPECT_EQ(765, *it);
	EXPECT_EQ(765, *it++);
	EXPECT_EQ(324, *it);
}

TEST(TestDListLib, iterator_operator_plus_assigment) {
	// Arrange
	DList<int> list;
	for (int i = 1; i < 7; i++) {
		list.push_back(i * 10);
	}

	// Act
	DList<int>::Iterator it = list.begin();
	it += 3;

	// Assert
	EXPECT_EQ(40, *it);
}