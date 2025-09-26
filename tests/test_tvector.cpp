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

TEST(TestTVectorLib, test_state_state_deleted) {
    // Arrange
    size_t size = 8;
    int arr[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    TVector<int> vec(arr, size);

    // Act
    vec.pop_front();

    // Assert
    EXPECT_EQ(State::deleted, vec.state(0));
}

TEST(TestTVectorLib, test_state_state_busy) {
    // Arrange
    size_t size = 8;
    int arr[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    TVector<int> vec(arr, size);

    // Act & Assert
    EXPECT_EQ(State::busy, vec.state(4));
}

TEST(TestTVectorLib, test_state_state_empty) {
    // Arrange
    size_t size = 8;
    int arr[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    TVector<int> vec(arr, size);

    // Act & Assert
    EXPECT_EQ(State::empty, vec.state(size+1));
}

TEST(TestTVectorLib, test_begin_and_end) {
    // Arrange
    size_t size = 3;
    int arr[8] = { 11, 22, 37 };
    TVector<int> vec(arr, size);
    int sum = 0;

    // Act
    int* begin = vec.begin();
    int* end = vec.end();
    for (int* p = begin; p < end; ++p) {
        sum += *p;
    }

    // Assert
    EXPECT_EQ(11+22+37, sum);
}

TEST(TestTVectorLib, test_front_without_deleted_elements) {
    // Arrange
    size_t size = 3;
    int arr[8] = { 112, 234, 345 };
    TVector<int> vec(arr, size);

    // Act & Assert
    EXPECT_EQ(112, vec.front());
}

TEST(TestTVectorLib, test_front_with_deleted_element) {
    // Arrange
    size_t size = 3;
    int arr[8] = { 112, 234, 345 };
    TVector<int> vec(arr, size);

    // Act
    vec.pop_front();

    // Assert
    EXPECT_EQ(234, vec.front());
}

TEST(TestTVectorLib, test_back_without_deleted_elements) {
    // Arrange
    size_t size = 3;
    int arr[8] = { 112, 234, 345 };
    TVector<int> vec(arr, size);

    // Act & Assert
    EXPECT_EQ(345, vec.back());
}

TEST(TestTVectorLib, test_back_with_deleted_element) {
    // Arrange
    size_t size = 3;
    int arr[8] = { 112, 234, 345 };
    TVector<int> vec(arr, size);

    // Act
    vec.pop_back();

    // Assert
    EXPECT_EQ(234, vec.back());
}

TEST(TestTVectorLib, test_is_empty_real_empty_vec) {
    // Arrange
    TVector<int> vec;

    // Act & Assert
    EXPECT_TRUE(vec.is_empty());
}

TEST(TestTVectorLib, test_is_empty_not_empty_vec) {
    // Arrange
    TVector<int> vec(3);

    // Act & Assert
    EXPECT_FALSE(vec.is_empty());
}

TEST(TestTVectorLib, test_push_front) {
    // Arrange
    TVector<int> vec(3);
    vec[0] = 1;
    vec[1] = 2;
    vec[2] = 3;
    const State* states_vec = vec.states();

    // Act
    vec.push_front(777);

    // Assert
    EXPECT_EQ(4, vec.size());
    EXPECT_EQ(3 + vec.RESERVE_MEMORY, vec.capacity());
    EXPECT_TRUE(states_vec[3] == State::busy);
    EXPECT_EQ(777, vec[0]);
    EXPECT_EQ(3, vec[3]);
}

TEST(TestTVectorLib, test_push_back) {
    // Arrange
    TVector<int> vec(3);
    vec[0] = 1;
    vec[1] = 2;
    vec[2] = 3;
    const State* states_vec = vec.states();

    // Act
    vec.push_back(42);

    // Assert
    EXPECT_EQ(4, vec.size());
    EXPECT_EQ(3 + vec.RESERVE_MEMORY, vec.capacity());
    EXPECT_TRUE(states_vec[3] == State::busy);
    EXPECT_EQ(1, vec[0]);
    EXPECT_EQ(42, vec[3]);
}

TEST(TestTVectorLib, test_insert_without_deleted_elements) {
    // Arrange
    TVector<int> vec(3);
    vec[0] = 1;
    vec[1] = 2;
    vec[2] = 3;

    // Act
    vec.insert(1, 66);

    // Assert
    EXPECT_EQ(4, vec.size());
    EXPECT_EQ(1, vec[0]);
    EXPECT_EQ(66, vec[1]);
    EXPECT_EQ(2, vec[2]);
    EXPECT_EQ(3, vec[3]);
}

TEST(TestTVectorLib, test_insert_with_deleted_elements) {
    // Arrange
    size_t size = 5;
    int arr[5] = { 1, 6, 4, 5, 7 };
    TVector<int> vec(arr, size);

    // Act
    vec.erase(1);
    vec.insert(1, 667);

    // Assert
    EXPECT_EQ(5, vec.size());
    EXPECT_EQ(1, vec.at(0));
    EXPECT_EQ(667, vec.at(1));
    EXPECT_EQ(4, vec.at(2));
    EXPECT_EQ(5, vec.at(3));
    EXPECT_EQ(7, vec.at(4));
}

TEST(TestTVectorLib, test_pop_front) {
    // Arrange
    size_t size = 7;
    int arr[7] = { 10, 20, 30, 10, 20, 30, 10 };
    TVector<int> vec(arr, size);
    const State* states_vec = vec.states();

    // Act
    vec.pop_front();

    // Assert
    EXPECT_TRUE(states_vec[0] == State::deleted && vec.size() == 7 && vec.deleted() == 1);
}

TEST(TestTVectorLib, test_pop_back_checking_without_difficulties) {
    // Arrange
    TVector<int> vec(3);
    vec[2] = 99;
    const State* states_vec = vec.states();

    // Act
    vec.pop_back();

    // Assert
    EXPECT_TRUE(states_vec[2] == State::empty && vec.size() == 2);
}

TEST(TestTVectorLib, test_pop_back_size_equal_0) {
    // Arrange
    TVector <int> vec;

    // Act & Assert
    ASSERT_ANY_THROW(vec.pop_back());
}

TEST(TestTVectorLib, test_erase) {
    // Arrange
    TVector<int> vec(9);
    const State* states_vec = vec.states();

    // Act
    vec.erase(1);

    // Assert
    EXPECT_TRUE(states_vec[1] == State::deleted);
}

TEST(TestTVectorLib, test_emplace) {
    // Arrange
    TVector<std::string> vec(3);

    // Act
    vec.emplace(0, std::string("hello"));

    // Assert
    EXPECT_EQ("hello", vec[0]);
}

TEST(TestTVectorLib, test_assign) {
    // Arrange
    size_t size = 3;
    TVector<int> vec1(size);
    vec1[0] = 1;
    vec1[1] = 2;
    vec1[2] = 3;

    // Act
    TVector<int> vec2;
    vec2.assign(vec1);

    // Assert
    EXPECT_EQ(1, vec2[0]);
    EXPECT_EQ(2, vec2[1]);
    EXPECT_EQ(3, vec2[2]);
}

TEST(TestTVectorLib, test_operator_equal) {
    // Arrange
    size_t size = 3;
    TVector<int> vec1(size);
    vec1[0] = 100;
    vec1[1] = 200;
    vec1[2] = 369;

    // Act
    TVector<int> vec2;
    vec2 = vec1;

    // Assert
    EXPECT_EQ(100, vec2[0]);
    EXPECT_EQ(200, vec2[1]);
    EXPECT_EQ(369, vec2[2]);
}

TEST(TestTVectorLib, test_clear) {
    // Arrange
    size_t size = 5;
    TVector<int> vec(size);
    const State* vec_states = vec.states();
    
    // Act
    vec.clear();

    // Assert
    for (size_t i = 0; i < size; ++i) { EXPECT_EQ(State::empty, vec_states[i]); }
    EXPECT_EQ(0, vec.size());
    EXPECT_EQ(0, vec.deleted());
}

TEST(TestTVectorLib, can_compare_with_operator_two_equal_object) {
    // Arrange
    size_t size = 2;
    TVector<int> vec1(size);
    vec1[0] = 5;
    vec1[1] = 6;
    TVector<int> vec2(size);
    vec2[0] = 5;
    vec2[1] = 6;

    // Act & Assert
    EXPECT_TRUE(vec1 == vec2);
}

TEST(TestTVectorLib, can_compare_with_operator_two_not_equal_object) {
    // Arrange
    size_t size = 2;
    TVector<int> vec1(size);
    vec1[0] = 5;
    vec1[1] = 6;
    TVector<int> vec2(size);
    vec2[0] = 5;
    vec2[1] = 7;

    // Act & Assert
    EXPECT_FALSE(vec1 == vec2);
}

TEST(TestTVectorLib, can_compare_with_operator_that_says_that_two_objects_are_not_equal_return_true) {
    // Arrange
    size_t size = 2;
    TVector<int> vec1(size);
    vec1[0] = 5;
    vec1[1] = 6;
    TVector<int> vec2(size);
    vec2[0] = 3;
    vec2[1] = -4;

    // Act & Assert
    EXPECT_TRUE(vec1 != vec2);
}

TEST(TestTVectorLib, can_compare_with_operator_that_says_that_two_objects_are_not_equal_return_fale) {
    // Arrange
    size_t size = 2;
    TVector<int> vec1(size);
    vec1[0] = 5;
    vec1[1] = 6;
    TVector<int> vec2(size);
    vec2[0] = 5;
    vec2[1] = 6;

    // Act & Assert
    EXPECT_FALSE(vec1 != vec2);
}

TEST(TestTVectorLib, test_reserve_new_capacity_more_than_old_capacity) {
    // Arrange
    TVector<int> vec(3);
    size_t old_capacity = vec.capacity();
    size_t new_capacity = old_capacity + 10;

    // Act
    vec.reserve(new_capacity);

    // Assert
    EXPECT_TRUE(vec.capacity() >= new_capacity);
}

TEST(TestTVectorLib, test_reserve_no_change_if_new_capacity_less_than_old_capacity) {
    // Arrange
    TVector<int> vec(4);
    size_t old_capacity = vec.capacity();

    // Act
    vec.reserve(old_capacity - 1);

    // Assert
    EXPECT_TRUE(vec.capacity() == old_capacity);
}

TEST(TestTVectorLib, test_resize) {
    // Arrange
    TVector<int> vec(3);
    vec[0] = 10;
    vec[1] = 20;
    vec[2] = 30;
    const State* states = vec.states();

    // Act
    vec.resize(5);

    // Assert
    EXPECT_EQ(5, vec.size());
    EXPECT_EQ(10, vec[0]);
    EXPECT_EQ(20, vec[1]);
    EXPECT_EQ(30, vec[2]);
    EXPECT_EQ(busy, states[3]);
    EXPECT_EQ(busy, states[4]);
}

TEST(TestTVectorLib, test_shuffle) {
    // Arrange
    size_t size = 5;
    TVector<int> vec(size);
    for (int i = 0; i < size; ++i) { vec[i] = i; }
    TVector<int> old_vec(vec);

    // Act
    shuffle(vec);

    // Assert
    EXPECT_TRUE(old_vec != vec);
}

TEST(TestTVectorLib, test_quick_sort) {
    // Arrange
    size_t size = 5;
    int arr_not_sort[5] = { 5, 3, 4, 1, 2 };
    int arr_sort[5] = { 1, 2, 3, 4, 5 };
    TVector<int> not_sort_vec(arr_not_sort, size);
    TVector<int> sort_vec(arr_sort, size);

    // Act
    quick_sort(not_sort_vec);

    // Assert
    EXPECT_TRUE(sort_vec == not_sort_vec);
}