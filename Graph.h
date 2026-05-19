#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <algorithm>
#include <functional>
#include <limits>
#include <fstream>
#include <cstdlib>
#include <filesystem>
#include <string>

template<typename Vertex, typename Distance = double>
class Graph {
public:
	struct Edge {
		Vertex from;
		Vertex to;
		Distance distance;

		Edge() : from(Vertex()), to(Vertex()), distance(Distance()) {}
		Edge(const Vertex& f, const Vertex& t, const Distance& d) : from(f), to(t), distance(d) {}
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
	std::vector<Edge> edges(const Vertex& vertex) const;

	size_t order() const;
	size_t degree(const Vertex& v) const;
	bool is_connected() const;

	std::vector<Edge> shortest_path(const Vertex& from, const Vertex& to) const;
	std::vector<Vertex> walk(const Vertex& start_vertex, std::function<void(const Vertex&)> action) const;

	Distance path_distance(const std::vector<Edge>& path) const;

	void print() const;
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

	for (std::vector<std::vector<Edge>>& row : _matrix) {
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

	for (std::vector<std::vector<Edge>>& row : _matrix) {
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

	Edge new_edge(from, to, d);
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
std::vector<typename Graph<Vertex, Distance>::Edge> Graph<Vertex, Distance>::edges(const Vertex& vertex) const {
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

template<typename Vertex, typename Distance>
size_t Graph<Vertex, Distance>::order() const {
	return _vertices.size();
}

template<typename Vertex, typename Distance>
size_t Graph<Vertex, Distance>::degree(const Vertex& v) const {
	long long idx = get_vertex_index(v);
	if (idx == -1) return 0;

	size_t count = 0;

	for (const auto& edges : _matrix[idx]) {
		count += edges.size();
	}

	for (const auto& rows : _matrix) {
		count += rows[idx].size();
	}

	return count;
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::is_connected() const {
	if (_vertices.empty()) return true;

	for (const auto& v : _vertices) {
		std::vector<Vertex> reached = walk(v, [](const Vertex&) {});
		if (reached.size() < _vertices.size()) return false;
	}

	return true;
}

template<typename Vertex, typename Distance>
std::vector<typename Graph<Vertex, Distance>::Edge> Graph<Vertex, Distance>::shortest_path(const Vertex& from, const Vertex& to) const {
	std::vector<Edge> path;

	long long start_idx = get_vertex_index(from);
	long long finish_idx = get_vertex_index(to);

	if (start_idx == -1 || finish_idx == -1) return path;

	size_t n = _vertices.size();
	Distance infinity = std::numeric_limits<Distance>::max();

	std::vector<Distance> distances(n, infinity);
	distances[start_idx] = 0;

	std::vector<Edge> prev_edge(n);

	for (size_t i = 0; i < n - 1; ++i) {
		bool is_updated = false;

		for (size_t u = 0; u < n; ++u) {
			if (distances[u] == infinity) continue;

			for (size_t v = 0; v < n; ++v) {
				for (const auto& edge : _matrix[u][v]) {
					if (distances[v] > edge.distance + distances[u]) {
						distances[v] = edge.distance + distances[u];
						prev_edge[v] = edge;
						is_updated = true;
					}
				}
			}
		}

		if (!is_updated) break;
	}

	if (distances[finish_idx] == infinity) return path;

	long long current = finish_idx;
	while (current != start_idx) {
		path.push_back(prev_edge[current]);
		current = get_vertex_index(prev_edge[current].from);
	}

	std::reverse(path.begin(), path.end());

	return path;
}

template<typename Vertex, typename Distance>
std::vector<Vertex> Graph<Vertex, Distance>::walk(const Vertex& start_vertex, std::function<void(const Vertex&)> action) const {
	std::vector<Vertex> result;
	long long start_idx = get_vertex_index(start_vertex);

	if (start_idx == -1) return result;

	std::vector<bool> visited(_vertices.size(), false);
	std::vector<size_t> queue;

	queue.push_back(static_cast<size_t>(start_idx));
	visited[static_cast<size_t>(start_idx)] = true;

	size_t head = 0;

	while (head < queue.size()) {
		size_t current_idx = queue[head];
		head++;
		const Vertex& current_vertex = _vertices[current_idx];

		action(current_vertex);
		result.push_back(current_vertex);

		for (size_t neighbor_idx = 0; neighbor_idx < _vertices.size(); ++neighbor_idx) {
			if (!_matrix[current_idx][neighbor_idx].empty() && !visited[neighbor_idx]) {
				visited[neighbor_idx] = true;
				queue.push_back(neighbor_idx);
			}
		}
	}

	return result;
}

template<typename Vertex, typename Distance>
Distance Graph<Vertex, Distance>::path_distance(const std::vector<Edge>& path) const {
	Distance distance = 0;
	for (const Edge& edge : path) {
		distance += edge.distance;
	}
	return distance;
}

template<typename Vertex, typename Distance>
void Graph<Vertex, Distance>::print() const {
	// 1. Сохраняем граф в файл в текущей рабочей директории (папке билда)
	std::ofstream out("graph_export.txt");
	if (!out.is_open()) {
		std::cerr << "Failed to open file for graph export.\n";
		return;
	}

	out << "VERTICES\n";
	for (const auto& v : _vertices) {
		out << v << "\n";
	}

	out << "EDGES\n";
	for (size_t u = 0; u < _matrix.size(); ++u) {
		for (size_t v = 0; v < _matrix[u].size(); ++v) {
			for (const auto& edge : _matrix[u][v]) {
				out << edge.from << ";" << edge.to << ";" << edge.distance << "\n";
			}
		}
	}
	out.close();

	// 2. Находим путь к скрипту Python
	// Макрос __FILE__ содержит полный путь к текущему файлу исходного кода (Graph.h)
	std::filesystem::path header_path = __FILE__;
	std::filesystem::path source_dir = header_path.parent_path();
	std::filesystem::path script_path = source_dir / "draw_graph.py";

	// 3. Формируем команду для терминала
	// Кавычки нужны на случай, если в пути есть пробелы
	std::string command = "python \"" + script_path.string() + "\"";

	std::cout << "Drawing graph...\n";

	// 4. Запускаем скрипт
	int result = std::system(command.c_str());
	if (result != 0) {
		std::cerr << "Error running Python script. Command was: " << command << "\n";
	}
}

#endif // GRAPH_H