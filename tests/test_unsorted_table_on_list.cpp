// Copyright 2026 Ekaterina Ushnitskaya

#include <gtest/gtest.h>

#include "../lib_unsorted_table_on_list/unsorted_table_on_list.h"
#include "../lib_polynom/polynom.h"

#define EPSILON 0.000001
#define TRUE 1
#define FALSE 0

TEST(TestUnsortedTableOnList, table_is_empty_after_creat) {
    // Arrange
    UnsortedTableOnList<std::string, Polynom> table;

    // Act
    bool result = table.is_empty();

    // Assert
    EXPECT_TRUE(result);
}

TEST(TestUnsortedTableOnList, table_not_empty_after_insert) {
    // Arrange
    UnsortedTableOnList<std::string, Polynom> table;
    Polynom p("x");

    // Act
    table.insert("A", p);

    // Assert
    EXPECT_FALSE(table.is_empty());
}

TEST(TestUnsortedTableOnList, insert_one_element_and_find) {
    // Arrange
    UnsortedTableOnList<std::string, Polynom> table;
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

TEST(TestUnsortedTableOnList, find_non_existing_key_returns_nullptr) {
    // Arrange
    UnsortedTableOnList<std::string, Polynom> table;

    // Act
    const Polynom* result = table.found("X");

    // Assert
    EXPECT_EQ(nullptr, result);
}

TEST(TestUnsortedTableOnList, insert_some_elements) {
    // Arrange
    UnsortedTableOnList<std::string, Polynom> table;

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

TEST(TestUnsortedTableOnList, insert_duplicate_key_should_throw) {
    // Arrange
    UnsortedTableOnList<std::string, Polynom> table;
    Polynom p("x");

    table.insert("A", p);

    // Act & Assert
    EXPECT_ANY_THROW(table.insert("A", p));
}

TEST(TestUnsortedTableOnList, erase_element) {
    // Arrange
    UnsortedTableOnList<std::string, Polynom> table;
    Polynom p("x");
    table.insert("A", p);

    // Act
    table.erase("A");
    const Polynom* result = table.found("A");

    // Assert
    EXPECT_EQ(nullptr, result);
}

TEST(TestUnsortedTableOnList, erase_should_throw) {
    // Arrange
    UnsortedTableOnList<std::string, Polynom> table;

    // Act & Assert
    EXPECT_ANY_THROW(table.erase("X"));
}

TEST(TestUnsortedTableOnList, table_empty_after_removing_last_element) {
    // Arrange
    UnsortedTableOnList<std::string, Polynom> table;
    table.insert("A", Polynom("x"));

    // Act
    table.erase("A");

    // Assert
    EXPECT_TRUE(table.is_empty());
}

TEST(TestUnsortedTableOnList, find_after_some_inserts) {
    // Arrange
    UnsortedTableOnList<std::string, Polynom> table;
    table.insert("P1", Polynom("x"));
    table.insert("P2", Polynom("2x"));
    table.insert("P3", Polynom("3x"));

    // Act
    const Polynom* result = table.found("P2");

    // Assert
    EXPECT_NE(nullptr, result);
}

TEST(TestUnsortedTableOnList, mixed_operations) {
    // Arrange
    UnsortedTableOnList<std::string, Polynom> table;

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

TEST(TestUnsortedTableOnList, elements_keep_insertion_order) {
    // Arrange
    UnsortedTableOnList<int, std::string> table;

    // Act
    table.insert(5, "five");
    table.insert(1, "one");
    table.insert(3, "three");
    table.insert(2, "two");
    table.insert(4, "four");

    // Assert
    ASSERT_EQ(5, table.size());
    EXPECT_EQ(5, table.get_row(0).first);
    EXPECT_EQ(1, table.get_row(1).first);
    EXPECT_EQ(3, table.get_row(2).first);
    EXPECT_EQ(2, table.get_row(3).first);
    EXPECT_EQ(4, table.get_row(4).first);
}

TEST(TestUnsortedTableOnList, erase_from_beginning) {
    // Arrange
    UnsortedTableOnList<int, std::string> table;
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

TEST(TestUnsortedTableOnList, erase_from_middle) {
    // Arrange
    UnsortedTableOnList<int, std::string> table;
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

TEST(TestUnsortedTableOnList, erase_from_end) {
    // Arrange
    UnsortedTableOnList<int, std::string> table;
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

TEST(TestUnsortedTableOnList, erase_and_insert_new) {
    // Arrange
    UnsortedTableOnList<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    // Act
    table.erase(2);
    table.insert(4, "four");

    // Assert
    ASSERT_EQ(3, table.size());
    EXPECT_EQ(1, table.get_row(0).first);
    EXPECT_EQ(3, table.get_row(1).first);
    EXPECT_EQ(4, table.get_row(2).first);
}

TEST(TestUnsortedTableOnList, get_row_out_of_range_throws) {
    // Arrange
    UnsortedTableOnList<int, std::string> table;
    table.insert(1, "one");

    // Act & Assert
    EXPECT_ANY_THROW(table.get_row(5));
    EXPECT_ANY_THROW(table.get_row(100456));
}

TEST(TestUnsortedTableOnList, size_returns_correct_number) {
    // Arrange
    UnsortedTableOnList<int, std::string> table;

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

TEST(TestUnsortedTableOnList, erase_and_check_memory) {
    // Arrange
    UnsortedTableOnList<int, std::string> table;
    for (int i = 0; i < 10; i++) {
        table.insert(i, "value" + std::to_string(i));
    }

    // Act - удаляем все элементы
    for (int i = 0; i < 10; i++) {
        table.erase(i);
    }

    // Assert
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(0, table.size());
}

TEST(TestUnsortedTableOnList, insert_polynom) {
    // Arrange
    UnsortedTableOnList<std::string, Polynom> table;
    Polynom p1("x^2 + 2x + 1");
    Polynom p2("3x^3 + 2x^2 + x");

    // Act
    table.insert("poly1", p1);
    table.insert("poly2", p2);

    // Assert
    const Polynom* result1 = table.found("poly1");
    const Polynom* result2 = table.found("poly2");

    EXPECT_NE(nullptr, result1);
    EXPECT_NE(nullptr, result2);

    std::ostringstream oss;
    oss << *result1;
    EXPECT_EQ("x^2 + 2x + 1", oss.str());

    oss.str("");
    oss << *result2;
    EXPECT_EQ("3x^3 + 2x^2 + x", oss.str());
}

TEST(TestUnsortedTableOnList, hard_test_with_mixed) {
    // Arrange
    UnsortedTableOnList<std::string, int> table;

    // Act & Assert
    table.insert("a", 10);
    table.insert("b", 20);
    table.insert("c", 30);

    EXPECT_EQ(3, table.size());

    table.erase("b");
    EXPECT_EQ(2, table.size());
    EXPECT_EQ(nullptr, table.found("b"));

    table.insert("d", 40);
    EXPECT_EQ(3, table.size());

    EXPECT_EQ("a", table.get_row(0).first);
    EXPECT_EQ(10, table.get_row(0).second);
    EXPECT_EQ("c", table.get_row(1).first);
    EXPECT_EQ(30, table.get_row(1).second);
    EXPECT_EQ("d", table.get_row(2).first);
    EXPECT_EQ(40, table.get_row(2).second);
}

TEST(TestUnsortedTableOnList, mixed_types) {
    // Arrange
    UnsortedTableOnList<int, double> table;

    // Act
    table.insert(1, 3.14);
    table.insert(2, 2.718);
    table.insert(3, 1.618);

    // Assert
    EXPECT_NEAR(3.14, *table.found(1), EPSILON);
    EXPECT_NEAR(2.718, *table.found(2), EPSILON);
    EXPECT_NEAR(1.618, *table.found(3), EPSILON);
}

TEST(TestUnsortedTableOnList, string_keys_and_values) {
    // Arrange
    UnsortedTableOnList<std::string, std::string> table;

    // Act
    table.insert("key1", "value1");
    table.insert("key2", "value2");
    table.insert("", "empty_key");

    // Assert
    EXPECT_EQ(3, table.size());
    EXPECT_EQ("value1", *table.found("key1"));
    EXPECT_EQ("value2", *table.found("key2"));
    EXPECT_EQ("empty_key", *table.found(""));
}

TEST(TestUnsortedTableOnList, find_on_empty_table_returns_nullptr) {
    // Arrange
    UnsortedTableOnList<int, std::string> table;

    // Act & Assert
    EXPECT_EQ(nullptr, table.found(1));
}

TEST(TestUnsortedTableOnList, erase_on_empty_table_throws) {
    // Arrange
    UnsortedTableOnList<int, std::string> table;

    // Act & Assert
    EXPECT_ANY_THROW(table.erase(1));
}

TEST(TestUnsortedTableOnList, erase_non_existent_throws) {
    // Arrange
    UnsortedTableOnList<int, std::string> table;
    table.insert(1, "one");

    // Act & Assert
    EXPECT_ANY_THROW(table.erase(2));
    EXPECT_EQ(1, table.size());
}

TEST(TestUnsortedTableOnList, insert_after_erase_same_key) {
    // Arrange
    UnsortedTableOnList<int, std::string> table;
    table.insert(1, "one");
    table.erase(1);

    // Act
    table.insert(1, "new one");

    // Assert
    EXPECT_EQ(1, table.size());
    EXPECT_EQ("new one", *table.found(1));
}

TEST(TestUnsortedTableOnList, insert_after_multiple_erases) {
    // Arrange
    UnsortedTableOnList<int, std::string> table;

    // Act
    for (int i = 0; i < 10; i++) {
        table.insert(i, "value" + std::to_string(i));
    }

    for (int i = 0; i < 5; i++) {
        table.erase(i);
    }

    for (int i = 10; i < 15; i++) {
        table.insert(i, "new" + std::to_string(i));
    }

    // Assert
    EXPECT_EQ(10, table.size());  // 5 оставшихся + 5 новых
    for (int i = 5; i < 10; i++) {
        EXPECT_NE(nullptr, table.found(i));
    }
    for (int i = 10; i < 15; i++) {
        EXPECT_NE(nullptr, table.found(i));
    }
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(nullptr, table.found(i));
    }
}