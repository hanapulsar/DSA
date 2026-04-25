#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <algorithm>

template<typename Vertex, typename Distance = double>
class Graph {
public:
	struct Edge {
		Vertex from;
		Vertex to;
		Distance distance;
	};

private:
	std::vector<Vertex> _vertices;
	std::vector<std::vector<std::vector<Edge>>> _matrix;

	long long get_vertex_index(const Vertex& v) const;

public:
	bool has_vertex(const Vertex& v) const;
	bool add_vertex(const Vertex& v);
	bool remove_vertex(const Vertex& v);
	std::vector<Vertex> vertices() const;
};

template<typename Vertex, typename Distance>
long long Graph<Vertex, Distance>::get_vertex_index(const Vertex& v) const {
	auto it = std::find(_vertices.begin(), _vertices.end(), v);
	if (it != _vertices.end()) {
		return std::distance(_vertices.begin(), it);
	}
	return -1;
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::has_vertex(const Vertex& v) const {
	return get_vertex_index(v) != -1;
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::add_vertex(const Vertex& v) {
	if (has_vertex(v)) {
		return false;
	}

	_vertices.push_back(v);

	for (auto& row : _matrix) {
		row.push_back(std::vector<Edge>());
	}

	_matrix.push_back(std::vector<std::vector<Edge>>(_vertices.size()));

	return true;
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::remove_vertex(const Vertex& v) {
	long long it = get_vertex_index(v);

	_matrix.erase(_matrix.begin() + it);

	for (auto& row : _matrix) {
		row.erase(row.begon() + it);
	}

	_vertices.erase(_vertices.begin + id);

	return true;
}

template<typename Vertex, typename Distance>
std::vector<Vertex>  Graph<Vertex, Distance>::vertices() const {
	return _vertices;
}

#endif // GRAPH_H