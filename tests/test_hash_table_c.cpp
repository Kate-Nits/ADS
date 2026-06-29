// Copyright 2026 Ekaterina Ushnitskaya

#include <gtest/gtest.h>
#include "../lib_hash_table_c/hash_table_c.h"

#define EPSILON 0.000001
#define TRUE 1
#define FALSE 0

TEST(TestHashTableC, default_constructor) {
    // Arrange & Act
    HashTableC<int> table;

    // Assert
    EXPECT_TRUE(table.is_empty());
}

TEST(TestHashTableC, constructor_with_size) {
    // Arrange & Act
    HashTableC<int> table(31);

    // Assert
    EXPECT_TRUE(table.is_empty());
}

TEST(TestHashTableC, constructor_with_size_returns_throws) {
    // Arrange & Act & Assert
    ASSERT_ANY_THROW(HashTableC<int> table(1));
}

TEST(TestHashTableC, insert_one_element) {
    // Arrange
    HashTableC<std::string> table;

    // Act
    table.insert("key1", "value1");

    // Assert
    EXPECT_FALSE(table.is_empty());
    const std::string* val = table.found("key1");
    ASSERT_NE(nullptr, val);
    EXPECT_EQ("value1", *val);
}

TEST(TestHashTableC, insert_multiple_elements) {
    // Arrange
    HashTableC<int> table(31);

    // Act
    table.insert("a", 1);
    table.insert("b", 2);
    table.insert("c", 3);

    // Assert
    EXPECT_EQ(1, *table.found("a"));
    EXPECT_EQ(2, *table.found("b"));
    EXPECT_EQ(3, *table.found("c"));
}

TEST(TestHashTableC, insert_duplicate_key_returns_throws) {
    // Arrange
    HashTableC<int> table;

    // Act
    table.insert("key", 100);

    // Assert
    ASSERT_ANY_THROW(table.insert("key", 200));
}

TEST(TestHashTableC, erase_one_simple_key) {
    // Arrange
    HashTableC<int> table;
    table.insert("key", 42);

    // Act
    table.erase("key");

    // Assert
    EXPECT_EQ(nullptr, table.found("key"));
    EXPECT_TRUE(table.is_empty());
}

TEST(TestHashTableC, erase_one_nonexistent_key_returns_throws) {
    // Arrange
    HashTableC<int> table;
    table.insert("exists", 1);

    // Act & Assert
    ASSERT_ANY_THROW(table.erase("not_exists"));
}

TEST(TestHashTableC, erase_and_insert_same_key) {
    // Arrange
    HashTableC<int> table;
    table.insert("key", 100);
    table.erase("key");

    // Act
    table.insert("key", 200);

    // Assert
    const int* val = table.found("key");
    ASSERT_NE(nullptr, val);
    EXPECT_EQ(200, *val);
}

TEST(TestHashTableC, erase_all_elements) {
    // Arrange
    HashTableC<int> table(31);
    table.insert("a", 1);
    table.insert("b", 2);
    table.insert("c", 3);

    // Act
    table.erase("a");
    table.erase("b");
    table.erase("c");

    // Assert
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(nullptr, table.found("a"));
    EXPECT_EQ(nullptr, table.found("b"));
    EXPECT_EQ(nullptr, table.found("c"));
}

TEST(TestHashTableC, erase_middle_element) {
    // Arrange
    HashTableC<int> table(3);
    table.insert("ab", 1);
    table.insert("ba", 2);
    table.insert("ca", 3);

    // Act
    table.erase("ba");

    // Assert
    EXPECT_NE(nullptr, table.found("ab"));
    EXPECT_EQ(nullptr, table.found("ba"));
    EXPECT_NE(nullptr, table.found("ca"));
}

TEST(TestHashTableC, erase_first_element) {
    // Arrange
    HashTableC<int> table(3);
    table.insert("ab", 1);
    table.insert("ba", 2);
    table.insert("ca", 3);

    // Act
    table.erase("ab");

    // Assert
    EXPECT_EQ(nullptr, table.found("ab"));
    EXPECT_NE(nullptr, table.found("ba"));
    EXPECT_NE(nullptr, table.found("ca"));
}

TEST(TestHashTableC, erase_last_element) {
    // Arrange
    HashTableC<int> table(3);
    table.insert("ab", 1);
    table.insert("ba", 2);
    table.insert("ca", 3);

    // Act
    table.erase("ca");

    // Assert
    EXPECT_NE(nullptr, table.found("ab"));
    EXPECT_NE(nullptr, table.found("ba"));
    EXPECT_EQ(nullptr, table.found("ca"));
}

TEST(TestHashTableC, found_one_simple_key) {
    // Arrange
    HashTableC<double> table;
    table.insert("number", 3.14159);

    // Act
    const double* val = table.found("number");

    // Assert
    ASSERT_NE(nullptr, val);
    EXPECT_DOUBLE_EQ(3.14159, *val);
}

TEST(TestHashTableC, found_nonexistent_key_returns_nullptr) {
    // Arrange
    HashTableC<int> table;
    table.insert("key1", 1);

    // Act
    const int* val = table.found("key2");

    // Assert
    EXPECT_EQ(nullptr, val);
}

TEST(TestHashTableC, found_after_erase_returns_nullptr) {
    // Arrange
    HashTableC<int> table;
    table.insert("key", 123);
    table.erase("key");

    // Act
    const int* val = table.found("key");

    // Assert
    EXPECT_EQ(nullptr, val);
}

TEST(TestHashTableC, found_middle_element) {
    // Arrange
    HashTableC<int> table(3);
    table.insert("ab", 1);
    table.insert("ba", 2);
    table.insert("ca", 3);

    // Act & Assert
    EXPECT_EQ(2, *table.found("ba"));
}

TEST(TestHashTableC, is_empty_new_empty_table) {
    // Arrange & Act
    HashTableC<int> table;

    // Assert
    EXPECT_TRUE(table.is_empty());
}

TEST(TestHashTableC, is_empty_after_insert) {
    // Arrange
    HashTableC<int> table;

    // Act
    table.insert("key", 1);

    // Assert
    EXPECT_FALSE(table.is_empty());
}

TEST(TestHashTableC, is_empty_after_insert_and_erase) {
    // Arrange
    HashTableC<int> table;
    table.insert("key", 1);

    // Act
    table.erase("key");

    // Assert
    EXPECT_TRUE(table.is_empty());
}

TEST(TestHashTableC, many_elements) {
    // Arrange
    HashTableC<int> table(101);

    // Act
    for (int i = 0; i < 100; ++i) {
        table.insert("key_" + std::to_string(i), i);
    }

    // Assert
    EXPECT_FALSE(table.is_empty());
    for (int i = 0; i < 100; ++i) {
        const int* val = table.found("key_" + std::to_string(i));
        ASSERT_NE(nullptr, val);
        EXPECT_EQ(i, *val);
    }
}

TEST(TestHashTableC, empty_string_key) {
    // Arrange
    HashTableC<int> table;

    // Act
    table.insert("", 100);

    // Assert
    const int* val = table.found("");
    ASSERT_NE(nullptr, val);
    EXPECT_EQ(100, *val);
}

TEST(TestHashTableC, merge_dictionaries_example_Marina_Andreevna) {
    // Arrange
    HashTableC<int> dict1;
    dict1.insert("Table", 73738);
    dict1.insert("OOP", 9238);
    dict1.insert("Hash-function", 38);
    dict1.insert("Vector", 3938);

    HashTableC<int> dict2;
    dict2.insert("Interface", 73898);
    dict2.insert("Vector", 11387);
    dict2.insert("Hash-function", 33928);
    dict2.insert("List", 9284);

    // Act
    HashTableC<int> result = merge_dictionaries(dict1, dict2);

    // Assert
    const int* table_val = result.found("Table");
    ASSERT_NE(nullptr, table_val);
    EXPECT_EQ(73738, *table_val);

    const int* oop_val = result.found("OOP");
    ASSERT_NE(nullptr, oop_val);
    EXPECT_EQ(9238, *oop_val);

    const int* hash_val = result.found("Hash-function");
    ASSERT_NE(nullptr, hash_val);
    EXPECT_EQ(38, *hash_val);

    const int* vector_val = result.found("Vector");
    ASSERT_NE(nullptr, vector_val);
    EXPECT_EQ(3938, *vector_val);

    const int* interface_val = result.found("Interface");
    ASSERT_NE(nullptr, interface_val);
    EXPECT_EQ(73898, *interface_val);

    const int* list_val = result.found("List");
    ASSERT_NE(nullptr, list_val);
    EXPECT_EQ(9284, *list_val);


    EXPECT_EQ(73738, *dict1.found("Table"));
    EXPECT_EQ(9238, *dict1.found("OOP"));
    EXPECT_EQ(38, *dict1.found("Hash-function"));
    EXPECT_EQ(3938, *dict1.found("Vector"));
    EXPECT_EQ(nullptr, dict1.found("Interface"));
    EXPECT_EQ(nullptr, dict1.found("List"));

    EXPECT_EQ(73898, *dict2.found("Interface"));
    EXPECT_EQ(11387, *dict2.found("Vector"));
    EXPECT_EQ(33928, *dict2.found("Hash-function"));
    EXPECT_EQ(9284, *dict2.found("List"));
    EXPECT_EQ(nullptr, dict2.found("Table"));
    EXPECT_EQ(nullptr, dict2.found("OOP"));
}

TEST(TestHashTableC, merge_dictionaries_empty_first) {
    // Arrange
    HashTableC<int> dict1;
    HashTableC<int> dict2;
    dict2.insert("key1", 100);
    dict2.insert("key2", 200);

    // Act
    HashTableC<int> result = merge_dictionaries(dict1, dict2);

    // Assert
    EXPECT_EQ(100, *result.found("key1"));
    EXPECT_EQ(200, *result.found("key2"));
    EXPECT_FALSE(result.is_empty());
}

TEST(TestHashTableC, merge_dictionaries_empty_second) {
    // Arrange
    HashTableC<int> dict1;
    dict1.insert("key1", 100);
    dict1.insert("key2", 200);
    HashTableC<int> dict2;

    // Act
    HashTableC<int> result = merge_dictionaries(dict1, dict2);

    // Assert
    EXPECT_EQ(100, *result.found("key1"));
    EXPECT_EQ(200, *result.found("key2"));
    EXPECT_FALSE(result.is_empty());
}

TEST(TestHashTableC, merge_dictionaries_both_empty) {
    // Arrange
    HashTableC<int> dict1;
    HashTableC<int> dict2;

    // Act
    HashTableC<int> result = merge_dictionaries(dict1, dict2);

    // Assert
    EXPECT_TRUE(result.is_empty());
}

TEST(TestHashTableC, merge_dictionaries_all_keys_are_unique) {
    // Arrange
    HashTableC<std::string> dict1;
    dict1.insert("A", "Apple");
    dict1.insert("B", "Banana");
    dict1.insert("C", "Cherry");

    HashTableC<std::string> dict2;
    dict2.insert("D", "Date");
    dict2.insert("E", "Elderberry");
    dict2.insert("F", "Fig");

    // Act
    HashTableC<std::string> result = merge_dictionaries(dict1, dict2);

    // Assert
    EXPECT_EQ("Apple", *result.found("A"));
    EXPECT_EQ("Banana", *result.found("B"));
    EXPECT_EQ("Cherry", *result.found("C"));
    EXPECT_EQ("Date", *result.found("D"));
    EXPECT_EQ("Elderberry", *result.found("E"));
    EXPECT_EQ("Fig", *result.found("F"));
}

TEST(TestHashTableC, insert_with_collision) {
    // Arrange
    HashTableC<int> table(5);

    // Act
    table.insert("abc", 1);
    table.insert("bca", 2);
    table.insert("cab", 3);

    // Assert
    const int* val1 = table.found("abc");
    const int* val2 = table.found("bca");
    const int* val3 = table.found("cab");
    ASSERT_NE(nullptr, val1);
    ASSERT_NE(nullptr, val2);
    ASSERT_NE(nullptr, val3);
    EXPECT_EQ(1, *val1);
    EXPECT_EQ(2, *val2);
    EXPECT_EQ(3, *val3);
}

TEST(TestHashTableC, erase_key_from_collision) {
    // Arrange
    HashTableC<int> table(5);
    table.insert("abc", 1);
    table.insert("bca", 2);
    table.insert("cab", 3);

    // Act
    table.erase("bca");

    // Assert
    const int* val1 = table.found("abc");
    const int* val2 = table.found("bca");
    const int* val3 = table.found("cab");

    ASSERT_NE(nullptr, val1);
    ASSERT_EQ(nullptr, val2);
    ASSERT_NE(nullptr, val3);

    EXPECT_EQ(1, *val1);
    EXPECT_EQ(3, *val3);
}

TEST(TestHashTableC, insert_after_erase_in_collision_chain) {
    // Arrange
    HashTableC<int> table(5);
    table.insert("abc", 1);
    table.insert("bca", 2);
    table.insert("cab", 3);
    table.erase("bca");

    // Act
    table.insert("acb", 4);

    // Assert
    const int* val1 = table.found("abc");
    const int* val2 = table.found("bca");
    const int* val3 = table.found("cab");
    const int* val4 = table.found("acb");

    ASSERT_NE(nullptr, val1);
    ASSERT_EQ(nullptr, val2);
    ASSERT_NE(nullptr, val3);
    ASSERT_NE(nullptr, val4);

    EXPECT_EQ(1, *val1);
    EXPECT_EQ(3, *val3);
    EXPECT_EQ(4, *val4);
}