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

	void add_edge(const Vertex& from, const Vertex& to, const Distance& d);
	bool remove_edge(const Vertex& from, const Vertex& to);
	bool remove_edge(const Edge& e);
	bool has_edge(const Vertex& from, const Vertex& to) const;
	bool has_edge(const Edge& e) const;
	std::vector<Edge> edges(const Vertex& vertex);
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
	long long idx = get_vertex_index(v);

	if (idx == -1) return false;

	_matrix.erase(_matrix.begin() + idx);

	for (auto& row : _matrix) {
		row.erase(row.begin() + idx);
	}

	_vertices.erase(_vertices.begin() + idx);

	return true;
}

template<typename Vertex, typename Distance>
std::vector<Vertex>  Graph<Vertex, Distance>::vertices() const {
	return _vertices;
}

template<typename Vertex, typename Distance>
void Graph<Vertex, Distance>::add_edge(const Vertex& from, const Vertex& to, const Distance& d) {
	long long idx_from = get_vertex_index(from);
	long long idx_to = get_vertex_index(to);

	if (idx_from == -1 || idx_to == -1) return;

	Edge new_edge = { from, to, d };
	_matrix[idx_from][idx_to].push_back(new_edge);
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::remove_edge(const Vertex& from, const Vertex& to) {
	long long idx_from = get_vertex_index(from);
	long long idx_to = get_vertex_index(to);

	if (idx_from == -1 || idx_to == -1) return false;

	if (_matrix[idx_from][idx_to].empty()) return false;

	_matrix[idx_from][idx_to].clear();
	return true;
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::remove_edge(const Edge& e) {
	long long idx_from = get_vertex_index(e.from);
	long long idx_to = get_vertex_index(e.to);

	if (idx_from == -1 || idx_to == -1) return false;

	auto& edges = _matrix[idx_from][idx_to]; //std::vector<Edge>&
	//for (typename std::vector<Edge>::iterator it = edges.begin(); it != edges.end(); ++it) {}
	for (auto it = edges.begin(); it != edges.end(); ++it) {
		if (it->distance == e.distance) {
			edges.erase(it);
			return true;
		}
	}

	return false;
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::has_edge(const Vertex& from, const Vertex& to) const {
	long long idx_from = get_vertex_index(from);
	long long idx_to = get_vertex_index(to);

	if (idx_from == -1 || idx_to == -1) return false;

	return !_matrix[idx_from][idx_to].empty();
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::has_edge(const Edge& e) const {
	long long idx_from = get_vertex_index(e.from);
	long long idx_to = get_vertex_index(e.to);

	if (idx_from == -1 || idx_to == -1) return false;

	for (const auto& edge : _matrix[idx_from][idx_to]) {
		if (edge.distance == e.distance) {
			return true;
		}
	}

	return false;
}

template<typename Vertex, typename Distance>
std::vector<typename Graph<Vertex, Distance>::Edge> Graph<Vertex, Distance>::edges(const Vertex& vertex) {
	std::vector<Edge> result;
	long long idx = get_vertex_index(vertex);

	if (idx == -1) return result;

	for (const auto& edges : _matrix[idx]) {
		for (const auto& edge : edges) {
			result.push_back(edge);
		}
	}

	return result;
}

#endif // GRAPH_H