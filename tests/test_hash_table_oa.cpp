// Copyright 2026 Ekaterina Ushnitskaya

#include <gtest/gtest.h>
#include "../lib_hash_table_oa/hash_table_oa.h"

#define EPSILON 0.000001
#define TRUE 1
#define FALSE 0

TEST(TestHashTableOA, default_constructor) {
    // Arrange & Act
    HashTableOA<int> table;

    // Assert
    EXPECT_TRUE(table.is_empty());
    EXPECT_FALSE(table.is_full());
}

TEST(TestHashTableOA, constructor_with_size) {
    // Arrange & Act
    HashTableOA<int> table(31);

    // Assert
    EXPECT_TRUE(table.is_empty());
    EXPECT_FALSE(table.is_full());
}

TEST(TestHashTableOA, constructor_with_size_returns_throws) {
    // Arrange & Act & Assert
    ASSERT_ANY_THROW(HashTableOA<int> table(1));
}

TEST(TestHashTableOA, insert_one_element) {
    // Arrange
    HashTableOA<std::string> table;

    // Act
    table.insert("key1", "value1");

    // Assert
    EXPECT_FALSE(table.is_empty());
    const std::string* val = table.found("key1");
    ASSERT_NE(nullptr, val);
    EXPECT_EQ("value1", *val);
}

TEST(TestHashTableOA, insert_multiple_elements) {
    // Arrange
    HashTableOA<int> table(31);

    // Act
    table.insert("a", 1);
    table.insert("b", 2);
    table.insert("c", 3);

    // Assert
    EXPECT_EQ(1, *table.found("a"));
    EXPECT_EQ(2, *table.found("b"));
    EXPECT_EQ(3, *table.found("c"));
}

TEST(TestHashTableOA, insert_duplicate_key_returns_throws) {
    // Arrange
    HashTableOA<int> table;

    // Act
    table.insert("key", 100);

    // Assert
    ASSERT_ANY_THROW(table.insert("key", 200));
}

TEST(TestHashTableOA, insert_when_hash_table_is_full_returns_throws) {
    // Arrange
    HashTableOA<int> table(3);
    table.insert("k1", 1);
    table.insert("k2", 2);
    table.insert("k3", 3);

    // Act & Assert
    ASSERT_ANY_THROW(table.insert("k4", 4));
}

TEST(TestHashTableOA, erase_one_simple_key) {
    // Arrange
    HashTableOA<int> table;
    table.insert("key", 42);

    // Act
    table.erase("key");

    // Assert
    EXPECT_EQ(nullptr, table.found("key"));
    EXPECT_TRUE(table.is_empty());
}

TEST(TestHashTableOA, erase_one_nonexistent_key_returns_throws) {
    // Arrange
    HashTableOA<int> table;
    table.insert("exists", 1);

    // Act & Assert
    ASSERT_ANY_THROW(table.erase("not_exists"));
}

TEST(TestHashTableOA, erase_and_insert_same_key) {
    // Arrange
    HashTableOA<int> table;
    table.insert("key", 100);
    table.erase("key");

    // Act
    table.insert("key", 200);

    // Assert
    const int* val = table.found("key");
    ASSERT_NE(nullptr, val);
    EXPECT_EQ(200, *val);
}

TEST(TestHashTableOA, erase_all_elements) {
    // Arrange
    HashTableOA<int> table(31);
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

TEST(TestHashTableOA, found_one_simple_key) {
    // Arrange
    HashTableOA<double> table;
    table.insert("number", 3.14159);

    // Act
    const double* val = table.found("number");

    // Assert
    ASSERT_NE(nullptr, val);
    EXPECT_DOUBLE_EQ(3.14159, *val);
}

TEST(TestHashTableOA, found_nonexistent_key_returns_nullptr) {
    // Arrange
    HashTableOA<int> table;
    table.insert("key1", 1);

    // Act
    const int* val = table.found("key2");

    // Assert
    EXPECT_EQ(nullptr, val);
}

TEST(TestHashTableOA, found_after_erase_returns_nullptr) {
    // Arrange
    HashTableOA<int> table;
    table.insert("key", 123);
    table.erase("key");

    // Act
    const int* val = table.found("key");

    // Assert
    EXPECT_EQ(nullptr, val);
}

TEST(TestHashTableOA, is_empty_new_empty_table) {
    // Arrange & Act
    HashTableOA<int> table;

    // Assert
    EXPECT_TRUE(table.is_empty());
    EXPECT_FALSE(table.is_full());
}

TEST(TestHashTableOA, is_empty_after_insert) {
    // Arrange 
    HashTableOA<int> table;

    // Act
    table.insert("key", 1);

    // Assert
    EXPECT_FALSE(table.is_empty());
}

TEST(TestHashTableOA, is_full_on_full_table) {
    // Arrange & Act
    HashTableOA<int> table(3);
    table.insert("k1", 1);
    table.insert("k2", 2);
    table.insert("k3", 3);

    // Assert
    EXPECT_TRUE(table.is_full());
}

TEST(TestHashTableOA, is_not_full_after_erase) {
    // Arrange
    HashTableOA<int> table(3);
    table.insert("k1", 1);
    table.insert("k2", 2);
    table.insert("k3", 3);
    EXPECT_TRUE(table.is_full());

    // Act
    table.erase("k2");

    // Assert
    EXPECT_FALSE(table.is_full());
}

TEST(TestHashTableOA, insert_with_collision) {
    // Arrange
    HashTableOA<int> table(5);

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

TEST(TestHashTableOA, erase_key_from_collision) {
    // Arrange
    HashTableOA<int> table(5);
    table.insert("abc", 1);
    table.insert("bca", 2);
    table.insert("cab", 3);

    // Act
    table.erase("bca");

    // Assert
    EXPECT_NE(nullptr, table.found("abc"));
    EXPECT_EQ(nullptr, table.found("bca"));
    EXPECT_NE(nullptr, table.found("cab"));
    EXPECT_EQ(1, *table.found("abc"));
    EXPECT_EQ(3, *table.found("cab"));
}

TEST(TestHashTableOA, insert_after_deleted_in_collision) {
    // Arrange
    HashTableOA<int> table(5);
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