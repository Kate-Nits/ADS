// Copyright 2025 Ekaterina Ushnitskaya

#include <gtest/gtest.h>
#include "../lib_tvector/tvector.h"

#define EPSILON 0.000001
#define TRUE 1
#define FALSE 0

TEST(TestTVectorLib, default_constructor) {
    // Arrange (Настройка)
    TVector<int> vec;

    // Act & Assert
    EXPECT_EQ(nullptr, vec.data()); //проверяет что два переданные значения равны
    EXPECT_EQ(nullptr, vec.states());
    EXPECT_EQ(0, vec.size());
    EXPECT_EQ(0, vec.capacity());
    EXPECT_EQ(0, vec.deleted());
    EXPECT_TRUE(vec.is_empty()); 
}

TEST(TestTVectorLib, constructor_with_size) {
    // Arrange (Настройка)
    size_t size = 10;
    TVector<int> vec(size);

    // Act & Assert
    EXPECT_EQ(size, vec.size());
    EXPECT_EQ(size + TVector<int>::RESERVE_MEMORY, vec.capacity());
    EXPECT_EQ(0, vec.deleted());
    EXPECT_FALSE(vec.is_empty());
    for (size_t i = 0; i < size; i++) {
        EXPECT_EQ(State::busy, vec.state(i));
    }
    for (size_t i = size; i < vec.capacity(); i++) {
        EXPECT_EQ(State::empty, vec.state(i));
    }
}

TEST(TestTVectorLib, constructor_with_mass_all_parameters_are_good) {
    // Arrange (Настройка)
    size_t size = 3;
    int copy_mass[3] = { 1, 2, 3 };

    // Act 
    TVector<int> vec(copy_mass, size);

    // Assert
    EXPECT_EQ(size, vec.size());
    EXPECT_EQ(size + TVector<int>::RESERVE_MEMORY, vec.capacity());
    EXPECT_EQ(0, vec.deleted());
    EXPECT_FALSE(vec.is_empty());
    EXPECT_EQ(1, vec.data(0));
    EXPECT_EQ(2, vec.data(1));
    EXPECT_EQ(3, vec.data(2));
    for (size_t i = 0; i < size; i++) {
        EXPECT_EQ(State::busy, vec.state(i));
    }
    for (size_t i = size; i < vec.capacity(); i++) {
        EXPECT_EQ(State::empty, vec.state(i));
    }
}

TEST(TestTVectorLib, constructor_with_mass_with_nullptr_and_size_gt_zero) {
    // Arrange
    int* null_data = nullptr;

    // Act & Assert
    ASSERT_ANY_THROW(TVector<int> vec(null_data, 5));
}

TEST(TestTVectorLib, copy_constructor) {
    // Arrange
    int arr[4] = { 1, 2, 3, 4 };
    TVector<int> vec1(arr, 4);

    // Act
    TVector<int> vec2(vec1);

    // Assert
    EXPECT_EQ(vec1.size(), vec2.size());
    EXPECT_EQ(vec1.capacity(), vec2.capacity());
    EXPECT_EQ(vec1.deleted(), vec2.deleted());
    for (size_t i = 0; i < vec1.size(); i++) {
        EXPECT_EQ(vec1.data(i), vec2.data(i));
        EXPECT_EQ(vec1.state(i), vec2.state(i));
    }
}

TEST(TestTVectorLib, test_at_checking_without_difficulties) {
    // Arrange
    size_t size = 8;
    int arr[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    TVector<int> vec(arr, size);

    // Act & Assert
    EXPECT_EQ(4, vec.at(4));
}

TEST(TestTVectorLib, test_at_checking_with_pop_front) {
    // Arrange
    size_t size = 8;
    int arr[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    TVector<int> vec(arr, size);

    // Act
    vec.pop_front();

    // Assert
    EXPECT_EQ(1, vec.at(0));
}