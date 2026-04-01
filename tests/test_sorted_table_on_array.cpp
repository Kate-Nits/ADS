// Copyright 2026 Ekaterina Ushnitskaya

#include <gtest/gtest.h>

#include "../lib_sorted_table_on_array/sorted_table_on_array.h"
#include "../lib_polynom/polynom.h"

#define EPSILON 0.000001
#define TRUE 1
#define FALSE 0

TEST(TestSortedTableOnArray, table_is_empty_after_creat) {
    // Arrange
    SortedTableOnArray<std::string, Polynom> table;

    // Act
    bool result = table.is_empty();

    // Assert
    EXPECT_TRUE(result);
}

TEST(TestSortedTableOnArray, table_not_empty_after_insert) {
    // Arrange
    SortedTableOnArray<std::string, Polynom> table;
    Polynom p("x");

    // Act
    table.insert("A", p);

    // Assert
    EXPECT_FALSE(table.is_empty());
}

TEST(TestSortedTableOnArray, insert_one_element_and_find) {
    // Arrange
    SortedTableOnArray<std::string, Polynom> table;
    Polynom p("2x");

    // Act
    table.insert("A", p);
    const Polynom* result = table.found("A");

    // Assert
    EXPECT_NE(result, nullptr);
    std::ostringstream oss;
    oss << *result;
    EXPECT_EQ("2x", oss.str());
}

TEST(TestSortedTableOnArray, find_non_existing_key_returns_nullptr) {
    // Arrange
    SortedTableOnArray<std::string, Polynom> table;

    // Act
    const Polynom* result = table.found("X");

    // Assert
    EXPECT_EQ(nullptr, result);
}

TEST(TestSortedTableOnArray, insert_some_elements) {
    // Arrange
    SortedTableOnArray<std::string, Polynom> table;

    // Act
    table.insert("A", Polynom("x"));
    table.insert("B", Polynom("y"));
    table.insert("C", Polynom("z"));

    const Polynom* a = table.found("A");
    const Polynom* b = table.found("B");
    const Polynom* c = table.found("C");

    // Assert
    EXPECT_NE(a, nullptr);
    EXPECT_NE(b, nullptr);
    EXPECT_NE(c, nullptr);
}

TEST(TestSortedTableOnArray, insert_duplicate_key_should_throw) {
    // Arrange
    SortedTableOnArray<std::string, Polynom> table;
    Polynom p("x");

    table.insert("A", p);

    // Act & Assert
    EXPECT_ANY_THROW(table.insert("A", p));
}

TEST(TestSortedTableOnArray, erase_element) {
    // Arrange
    SortedTableOnArray<std::string, Polynom> table;
    Polynom p("x");
    table.insert("A", p);

    // Act
    table.erase("A");
    const Polynom* result = table.found("A");

    // Assert
    EXPECT_EQ(nullptr, result);
}

TEST(TestSortedTableOnArray, erase_should_throw) {
    // Arrange
    SortedTableOnArray<std::string, Polynom> table;

    // Act & Assert
    EXPECT_ANY_THROW(table.erase("X"));
}

TEST(TestSortedTableOnArray, table_empty_after_removing_last_element) {
    // Arrange
    SortedTableOnArray<std::string, Polynom> table;
    table.insert("A", Polynom("x"));

    // Act
    table.erase("A");

    // Assert
    EXPECT_TRUE(table.is_empty());
}

TEST(TestSortedTableOnArray, find_after_some_inserts) {
    // Arrange
    SortedTableOnArray<std::string, Polynom> table;
    table.insert("P1", Polynom("x"));
    table.insert("P2", Polynom("2x"));
    table.insert("P3", Polynom("3x"));

    // Act
    const Polynom* result = table.found("P2");

    // Assert
    EXPECT_NE(nullptr, result);
}

TEST(TestSortedTableOnArray, mixed_operations) {
    // Arrange
    SortedTableOnArray<std::string, Polynom> table;

    // Act
    table.insert("A", Polynom("x"));
    table.insert("B", Polynom("2x"));
    table.insert("C", Polynom("3x"));

    table.erase("B");

    const Polynom* a = table.found("A");
    const Polynom* b = table.found("B");
    const Polynom* c = table.found("C");

    // Assert
    EXPECT_NE(a, nullptr);
    EXPECT_EQ(b, nullptr);
    EXPECT_NE(c, nullptr);
}

TEST(TestSortedTableOnArray, elements_are_sorted_after_insert) {
    // Arrange
    SortedTableOnArray<int, std::string> table;

    // Act
    table.insert(5, "five");
    table.insert(1, "one");
    table.insert(3, "three");
    table.insert(2, "two");
    table.insert(4, "four");

    // Assert
    ASSERT_EQ(5, table.size());
    EXPECT_EQ(1, table.get_row(0).first);
    EXPECT_EQ(2, table.get_row(1).first);
    EXPECT_EQ(3, table.get_row(2).first);
    EXPECT_EQ(4, table.get_row(3).first);
    EXPECT_EQ(5, table.get_row(4).first);
}

TEST(TestSortedTableOnArray, elements_are_sorted_with_string_keys) {
    // Arrange
    SortedTableOnArray<std::string, int> table;

    // Act
    table.insert("banana", 3);
    table.insert("apple", 1);
    table.insert("cherry", 4);
    table.insert("date", 5);
    table.insert("elderberry", 6);

    // Assert
    ASSERT_EQ(5, table.size());
    EXPECT_EQ("apple", table.get_row(0).first);
    EXPECT_EQ("banana", table.get_row(1).first);
    EXPECT_EQ("cherry", table.get_row(2).first);
    EXPECT_EQ("date", table.get_row(3).first);
    EXPECT_EQ("elderberry", table.get_row(4).first);
}

TEST(TestSortedTableOnArray, insert_at_beginning_sort) {
    // Arrange
    SortedTableOnArray<int, std::string> table;
    table.insert(5, "five");
    table.insert(10, "ten");
    table.insert(15, "fifteen");

    // Act
    table.insert(1, "one");

    // Assert
    ASSERT_EQ(4, table.size());
    EXPECT_EQ(1, table.get_row(0).first);
    EXPECT_EQ(5, table.get_row(1).first);
    EXPECT_EQ(10, table.get_row(2).first);
    EXPECT_EQ(15, table.get_row(3).first);
}

TEST(TestSortedTableOnArray, insert_at_end_sort) {
    // Arrange
    SortedTableOnArray<int, std::string> table;
    table.insert(5, "five");
    table.insert(10, "ten");

    // Act
    table.insert(20, "twenty");

    // Assert
    ASSERT_EQ(3, table.size());
    EXPECT_EQ(5, table.get_row(0).first);
    EXPECT_EQ(10, table.get_row(1).first);
    EXPECT_EQ(20, table.get_row(2).first);
}

TEST(TestSortedTableOnArray, insert_in_middle_sort) {
    // Arrange
    SortedTableOnArray<int, std::string> table;
    table.insert(1, "one");
    table.insert(3, "three");
    table.insert(5, "five");
    table.insert(7, "seven");
    table.insert(9, "nine");

    // Act 
    table.insert(6, "six");

    // Assert
    ASSERT_EQ(6, table.size());
    EXPECT_EQ(1, table.get_row(0).first);
    EXPECT_EQ(3, table.get_row(1).first);
    EXPECT_EQ(5, table.get_row(2).first);
    EXPECT_EQ(6, table.get_row(3).first);
    EXPECT_EQ(7, table.get_row(4).first);
    EXPECT_EQ(9, table.get_row(5).first);
}

TEST(TestSortedTableOnArray, some_insert_sort) {
    // Arrange
    SortedTableOnArray<int, std::string> table;

    // Act
    int keys[] = { 10, 3, 7, 1, 9, 2, 8, 4, 6, 5 };
    for (int key : keys) {
        table.insert(key, "value" + std::to_string(key));
    }

    // Assert
    ASSERT_EQ(10, table.size());
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(i + 1, table.get_row(i).first);
    }
}

TEST(TestSortedTableOnArray, binary_search_finds_existing_keys) {
    // Arrange
    SortedTableOnArray<int, std::string> table;
    for (int i = 1; i <= 10; i++) {
        table.insert(i, "value" + std::to_string(i));
    }

    // Act & Assert
    for (int i = 1; i <= 10; i++) {
        const std::string* value = table.found(i);
        EXPECT_NE(nullptr, value);
        EXPECT_EQ("value" + std::to_string(i), *value);
    }
}

TEST(TestSortedTableOnArray, binary_search_returns_nullptr_for_non_existing) {
    // Arrange
    SortedTableOnArray<int, std::string> table;
    for (int i = 1; i <= 5; i++) {
        table.insert(i, "value" + std::to_string(i));
    }

    // Act & Assert
    EXPECT_EQ(nullptr, table.found(0));
    EXPECT_EQ(nullptr, table.found(6));
    EXPECT_EQ(nullptr, table.found(10));
    EXPECT_EQ(nullptr, table.found(100789));
}

TEST(TestSortedTableOnArray, erase_from_beginning) {
    // Arrange
    SortedTableOnArray<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    table.insert(4, "four");

    // Act
    table.erase(1);

    // Assert
    ASSERT_EQ(3, table.size());
    EXPECT_EQ(2, table.get_row(0).first);
    EXPECT_EQ(3, table.get_row(1).first);
    EXPECT_EQ(4, table.get_row(2).first);
}

TEST(TestSortedTableOnArray, erase_from_middle) {
    // Arrange
    SortedTableOnArray<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    table.insert(4, "four");
    table.insert(5, "five");

    // Act
    table.erase(3);

    // Assert
    ASSERT_EQ(4, table.size());
    EXPECT_EQ(1, table.get_row(0).first);
    EXPECT_EQ(2, table.get_row(1).first);
    EXPECT_EQ(4, table.get_row(2).first);
    EXPECT_EQ(5, table.get_row(3).first);
}

TEST(TestSortedTableOnArray, erase_from_end) {
    // Arrange
    SortedTableOnArray<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    // Act
    table.erase(3);

    // Assert
    ASSERT_EQ(2, table.size());
    EXPECT_EQ(1, table.get_row(0).first);
    EXPECT_EQ(2, table.get_row(1).first);
}

TEST(TestSortedTableOnArray, erase_and_insert_maintains_sort) {
    // Arrange
    SortedTableOnArray<int, std::string> table;
    table.insert(1, "one");
    table.insert(3, "three");
    table.insert(5, "five");
    table.insert(7, "seven");
    table.insert(9, "nine");

    // Act
    table.erase(5);
    table.insert(6, "six");
    table.insert(5, "four");

    // Assert
    ASSERT_EQ(6, table.size());
    EXPECT_EQ(1, table.get_row(0).first);
    EXPECT_EQ(3, table.get_row(1).first);
    EXPECT_EQ(5, table.get_row(2).first);
    EXPECT_EQ(6, table.get_row(3).first);
    EXPECT_EQ(7, table.get_row(4).first);
    EXPECT_EQ(9, table.get_row(5).first);
}

TEST(TestSortedTableOnArray, size_returns_correct_number) {
    // Arrange
    SortedTableOnArray<int, std::string> table;

    // Act & Assert
    EXPECT_EQ(0, table.size());

    table.insert(1, "one");
    EXPECT_EQ(1, table.size());

    table.insert(2, "two");
    EXPECT_EQ(2, table.size());

    table.erase(1);
    EXPECT_EQ(1, table.size());

    table.erase(2);
    EXPECT_EQ(0, table.size());
}

TEST(TestSortedTableOnArray, insert_with_same_key_different_value_throws) {
    // Arrange
    SortedTableOnArray<int, std::string> table;
    table.insert(1, "one");

    // Act & Assert
    EXPECT_ANY_THROW(table.insert(1, "ONE"));
    EXPECT_EQ(1, table.size());
    const std::string* val = table.found(1);
    EXPECT_EQ("one", *val);
}

TEST(TestSortedTableOnArray, empty_table_binary_search_returns_minus_one) {
    // Arrange
    SortedTableOnArray<int, std::string> table;

    // Act & Assert
    EXPECT_EQ(nullptr, table.found(1));
}

TEST(TestSortedTableOnArray, find_insert_pos_for_empty_table) {
    // Arrange
    SortedTableOnArray<int, std::string> table;

    // Act
    table.insert(5, "five");

    // Assert
    EXPECT_EQ(1, table.size());
    EXPECT_EQ(5, table.get_row(0).first);
}

TEST(TestSortedTableOnArray, find_insert_pos_for_duplicate_throws_before_insert) {
    // Arrange
    SortedTableOnArray<int, std::string> table;
    table.insert(5, "five");

    // Act & Assert
    EXPECT_ANY_THROW(table.insert(5, "five again"));
    EXPECT_EQ(1, table.size());
}

TEST(TestSortedTableOnArray, erase_from_empty_table_throws) {
    // Arrange
    SortedTableOnArray<int, std::string> table;

    // Act & Assert
    EXPECT_ANY_THROW(table.erase(1));
}

TEST(TestSortedTableOnArray, get_row_out_of_range_throws) {
    // Arrange
    SortedTableOnArray<int, std::string> table;
    table.insert(1, "one");

    // Act & Assert
    EXPECT_ANY_THROW(table.get_row(5));
    EXPECT_ANY_THROW(table.get_row(100));
}

TEST(TestSortedTableOnArray, binary_search) {
    // Arrange
    SortedTableOnArray<int, std::string> table;

    // Тест с 1 элементом
    table.insert(5, "five");
    EXPECT_NE(nullptr, table.found(5));
    EXPECT_EQ(nullptr, table.found(4));
    EXPECT_EQ(nullptr, table.found(6));

    // Тест с 2 элементами
    table.insert(10, "ten");
    EXPECT_NE(nullptr, table.found(5));
    EXPECT_NE(nullptr, table.found(10));
    EXPECT_EQ(nullptr, table.found(7));
    EXPECT_EQ(nullptr, table.found(15));

    // Тест с 3 элементами
    table.insert(7, "seven");
    EXPECT_NE(nullptr, table.found(5));
    EXPECT_NE(nullptr, table.found(7));
    EXPECT_NE(nullptr, table.found(10));
    EXPECT_EQ(nullptr, table.found(1));
    EXPECT_EQ(nullptr, table.found(20));
}