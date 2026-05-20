// Copyright 2026 Ekaterina Ushnitskaya

#ifndef LIB_EDGES_LIST_GRAPH_EDGES_LIST_GRAPH_H
#define LIB_EDGES_LIST_GRAPH_EDGES_LIST_GRAPH_H

#include <iostream>
#include <stdexcept>

#include "../lib_tvector/tvector.h"
#include "../lib_pair/pair.h"

template <class T>
class EdgesListGraph {
	TVector<Pair<Pair<T, T>, int>> _edges;
	bool _is_directed;
	bool _is_weighted;
public:
	EdgesListGraph(bool isDirected = false, bool isWeight = false);
	EdgesListGraph(const TVector<Pair<Pair<T, T>, int>>& graph, bool isDirected = false, bool isWeighted = false);

	void add_edge(const T& from, const T& to, int value_weight = 1);
	void delete_edge(const T& from, const T& to);
	void delete_vertex(const T& vertex);

	void print() const noexcept;
private:
	bool is_vertex_exists(const T& vertex) const noexcept;
};

template <class T>
EdgesListGraph<T>::EdgesListGraph(bool isDirected, bool isWeight) : _is_directed(isDirected), _is_weighted(isWeight) {}

template <class T>
EdgesListGraph<T>::EdgesListGraph(const TVector<Pair<Pair<T, T>, int>>& graph, bool isDirected, bool isWeighted) : _is_directed(isDirected), _is_weighted(isWeighted) {
	for (size_t i = 0; i < graph.size(); ++i) {
		add_edge(graph[i].first.first, graph[i].first.second, graph[i].second);
	}
}

template <class T>
void EdgesListGraph<T>::add_edge(const T& from, const T& to, int value_weight) {
	int weight;
	if (_is_weighted) {
		weight = value_weight;
	}
	else {
		weight = 1;
	}
	if (!_edges.is_empty()) {
		if (!is_vertex_exists(from) && !is_vertex_exists(to)) { throw std::invalid_argument("Cannot create unconnected edge!"); }
	}
	for (size_t i = 0; i < _edges.size(); ++i) {
		if (_edges[i].first.first == from && _edges[i].first.second == to) {
			_edges[i].second = weight;
			return;
		}
	}
	_edges.push_back(Pair<Pair<T, T>, int>(Pair<T, T>(from, to), weight));
	if (!_is_directed && from != to) {
		for (size_t i = 0; i < _edges.size(); ++i) {
			if (_edges[i].first.first == to && _edges[i].first.second == from) { return; }
		}
		_edges.push_back(Pair<Pair<T, T>, int>(Pair<T, T>(to, from), weight));
	}
}

template <class T>
void EdgesListGraph<T>::delete_edge(const T& from, const T& to) {
	if (_edges.is_empty()) { throw std::invalid_argument("EdgesListGraph is empty!"); }
	bool is_found = false;
	for (size_t i = 0; i < _edges.size(); ++i) {
		if (_edges[i].first.first == from && _edges[i].first.second == to) {
			_edges.erase(i);
			is_found = true;
			break;
		}
	}
	if (!is_found) { throw std::invalid_argument("Edge doesn't exist!"); }
	if (!_is_directed && from != to) {
		for (size_t i = 0; i < _edges.size(); ++i) {
			if (_edges[i].first.first == to && _edges[i].first.second == from) {
				_edges.erase(i);
				break;
			}
		}
	}
}

template <class T>
void EdgesListGraph<T>::delete_vertex(const T& vertex) {
	if (_edges.is_empty()) { throw std::invalid_argument("EdgesListGraph is empty!"); }
	bool is_found = false;
	for (int i = (int)_edges.size() - 1; i >= 0; --i) {
		if (_edges[i].first.first == vertex || _edges[i].first.second == vertex) {
			_edges.erase(i);
			is_found = true;
		}
	}
	if (!is_found) { throw std::invalid_argument("Vertex doesn't exist!"); }
}

template <class T>
void EdgesListGraph<T>::print() const noexcept {
	for (size_t i = 0; i < _edges.size(); ++i) {
		std::cout << "(" << _edges[i].first.first << ", " << _edges[i].first.second << ")";
		if (_is_weighted) { std::cout << " weight=" << _edges[i].second; }
		if (i != _edges.size() - 1) { std::cout << " -> "; }
	}
	std::cout << std::endl;
}

template <class T>
bool EdgesListGraph<T>::is_vertex_exists(const T& vertex) const noexcept {
	for (size_t i = 0; i < _edges.size(); ++i) {
		if (_edges[i].first.first == vertex || _edges[i].first.second == vertex) {
			return true;
		}
	}
	return false;
}

#endif // LIB_EDGES_LIST_GRAPH_EDGES_LIST_GRAPH_H