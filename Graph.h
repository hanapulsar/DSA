#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

template<typename Vertex, typename Distance = double>
class Graph {
private:
	std::vector<Vertex> vertices;
	std::vector<std::vector<std::vector<Edge>>> matrix;

	int get_vertex_index(const Vetrex& v) const;

public:
	struct Edge {
		Vertex from;
		Vertex to;
		Distance distance;
	};

	bool has_vertex(const Vertex& v) const;
	bool add_vertex(const Vertex& v);
	bool remove_vertex(const Vertex& v);
	std::vector<Vertex> vertices() const;
};

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::has_vertex(const Vertex& v) const {
	
}

#endif // GRAPH_H