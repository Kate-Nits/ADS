// Copyright 2025 Ekaterina Ushnitskaya

#include <gtest/gtest.h>
#include "../lib_mathvector/MathVector.h"

#define EPSILON 0.000001
#define TRUE 1
#define FALSE 0

TEST(TestMathVectorLib, default_constructor) {
    // Arrange & Act
    MathVector<int> vec;

    // Assert
    EXPECT_EQ(nullptr, vec.data()); //проверяет что два переданные значения равны
    EXPECT_EQ(nullptr, vec.states());
    EXPECT_EQ(0, vec.size());
    EXPECT_EQ(0, vec.capacity());
    EXPECT_EQ(0, vec.deleted());
    EXPECT_TRUE(vec.is_empty());
}

TEST(TestMathVectorLib, constructor_with_size) {
    // Arrange (Настройка)
    size_t size = 10;

    // Act
    MathVector<int> vec(size);

    // Assert
    EXPECT_EQ(size, vec.size());
    EXPECT_EQ(size + MathVector<int>::RESERVE_MEMORY, vec.capacity());
    EXPECT_EQ(0, vec.deleted());
    EXPECT_FALSE(vec.is_empty());
    for (size_t i = 0; i < size; i++) {
        EXPECT_EQ(State::busy, vec.state(i));
    }
    for (size_t i = size; i < vec.capacity(); i++) {
        EXPECT_EQ(State::empty, vec.state(i));
    }
}

TEST(TestMathVectorLib, constructor_with_mass_all_parameters_are_good) {
    // Arrange (Настройка)
    size_t size = 3;
    int copy_mass[3] = { 1, 2, 3 };

    // Act 
    MathVector<int> vec(copy_mass, size);

    // Assert
    EXPECT_EQ(size, vec.size());
    EXPECT_EQ(size + MathVector<int>::RESERVE_MEMORY, vec.capacity());
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

TEST(TestMathVectorLib, constructor_with_mass_with_nullptr_and_size_gt_zero) {
    // Arrange
    int* null_data = nullptr;

    // Act & Assert
    ASSERT_ANY_THROW(MathVector<int> vec(null_data, 5));
}

TEST(TestMathVectorLib, copy_constructor) {
    // Arrange
    int arr[4] = { 1, 2, 3, 4 };
    MathVector<int> vec1(arr, 4);

    // Act
    MathVector<int> vec2(vec1);

    // Assert
    EXPECT_EQ(vec1.size(), vec2.size());
    EXPECT_EQ(vec1.capacity(), vec2.capacity());
    EXPECT_EQ(vec1.deleted(), vec2.deleted());
    for (size_t i = 0; i < vec1.size(); i++) {
        EXPECT_EQ(vec1.data(i), vec2.data(i));
        EXPECT_EQ(vec1.state(i), vec2.state(i));
    }
}

TEST(TestMathVectorLib, test_constructor_list_checking_without_problems) {
    // Arrange & Act
    MathVector<int> vec{ 1, 2, 3 };

    // Assert
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}

TEST(TestMathVectorLib, test_constructor_list_empty_init) {
    // Arrange & Act
    MathVector<int> vec{};

    // Assert
    EXPECT_EQ(vec.size(), 0);
    EXPECT_TRUE(vec.is_empty());
}

TEST(TestMathVectorLib, test_constructor_list_double_init) {
    // Arrange & Act
    MathVector<double> vec{ 1.1, 2.2, 3.3, 4.4 };

    // Assert
    EXPECT_EQ(vec.size(), 4);
    EXPECT_EQ(vec[0], 1.1);
    EXPECT_EQ(vec[1], 2.2);
    EXPECT_EQ(vec[2], 3.3);
    EXPECT_EQ(vec[3], 4.4);
}