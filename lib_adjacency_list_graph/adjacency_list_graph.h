// Copyright 2026 Ekaterina Ushnitskaya

#ifndef LIB_ADJACENCY_LIST_GRAPH_ADJACENCY_LIST_GRAPH_H
#define LIB_ADJACENCY_LIST_GRAPH_ADJACENCY_LIST_GRAPH_H

#include <string>
#include <stdexcept>

#include "../lib_tvector/tvector.h"
#include "../lib_list/list.h"
#include "../lib_pair/pair.h"

template <class T>
class AdjacencyListGraph {
	TVector<List<Pair<T, int>>> _graph;
	bool _is_directed;
	bool _is_weighted;
public:
	AdjacencyListGraph(bool isDirected = false, bool isWeight = false);
	AdjacencyListGraph(const TVector<Pair<Pair<T, T>, int>>& edges, bool isDirected = false, bool isWeighted = false);

	void add_edge(const T& from, const T& to, int weight = 1);
	void delete_edge(const T& from, const T& to);
	void delete_vertex(const T& vertex);

	size_t count_vertex() const noexcept;
	void print() const noexcept;
private:
	int find_index(const T& vertex) const noexcept;
	bool is_edge_exists(size_t from_index, const T& to) const noexcept;
	void add_or_update_neighbor(size_t from_index, const T& to, int weight);
};

template <class T>
AdjacencyListGraph<T>::AdjacencyListGraph(bool isDirected, bool isWeighted) {
	_is_directed = isDirected;
	_is_weighted = isWeighted;
}

template <class T>
AdjacencyListGraph<T>::AdjacencyListGraph(const TVector<Pair<Pair<T, T>, int>>& edges, bool isDirected, bool isWeighted) {
	_is_directed = isDirected;
	_is_weighted = isWeighted;
	for (size_t i = 0; i < edges.size(); ++i) {
		add_edge(edges[i].first.first, edges[i].first.second, edges[i].second);
	}
}

template <class T>
int AdjacencyListGraph<T>::find_index(const T& vertex) const noexcept {
	for (size_t i = 0; i < _graph.size(); ++i) {
		if (_graph.state(i) != State::busy) { continue; }
		if (_graph[i].head() != nullptr && _graph[i].head()->value.first == vertex) {
			return i;
		}
	}
	return -1;
}

template <class T>
bool AdjacencyListGraph<T>::is_edge_exists(size_t from_index, const T& to) const noexcept {
	auto it = _graph[from_index].begin();
	if (it != _graph[from_index].end()) { it++; }
	for (; it != _graph[from_index].end(); ++it) {
		if ((*it).first == to) {
			return true;
		}
	}
	return false;
}

template <class T>
void AdjacencyListGraph<T>::add_or_update_neighbor(size_t from_index, const T& to, int weight) {
	auto it = _graph[from_index].begin();
	if (it != _graph[from_index].end()) { it++; }
	for (; it != _graph[from_index].end(); ++it) {
		if ((*it).first == to) {
			(*it).second = weight;
			return;
		}
	}
	_graph[from_index].push_back(Pair<T, int>(to, weight));
}

template <class T>
void AdjacencyListGraph<T>::add_edge(const T& from, const T& to, int weight) {
	if (!_is_weighted) { weight = 1; }
	int from_index = find_index(from);
	if (from_index == -1) {
		List<Pair<T, int>> list;
		list.push_back(Pair<T, int>(from, 0));
		_graph.push_back(list);
		from_index = (int)_graph.size() - 1;
	}
	if (from != to) {
		int to_index = find_index(to);
		if (to_index == -1) {
			List<Pair<T, int>> list;
			list.push_back(Pair<T, int>(to, 0));
			_graph.push_back(list);
			to_index = (int)_graph.size() - 1;
		}
		add_or_update_neighbor(from_index, to, weight);
		if (!_is_directed && from != to) {
			add_or_update_neighbor(to_index, from, weight);
		}
	}
	else {
		add_or_update_neighbor(from_index, to, weight);
	}
}

template <class T>
void AdjacencyListGraph<T>::delete_edge(const T& from, const T& to) {
	int from_index = find_index(from);
	if (from_index == -1) { throw std::invalid_argument("Edge doesn't exist"); }
	bool is_deleted = false;
	auto it = _graph[from_index].begin();
	if (it != _graph[from_index].end()) { it++; }
	size_t pos = 1;
	for (; it != _graph[from_index].end(); ++it) {
		if ((*it).first == to) {
			_graph[from_index].erase(pos);
			is_deleted = true;
			break;
		}
		pos++;
	}
	if (!is_deleted) { throw std::invalid_argument("Edge doesn't exist"); }
	if (!_is_directed && from != to) {
		int to_index = find_index(to);
		if (to_index != -1) {
			auto it_reverse = _graph[to_index].begin();
			if (it_reverse != _graph[to_index].end()) { it_reverse++; }
			size_t reverse_pos = 1;
			for (; it_reverse != _graph[to_index].end(); ++it_reverse) {
				if ((*it_reverse).first == from) {
					_graph[to_index].erase(reverse_pos);
					break;
				}
				reverse_pos++;
			}
		}
	}
}

template <class T>
void AdjacencyListGraph<T>::delete_vertex(const T& vertex) {
	int vertex_index = find_index(vertex);
	if (vertex_index == -1) { throw std::invalid_argument("Vertex doesn't exist"); }
	for (size_t i = 0; i < _graph.size(); ++i) {
		if (_graph.state(i) != State::busy) { continue; }
		if ((int)i == vertex_index) { continue; }
		auto it = _graph[i].begin();
		if (it != _graph[i].end()) { it++; }
		size_t pos = 1;
		for (; it != _graph[i].end(); ++it) {
			if ((*it).first == vertex) {
				_graph[i].erase(pos);
				break;
			}
			pos++;
		}
	}
	_graph.erase(vertex_index);
	_graph.shrink_to_fit();
}

template <class T>
size_t AdjacencyListGraph<T>::count_vertex() const noexcept {
	return _graph.size() - _graph.deleted();
}

template <class T>
void AdjacencyListGraph<T>::print() const noexcept {
	for (size_t i = 0; i < _graph.size(); ++i) {
		if (_graph.state(i) != State::busy) { continue; }
		auto it = _graph[i].begin();
		if (it == _graph[i].end()) { continue; }
		std::cout << (*it).first << ": ";
		it++;
		for (; it != _graph[i].end(); ++it) {
			std::cout << "(" << (*it).first;
			if (_is_weighted) {
				std::cout << ", " << (*it).second;
			}
			std::cout << ") ";
		}
		std::cout << std::endl;
	}
}

#endif // LIB_ADJACENCY_LIST_GRAPH_ADJACENCY_LIST_GRAPH_H