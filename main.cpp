#include <iostream>
#include <string>
#include <limits>
#include "Graph.h"

std::string find_optimal(const Graph<std::string, double>& g) {
	std::vector<std::string> points = g.vertices();
	if (points.empty()) return "";

	if (!g.is_connected()) return "Error: Graph is not connected.";

	std::string best_point = points[0];
	double min_max_distance = std::numeric_limits<double>::max();

	for (const std::string& point : points) {
		double current_max_distance = 0.0;

		for (const std::string& go_to_point : points) {
			if (point == go_to_point) continue;

			std::vector<Graph<std::string, double>::Edge> path = g.shortest_path(point, go_to_point);

			if (path.empty()) {
				current_max_distance = std::numeric_limits<double>::max();
				break;
			}

			double distance = g.path_distance(path);
			if (distance > current_max_distance) {
				current_max_distance = distance;
			}
		}

		if (current_max_distance < min_max_distance) {
			min_max_distance = current_max_distance;
			best_point = point;
		}
	}

	return best_point;
}

int main() {
	Graph<std::string, double> city;

	city.add_vertex("Center");
	city.add_vertex("North");
	city.add_vertex("South");
	city.add_vertex("South2");
	city.add_vertex("South3");
	city.add_vertex("East");
	city.add_vertex("West");

	city.add_edge("Center", "North", 1);
	city.add_edge("Center", "South", 13);
	city.add_edge("South", "South2", 7);
	city.add_edge("South2", "South", 7);
	city.add_edge("South2", "South3", 7);
	city.add_edge("Center", "East", 5);
	city.add_edge("Center", "West", 25);

	city.add_edge("North", "Center", 10);
	city.add_edge("South", "Center", 7);
	city.add_edge("East", "Center", 5);
	city.add_edge("West", "Center", 8);

	city.add_edge("North", "East", 10);
	city.add_edge("East", "South", 6);
	city.add_edge("South", "West", 9);
	city.add_edge("West", "North", 7);

	std::cout << "Test has_vertex (center): " << (city.has_vertex("Center") ? "Yes" : "No") << "\n";
	std::cout << "Test has_vertex (center2): " << (city.has_vertex("Center2") ? "Yes" : "No") << "\n";
	std::cout << "Test has_vertex (south3): " << (city.has_vertex("South3") ? "Yes" : "No") << "\n";
	std::cout << "Test has_vertex (south4): " << (city.has_vertex("South4") ? "Yes" : "No") << "\n";
	std::cout << "Test remove_vertex (south3): " << (city.remove_vertex("South3") ? "Yes" : "No") << '\n';
	std::cout << "Test remove_vertex (south4): " << (city.remove_vertex("South4") ? "Yes" : "No") << '\n';
	std::cout << "Test has_vertex (south3): " << (city.has_vertex("South3") ? "Yes" : "No") << "\n";
	std::cout << "Test has_vertex (south4): " << (city.has_vertex("South4") ? "Yes" : "No") << "\n";
	std::cout << "All vertices: ";
	for (const auto& v : city.vertices()) {
		std::cout << v << " ";
	}
	std::cout << "\n";

	std::cout << "BFS Walk from center: \n";
	city.walk("Center", [](const std::string& v) {
		std::cout << "Visited:" << v << "\n";
		});
	std::cout << "\n";

	std::cout << "Graph order: " << city.order() << "\n";
	std::cout << "Graph degree at center: " << city.degree("Center") << "\n";
	std::cout << "Is graph connected: " << (city.is_connected() ? "Yes" : "No") << "\n\n";

	std::cout << "Shortest from West to East: \n";
	auto path = city.shortest_path("West", "East");
	for (const auto& edge : path) {
		std::cout << edge.from << " -> " << edge.to << " ( distance: " << edge.distance << " )\n";
	}
	std::cout << "Total distance of a path: " << city.path_distance(path) << "\n\n";

	std::cout << "Optimal point (center): " << find_optimal(city) << "\n";

	city.print();

	//TODO task
}
