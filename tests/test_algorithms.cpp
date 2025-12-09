// Copyright 2025 Ekaterina Ushnitskaya

#include <gtest/gtest.h>
#include "../lib_tvector/tvector.h"
#include "../lib_mathvector/MathVector.h"
#include "../lib_matrix/matrix.h"
#include "../lib_node/node.h"
#include "../lib_list/list.h"
#include "../lib_algorithms/algorithms.h"

#define EPSILON 0.000001
#define TRUE 1
#define FALSE 0

TEST(TestAlgorithmsLib, test_gradient_descent_from_example1) {
    // Arrange
    Matrix<int> matrix{ {3, 1, 2}, {5, 8, 4}, {7, 6, 9} };

    // Act 
    int res = gradient_descent(matrix);

    // Assert
    EXPECT_TRUE(res == 6 || res == 1);
}

TEST(TestAlgorithmsLib, test_gradient_descent_from_example2) {
    // Arrange
    Matrix<int> matrix{ {11, 15, 10, 9}, {6, 16, 3, 8}, {7, 4, 2, 13}, {14, 12, 1, 5} };

    // Act 
    int res = gradient_descent(matrix);

    // Assert
    EXPECT_TRUE(res == 6 || res == 1);
}

TEST(TestAlgorithmsLib, test_1_on_check_brackets_empty_list) {
    // Arrange
    std::string string = "";

    // Act & Assert
    EXPECT_TRUE(check_brackets(string));
}

TEST(TestAlgorithmsLib, test_2_on_check_brackets_easy) {
    // Arrange
    std::string string = "()";

    // Act & Assert
    EXPECT_TRUE(check_brackets(string));
}

TEST(TestAlgorithmsLib, test_3_on_check_brackets_easy) {
    // Arrange
    std::string string = "()()";

    // Act & Assert
    EXPECT_TRUE(check_brackets(string));
}

TEST(TestAlgorithmsLib, test_4_on_check_brackets) {
    // Arrange
    std::string string = "[(()())(())]";

    // Act & Assert
    EXPECT_TRUE(check_brackets(string));
}

TEST(TestAlgorithmsLib, test_5_on_check_brackets) {
    // Arrange
    std::string string = "(()()";

    // Act & Assert
    EXPECT_FALSE(check_brackets(string));
}

TEST(TestAlgorithmsLib, test_6_on_check_brackets) {
    // Arrange
    std::string string = "())(())";

    // Act & Assert
    EXPECT_FALSE(check_brackets(string));
}

TEST(TestAlgorithmsLib, test_7_on_check_brackets) {
    // Arrange
    std::string string = "((()()(()))";

    // Act & Assert
    EXPECT_FALSE(check_brackets(string));
}

TEST(TestAlgorithmsLib, different_types_of_brackets_correct) {
    // Arrange
    std::string str = "({[]})";

    // Act & Assert
    EXPECT_TRUE(check_brackets(str));
}

TEST(TestAlgorithmsLib, mixed_brackets_incorrect) {
    // Arrange
    std::string str = "({[}])";

    // Act & Assert
    EXPECT_FALSE(check_brackets(str));
}

TEST(TestAlgorithmsLib, real_example1_with_text) {
    // Arrange
    std::string str = "[5*(x+8)-9]/[(7/(y*1))*(y*1)]";

    // Act & Assert
    EXPECT_TRUE(check_brackets(str));
}

TEST(TestAlgorithmsLib, real_example2_with_text) {
    // Arrange
    std::string str = "[5*(x+(8)-9]/[(7/(y*1))*(y*1)]";

    // Act & Assert
    EXPECT_FALSE(check_brackets(str));
}

TEST(TestAlgorithmsLib, is_looped_hare_and_turtle_on_empty_list) {
    // Arrange
    List<int> list;

    // Act & Assert
    EXPECT_FALSE(is_looped_hare_and_turtle(list));
}

TEST(TestAlgorithmsLib, is_looped_hare_and_turtle_on_list_with_one_elem_no_loop) {
    // Arrange
    List<int> list;
    list.push_back(7654);

    // Act & Assert
    EXPECT_FALSE(is_looped_hare_and_turtle(list));
}

TEST(TestAlgorithmsLib, is_looped_hare_and_turtle_on_list_with_one_elem_with_loop) {
    // Arrange
    List<int> list;
    list.push_back(8765);
    list.head()->next = list.head();

    // Act & Assert
    EXPECT_TRUE(is_looped_hare_and_turtle(list));
    list.head()->next = nullptr;
}

TEST(TestAlgorithmsLib, is_looped_hare_and_turtle_on_large_list_with_no_loop) {
    // Arrange
    List<int> list;
    for (int i = 0; i < 100; ++i) {
        list.push_back(i);
    }

    // Act & Assert
    EXPECT_FALSE(is_looped_hare_and_turtle(list));
}

TEST(TestAlgorithmsLib, is_looped_hare_and_turtle_on_large_list_with_loop_in_middle) {
    // Arrange
    List<int> list;
    for (int i = 0; i < 100; ++i) {
        list.push_back(i);
    }
    Node<int>* middle = list.head();
    for (int i = 0; i < 50; ++i) {
        middle = middle->next;
    }
    list.tail()->next = middle;

    // Act & Assert
    EXPECT_TRUE(is_looped_hare_and_turtle(list));
    list.tail()->next = nullptr;
}

TEST(TestAlgorithmsLib, is_looped_turn_ptr_on_empty_list) {
    // Arrange
    List<int> list;

    // Act & Assert
    EXPECT_FALSE(is_looped_turn_ptr(list));
}

TEST(TestAlgorithmsLib, is_looped_turn_ptr_on_list_with_one_elem_no_loop) {
    // Arrange
    List<int> list;
    list.push_back(7654);

    // Act & Assert
    EXPECT_FALSE(is_looped_turn_ptr(list));
}

TEST(TestAlgorithmsLib, is_looped_turn_ptr_on_list_with_one_elem_with_loop) {
    // Arrange
    List<int> list;
    list.push_back(8765);
    list.head()->next = list.head();

    // Act & Assert
    EXPECT_TRUE(is_looped_turn_ptr(list));
    list.head()->next = nullptr;
}

TEST(TestAlgorithmsLib, is_looped_turn_ptr_on_large_list_with_no_loop) {
    // Arrange
    List<int> list;
    for (int i = 0; i < 100; ++i) {
        list.push_back(i);
    }

    // Act & Assert
    EXPECT_FALSE(is_looped_turn_ptr(list));
}

TEST(TestAlgorithmsLib, is_looped_turn_ptr_on_large_list_with_loop_in_middle) {
    // Arrange
    List<int> list;
    for (int i = 0; i < 100; ++i) {
        list.push_back(i);
    }
    Node<int>* middle = list.head();
    for (int i = 0; i < 50; ++i) {
        middle = middle->next;
    }
    list.tail()->next = middle;

    // Act & Assert
    EXPECT_TRUE(is_looped_turn_ptr(list));
    list.tail()->next = nullptr;
}

TEST(TestAlgorithmsLib, find_loop_node_in_empty_list) {
    // Arrange
    List<int> list;

    // Act & Assert
    EXPECT_EQ(nullptr, find_loop_node(list));
}

TEST(TestAlgorithmsLib, find_loop_node_no_loop) {
    // Arrange
    List<int> list;
    for (int i = 1; i < 5; ++i) {
        list.push_back(i);
    }

    // Act & Assert
    EXPECT_EQ(nullptr, find_loop_node(list));
}

TEST(TestAlgorithmsLib, find_loop_node_with_loop_in_list_with_one_elem) {
    // Arrange
    List<int> list;
    list.push_back(1);
    list.head()->next = list.head();

    // Act & Assert
    EXPECT_EQ(list.head(), find_loop_node(list));
    list.head()->next = nullptr;
}

TEST(TestAlgorithmsLib, find_loop_node_with_loop_at_beginning) {
    // Arrange
    List<int> list;
    for (int i = 1; i < 5; ++i) {
        list.push_back(i);
    }

    // Act
    list.tail()->next = list.head();

    // Act & Assert
    EXPECT_EQ(list.head(), find_loop_node(list));
    list.tail()->next = nullptr;
}

TEST(TestAlgorithmsLib, find_loop_node_with_loop_in_middle) {
    // Arrange
    List<int> list;
    for (int i = 1; i < 6; ++i) {
        list.push_back(i);
    }

    // Act
    Node<int>* third_node = list.head()->next->next;
    list.tail()->next = third_node;

    // Act & Assert
    EXPECT_EQ(third_node, find_loop_node(list));
    EXPECT_EQ(3, find_loop_node(list)->value);
    list.tail()->next = nullptr;
}

TEST(TestAlgorithmsLib, find_loop_node_with_loop_in_large_list) {
    // Arrange
    List<int> list;
    for (int i = 0; i < 100; ++i) {
        list.push_back(i);
    }
    Node<int>* loop_node = list.head();
    for (int i = 0; i < 75; ++i) {
        loop_node = loop_node->next;
    }
    list.tail()->next = loop_node;

    // Act & Assert
    EXPECT_EQ(loop_node, find_loop_node(list));
    EXPECT_EQ(75, find_loop_node(list)->value);

    // Восстанавливаем
    list.tail()->next = nullptr;
}