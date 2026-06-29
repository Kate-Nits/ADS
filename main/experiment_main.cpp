// Copyright 2026 Ekaterina Ushnitskaya

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "../lib_pair/pair.h"
#include "../lib_polynom/polynom.h"
#include "../lib_sorted_table_on_array/sorted_table_on_array.h"
#include "../lib_unsorted_table_on_array/unsorted_table_on_array.h"
#include "../lib_unsorted_table_on_list/unsorted_table_on_list.h"
#include "../lib_unsorted_table_on_tree/unsorted_table_on_tree.h"
#include "../lib_sorted_table_on_bstree/sorted_table_on_bstree.h"
#include "../lib_sorted_table_on_avltree/sorted_table_on_avltree.h"
#include "../lib_sorted_table_on_rbtree/sorted_table_on_rbtree.h"
#include "../lib_hash_table_c/hash_table_c.h"
#include "../lib_hash_table_oa/hash_table_oa.h"

//#define UNSORTED_ARRAY
//#define UNSORTED_LIST
//#define UNSORTED_TREE

//#define SORTED_ARRAY
//#define SORTED_BSTREE
//#define SORTED_AVLTREE
//#define SORTED_RBTREE

//#define HASH_TABLE_C
//#define HASH_TABLE_OA

//#define MAIN

double my_pow(double value, int power) {
    double result = 1.0;

    if (power < 0) {
        for (int i = 0; i < -power; i++) {
            result *= value;
        }
        return 1.0 / result;
    }

    for (int i = 0; i < power; i++) {
        result *= value;
    }

    return result;
}

namespace Parser {
    bool is_digit(char symbol) {
        return symbol >= '0' && symbol <= '9';
    }
}

#define COUNT_EXPERIMENT 10

struct ExperimentResult {
	std::string table_name;
	int size;

	double avg_insert;
	double avg_found_existing;
	double avg_found_not_existing;
	double avg_found_all;
	double avg_erase;
};

std::string make_monom_string(double coeff, int px, int py, int pz) {
	std::ostringstream out;
	out << coeff;
	if (px != 0) { out << "x^" << px; }
	if (py != 0) { out << "y^" << py; }
	if (pz != 0) { out << "z^" << pz; }
	return out.str();
}

bool read_int_from_stream(std::stringstream& ss, int& value) {
	std::string str;
	if (!std::getline(ss, str, ',')) { return false; }
	if (str.empty()) { return false; }
	value = std::stoi(str);
	return true;
}

bool parse_polynom_line(const std::string& line, Pair<std::string, Polynom>& result) {
    if (line.empty()) { return false; }
    size_t sep_pos = line.find(';');
    if (sep_pos == std::string::npos) { return false; }

    std::string name = line.substr(0, sep_pos);
    std::string rest = line.substr(sep_pos + 1);

    if (name.empty() || rest.empty()) { return false; }

    std::stringstream ss(rest);
    std::string monom_str;
    std::ostringstream polynom_expression;

    bool is_first_monom = true;

    while (std::getline(ss, monom_str, ';')) {
        if (monom_str.empty()) { continue; }

        std::stringstream monom_ss(monom_str);

        int coeff = 0;
        int px = 0;
        int py = 0;
        int pz = 0;

        bool correct_monom =
            read_int_from_stream(monom_ss, coeff) &&
            read_int_from_stream(monom_ss, px) &&
            read_int_from_stream(monom_ss, py) &&
            read_int_from_stream(monom_ss, pz);

        if (!correct_monom) { continue; }

        if (!is_first_monom && coeff >= 0) { polynom_expression << "+"; }

        polynom_expression << make_monom_string(coeff, px, py, pz);
        is_first_monom = false;
    }

    if (is_first_monom) { return false; }

    result = Pair<std::string, Polynom>(name, Polynom(polynom_expression.str()));
    return true;
}

std::vector<Pair<std::string, Polynom>> read_polynoms_from_file(const std::string& file_name) {
    std::ifstream in(file_name);
    if (!in.is_open()) { throw std::runtime_error("File polynoms.txt is not opened"); }
    std::vector<Pair<std::string, Polynom>> polynoms;
    std::string line;
    while (std::getline(in, line)) {
        Pair<std::string, Polynom> cur;
        if (parse_polynom_line(line, cur)) { polynoms.push_back(cur); }
    }
    return polynoms;
}

double average(const std::vector<double>& values) {
    if (values.empty()) { return 0.0; }
    double sum = 0.0;
    for (double value : values) {
        sum += value;
    }
    return sum / values.size();
}

void print_result(std::ostream& out, const ExperimentResult& result) {
    out << "Таблица: " << result.table_name << "\n";
    out << "Размер: " << result.size << "\n";
    out << "Среднее время вставки: " << result.avg_insert << " сек.\n";
    out << "Среднее время поиска существующего ключа: "
        << result.avg_found_existing << " сек.\n";
    out << "Среднее время поиска несуществующего ключа: "
        << result.avg_found_not_existing << " сек.\n";
    out << "Среднее время поиска общее: "
        << result.avg_found_all << " сек.\n";
    out << "Среднее время удаления: " << result.avg_erase << " сек.\n";
    out << "----------------------------------------\n";
}

void print_csv_header(std::ostream& out) {
    out << "table;size;avg_insert;avg_found_existing;avg_found_not_existing;avg_found_all;avg_erase\n";
}

void print_csv_result(std::ostream& out, const ExperimentResult& result) {
    out << result.table_name << ";"
        << result.size << ";"
        << result.avg_insert << ";"
        << result.avg_found_existing << ";"
        << result.avg_found_not_existing << ";"
        << result.avg_found_all << ";"
        << result.avg_erase << "\n";
}

void save_result(std::ofstream& txt_out, std::ofstream& csv_out, const ExperimentResult& result) {
    print_result(std::cout, result);
    print_result(txt_out, result);
    print_csv_result(csv_out, result);

    txt_out.flush();
    csv_out.flush();
}

template <class TTable>
ExperimentResult run_experiment(const std::string& table_name, int size, const std::vector<Pair<std::string, Polynom>>& polynoms) {
    TTable table;
    std::vector<std::string> exist_keys;
    for (int i = 0; i < size; i++) {
        table.insert(polynoms[i].first, polynoms[i].second);
        exist_keys.push_back(polynoms[i].first);
    }

    std::mt19937 generator(42);
    std::shuffle(exist_keys.begin(), exist_keys.end(), generator);

    std::vector<double> insert_times;
    std::vector<double> found_existing_times;
    std::vector<double> found_not_existing_times;
    std::vector<double> erase_times;

    for (int i = 0; i < COUNT_EXPERIMENT; i++) { // Вставка
        int index = size + i;

        auto start = std::chrono::high_resolution_clock::now();
        table.insert(polynoms[index].first, polynoms[index].second);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> sec = end - start;
        insert_times.push_back(sec.count());

        table.erase(polynoms[index].first);
    }

    for (int i = 0; i < COUNT_EXPERIMENT; i++) { // Поиск существующих ключей
        auto start = std::chrono::high_resolution_clock::now();
        table.found(exist_keys[i]);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> sec = end - start;
        found_existing_times.push_back(sec.count());
    }

    for (int i = 0; i < COUNT_EXPERIMENT; i++) { // Поиск несуществующих ключей
        std::string not_existing_key = polynoms[size + i].first + "_NOT_EXIST";

        auto start = std::chrono::high_resolution_clock::now();
        table.found(not_existing_key);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> sec = end - start;
        found_not_existing_times.push_back(sec.count());
    }

    for (int i = 0; i < COUNT_EXPERIMENT; i++) { // Удаление
        std::string key = exist_keys[i];

        const Polynom* value = table.found(key);

        if (value == nullptr) { throw std::logic_error("Existing key was not found before erase"); }

        Polynom saved_value = *value;

        auto start = std::chrono::high_resolution_clock::now();
        table.erase(key);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> sec = end - start;
        erase_times.push_back(sec.count());

        table.insert(key, saved_value);
    }

    double total_found =
        average(found_existing_times) * COUNT_EXPERIMENT +
        average(found_not_existing_times) * COUNT_EXPERIMENT;

    ExperimentResult result;
    result.table_name = table_name;
    result.size = size;
    result.avg_insert = average(insert_times);
    result.avg_found_existing = average(found_existing_times);
    result.avg_found_not_existing = average(found_not_existing_times);
    result.avg_found_all = total_found / (COUNT_EXPERIMENT * 2);
    result.avg_erase = average(erase_times);
    return result;
}

ExperimentResult run_experiment_hash_table_oa( const std::string& table_name, int size, const std::vector<Pair<std::string, Polynom>>& polynoms) {
    HashTableOA<Polynom> table(size * 2);

    std::vector<std::string> exist_keys;

    for (int i = 0; i < size; i++) {
        table.insert(polynoms[i].first, polynoms[i].second);
        exist_keys.push_back(polynoms[i].first);
    }

    std::mt19937 generator(42);
    std::shuffle(exist_keys.begin(), exist_keys.end(), generator);

    std::vector<double> insert_times;
    std::vector<double> found_existing_times;
    std::vector<double> found_not_existing_times;
    std::vector<double> erase_times;

    for (int i = 0; i < COUNT_EXPERIMENT; i++) {
        int index = size + i;

        auto start = std::chrono::high_resolution_clock::now();
        table.insert(polynoms[index].first, polynoms[index].second);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> sec = end - start;
        insert_times.push_back(sec.count());

        table.erase(polynoms[index].first);
    }

    for (int i = 0; i < COUNT_EXPERIMENT; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        table.found(exist_keys[i]);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> sec = end - start;
        found_existing_times.push_back(sec.count());
    }

    for (int i = 0; i < COUNT_EXPERIMENT; i++) {
        std::string not_existing_key = polynoms[size + i].first + "_NOT_EXIST";

        auto start = std::chrono::high_resolution_clock::now();
        table.found(not_existing_key);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> sec = end - start;
        found_not_existing_times.push_back(sec.count());
    }

    for (int i = 0; i < COUNT_EXPERIMENT; i++) {
        std::string key = exist_keys[i];

        const Polynom* value = table.found(key);

        if (value == nullptr) { throw std::logic_error("Existing key was not found before erase"); }

        Polynom saved_value = *value;

        auto start = std::chrono::high_resolution_clock::now();
        table.erase(key);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> sec = end - start;
        erase_times.push_back(sec.count());

        table.insert(key, saved_value);
    }

    double total_found = average(found_existing_times) * COUNT_EXPERIMENT + average(found_not_existing_times) * COUNT_EXPERIMENT;

    ExperimentResult result;
    result.table_name = table_name;
    result.size = size;
    result.avg_insert = average(insert_times);
    result.avg_found_existing = average(found_existing_times);
    result.avg_found_not_existing = average(found_not_existing_times);
    result.avg_found_all = total_found / (COUNT_EXPERIMENT * 2);
    result.avg_erase = average(erase_times);

    return result;
}

#ifdef MAIN
int main() {
    setlocale(LC_ALL, "rus");

    const std::string file_name = "polynoms.txt";

    const int sizes[] = { 100, 1000, 10000, 100000 };
    //const int sizes[] = { 100000 };
    /*
    std::ofstream txt_out("experiment_results.txt");
    std::ofstream csv_out("experiment_results.csv");
    */
    std::ofstream txt_out("experiment_results.txt", std::ios::app);
    std::ofstream csv_out("experiment_results.csv", std::ios::app);

    if (!txt_out.is_open()) {
        std::cout << "Файл experiment_results.txt не открывается!\n";
        return 1;
    }

    if (!csv_out.is_open()) {
        std::cout << "Файл experiment_results.csv не открывается!\n";
        return 1;
    }
    try {
        std::vector<Pair<std::string, Polynom>> polynoms =
            read_polynoms_from_file(file_name);

        int max_size = sizes[sizeof(sizes) / sizeof(sizes[0]) - 1] + COUNT_EXPERIMENT;

        if ((int)polynoms.size() < max_size) {
            std::cout << "В файле недостаточно корректных полиномов!\n";
            std::cout << "Нужно минимум: " << max_size << "\n";
            std::cout << "Считано: " << polynoms.size() << "\n";
            return 1;
        }

        print_csv_header(csv_out);

        txt_out << std::fixed << std::setprecision(10);
        csv_out << std::fixed << std::setprecision(10);
        std::cout << std::fixed << std::setprecision(10);

        for (int size : sizes) {

#ifdef UNSORTED_ARRAY
            std::cout << "Start: UnsortedTableOnArray, size = " << size << std::endl;
            ExperimentResult unsorted_array_result = run_experiment<UnsortedTableOnArray<std::string, Polynom>>("UnsortedTableOnArray", size, polynoms);
            save_result(txt_out, csv_out, unsorted_array_result);
#endif // UNSORTED_ARRAY

#ifdef UNSORTED_LIST
            std::cout << "Start: UnsortedTableOnList, size = " << size << std::endl;
            ExperimentResult unsorted_list_result = run_experiment<UnsortedTableOnList<std::string, Polynom>>("UnsortedTableOnList", size, polynoms);
            save_result(txt_out, csv_out, unsorted_list_result);
#endif // UNSORTED_LIST

#ifdef UNSORTED_TREE
            std::cout << "Start: UnsortedTableOnTree, size = " << size << std::endl;
            ExperimentResult unsorted_tree_result = run_experiment<UnsortedTableOnTree<std::string, Polynom>>("UnsortedTableOnTree", size, polynoms);
            save_result(txt_out, csv_out, unsorted_tree_result);
#endif // UNSORTED_TREE            

#ifdef SORTED_ARRAY
            std::cout << "Start: SortedTableOnArray, size = " << size << std::endl;
            ExperimentResult sorted_array_result = run_experiment<SortedTableOnArray<std::string, Polynom>>("SortedTableOnArray", size, polynoms);
            save_result(txt_out, csv_out, sorted_array_result);
#endif // SORTED_ARRAY

#ifdef SORTED_BSTREE
            std::cout << "Start: SortedTableOnBSTree, size = " << size << std::endl;
            ExperimentResult sorted_bstree_result = run_experiment<SortedTableOnBSTree<std::string, Polynom>>("SortedTableOnBSTree", size, polynoms);
            save_result(txt_out, csv_out, sorted_bstree_result);
#endif // SORTED_BSTREE


#ifdef SORTED_AVLTREE
            std::cout << "Start: SortedTableOnAVLTree, size = " << size << std::endl;
            ExperimentResult sorted_avltree_result = run_experiment<SortedTableOnAVLTree<std::string, Polynom>>("SortedTableOnAVLTree", size, polynoms);
            save_result(txt_out, csv_out, sorted_avltree_result);
#endif // SORTED_AVLTREE

#ifdef SORTED_RBTREE
            std::cout << "Start: SortedTableOnRBTree, size = " << size << std::endl;
            ExperimentResult sorted_rbtree_result = run_experiment<SortedTableOnRBTree<std::string, Polynom>>("SortedTableOnRBTree", size, polynoms);
            save_result(txt_out, csv_out, sorted_rbtree_result);
#endif // SORTED_RBTREE

#ifdef HASH_TABLE_C
            std::cout << "Start: HashTableC, size = " << size << std::endl;
            ExperimentResult hash_table_c_result = run_experiment<HashTableC<Polynom>>("HashTableC", size, polynoms);
            save_result(txt_out, csv_out, hash_table_c_result);
#endif // HASH_TABLE_C

#ifdef HASH_TABLE_OA
            std::cout << "Start: HashTableOA, size = " << size << std::endl;
            ExperimentResult hash_table_oa_result = run_experiment_hash_table_oa("HashTableOA", size, polynoms);
            save_result(txt_out, csv_out, hash_table_oa_result);
#endif // HASH_TABLE_OA
        }

        std::cout << "Эксперимент завершен.\n";
        std::cout << "Результаты сохранены в experiment_results.txt и experiment_results.csv\n";
    }
    catch (const std::exception& error) {
        std::cout << "Ошибка: " << error.what() << "\n";
        return 1;
    }

    return 0;
}
#endif // MAIN