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

TEST(TestTVectorLib, test_data_with_index) {
    // Arrange
    int arr[3] = { 11, 22, 33 };
    TVector<int> vec(arr, 3);

    // Act & Assert
    EXPECT_EQ(11, vec.data(0));
    EXPECT_EQ(22, vec.data(1));
    EXPECT_EQ(33, vec.data(2));
    ASSERT_ANY_THROW(vec.data(10)); // выход за границы
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

TEST(TestTVectorLib, test_size_setter_increase) { //увеличение
    // Arrange
    TVector<int> vec(2);

    // Act
    vec.size(5);

    // Assert
    EXPECT_EQ(5, vec.size());
    for (size_t i = 2; i < 5; i++) {
        EXPECT_EQ(State::busy, vec.state(i));
    }
}

TEST(TestTVectorLib, test_size_setter_decrease) {
    // Arrange
    TVector<int> vec(5);
    vec[0] = 99;

    // Act
    vec.size(2);

    // Assert
    EXPECT_EQ(2, vec.size());
    EXPECT_EQ(99, vec[0]); // проверка, что данные остались
}

TEST(TestTVectorLib, test_capacity_setter) {
    // Arrange
    TVector<int> vec(2);
    size_t old_capacity = vec.capacity();

    // Act
    vec.capacity(old_capacity + 20);

    // Assert
    EXPECT_TRUE(vec.capacity() >= old_capacity + 20);
}

/*
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
*/

TEST(TestTVectorLib, test_deleted_counter) {
    // Arrange
    TVector<int> vec(35);

    // Act
    vec.erase(1);
    vec.erase(2);

    // Assert
    EXPECT_EQ(2, vec.deleted());
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

TEST(TestTVectorLib, test_push_front_checking_without_difficulties) {
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

TEST(TestTVectorLib, test_push_front_with_reserve) {
    // Arrange
    TVector<int> vec(1);
    size_t vec_capacity = vec.capacity();
    for (size_t i = 0; i < vec_capacity; ++i) { // Заполнили до capacity
        vec.push_back(1);
    }

    // Act
    vec.push_front(0); // должно вызвать reserve()

    // Assert
    EXPECT_TRUE(vec[0] == 0 && vec_capacity <= vec.capacity());
}

TEST(TestTVectorLib, test_push_back_checking_without_difficulties) {
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

TEST(TestTVectorLib, test_push_back_with_reserve) {
    // Arrange
    TVector<int> vec(1);
    size_t vec_capacity1 = vec.capacity();
    for (size_t i = 0; i < vec_capacity1; ++i) { // Заполнили до capacity
        vec.push_back(1);
    }

    // Act
    vec.push_back(0); // должно вызвать reserve()

    // Assert
    EXPECT_TRUE(vec[vec.size() - 1] == 0 && vec_capacity1 <= vec.capacity());
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

TEST(TestTVectorLib, test_insert_with_reserve) {
    // Arrange
    TVector<int> vec(3);
    size_t vec_capacity = vec.capacity();
    for (size_t i = 0; i < vec_capacity; ++i) { // Заполнилa до capacity
        vec.insert(1, 5);
    }

    // Act
    vec.insert(1, 5);

    // Assert
    EXPECT_TRUE(vec[1] == 5 && vec_capacity <= vec.capacity());
}

TEST(TestTVectorLib, test_insert_out_of_range) {
    // Arrange
    TVector<int> vec(2);

    // Act
    vec.insert(1, 66);

    // Assert
    ASSERT_ANY_THROW(vec.insert(5, 999));
}

TEST(TestTVectorLib, test_pop_front_checking_without_difficulties) {
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

TEST(TestTVectorLib, test_pop_front_with_shrink_to_fit) {
    // Arrange
    TVector<int> vec(6);
    for (size_t i = 0; i < 1; ++i) {
        vec.erase(i); // deleted 1
    }
    // Act
    vec.pop_front();

    // Assert
    EXPECT_EQ(0, vec.deleted());
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

TEST(TestTVectorLib, test_erase_checking_without_difficulties) {
    // Arrange
    TVector<int> vec(9);
    const State* states_vec = vec.states();

    // Act
    vec.erase(1);

    // Assert
    EXPECT_TRUE(states_vec[1] == State::deleted);
}

TEST(TestTVectorLib, test_erase_with_shrink_to_fit) {
    // Arrange
    TVector<int> vec(20);

    // Act
    for (int i = 0; i < 4; ++i) { vec.erase(i); }

    // Assert
    EXPECT_EQ(0, vec.deleted());
    EXPECT_EQ(16, vec.size());
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

TEST(TestTVectorLib, test_operator_equal_for_empty_vectors) {
    // Arrange
    TVector<int> vec1;
    TVector<int> vec2;

    // Act & Assert
    EXPECT_TRUE(vec1 == vec2);
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

TEST(TestTVectorLib, test_shrink_to_fit) {
    // Arrange
    size_t size = 5;
    int arr[5] = { 10, 20, 30, 40, 50 };
    TVector<int> vec(arr, size);
    size_t old_capacity = vec.capacity();

    // Act
    vec.erase(1);
    vec.erase(3);
    vec.shrink_to_fit();

    // Assert
    EXPECT_TRUE(vec.capacity() < old_capacity);
    EXPECT_EQ(3, vec.size());
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

TEST(TestTVectorLib, test_find_first) {
    // Arrange
    size_t size = 5;
    int arr[5] = { 7, 3, 5, 3, 9 };
    TVector<int> vec(arr, size);

    // Act & Assert
    EXPECT_EQ(1, find_first(vec, 3));
}

TEST(TestTVectorLib, test_find_last) {
    // Arrange
    size_t size = 5;
    int arr[5] = { 7, 3, 5, 3, 9 };
    TVector<int> vec(arr, size);

    // Act & Assert
    EXPECT_EQ(3, find_last(vec, 3));
}

TEST(TestTVectorLib, test_find_all) {
    // Arrange
    size_t size = 6;
    int arr[6] = { 1, 2, 3, 2, 5, 2 };
    TVector<int> vec(arr, size);

    // Act
    size_t* result = find_all(vec, 2);

    // Assert
    EXPECT_TRUE(result[0] == 1 && result[1] == 3 && result[2] == 5);
    delete[] result; //спроси НУЖНО ли УДАЛЯТЬ????
}

TEST(TestTVectorLib, iteration_empty_vector) {
    // Arrange
    TVector<int> vec;

    // Act
    auto it = vec.begin();
    auto end_it = vec.end();

    // Assert
    EXPECT_EQ(it, end_it);
    int count = 0;
    while (it != end_it) {
        ++count;
        ++it;
    }
    EXPECT_EQ(0, count);
}

TEST(TestTVectorLib, write_iterator) {
    // Arrange
    TVector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    // Act
    int k = 2;
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        *it = *it * k;
        k++;
    }

    // Assert
    EXPECT_EQ(20, vec.at(0));
    EXPECT_EQ(60, vec.at(1));
    EXPECT_EQ(120, vec.at(2));
    auto it = vec.begin();
    EXPECT_EQ(*it, 20);
    ++it;
    EXPECT_EQ(*it, 60);
    ++it;
    EXPECT_EQ(*it, 120);
    ++it;
    EXPECT_EQ(it, vec.end());
}

TEST(TestTVectorLib, read_iterator) {
    // Arrange
    TVector<int> vec;
    vec.push_back(5);
    vec.push_back(15);
    vec.push_back(25);
    vec.push_back(35);
    vec.erase(1);

    // Act
    int sum = 0;
    int count = 0;
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        sum += *it;
        ++count;
    }

    // Assert
    EXPECT_EQ(3, count);
    EXPECT_EQ(65, sum);
}