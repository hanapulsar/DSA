#include <iostream>
#include <string>
#include "Graph.h"

std::string find_optimal(Graph<std::string, double>& g) {
	std::vector<std::string> points = g.vertices();
	if (points.empty()) return "";


}

int main() {
	Graph<std::string, double> city;

	city.add_vertex("Center");
	city.add_vertex("North");
	city.add_vertex("South");
	city.add_vertex("East");
	city.add_vertex("West");

	city.add_edge("Center", "North", 10);
	city.add_edge("Center", "South", 7);
	city.add_edge("Center", "East", 5);
	city.add_edge("Center", "West", 8);

	city.add_edge("North", "Center", 10);
	city.add_edge("South", "Center", 7);
	city.add_edge("East", "Center", 5);
	city.add_edge("West", "Center", 8);

	city.add_edge("North", "East", 20);
	city.add_edge("East", "South", 6);
	city.add_edge("South", "West", 11);
	city.add_edge("West", "North", 3);

	std::cout << "BFS Walk from center: \n";
	city.walk("Center", [](const std::string& v) {
		std::cout << "Visited:" << v << "\n";
		});
	std::cout << "\n";

	std::cout << "Graph order: " << city.order() << "\n";
	std::cout << "Graph degree at center: " << city.degree("Center") << "\n";
	std::cout << "Is graph connected: " << (city.is_connected() ? "Yes" : "No") << "\n";

	std::cout << "Shortest from West to East: \n";
	auto path = city.shortest_path("West", "East");
	for (const auto& edge : path) {
		std::cout << edge.from << " -> " << edge.to << " ( distance: " << edge.distance << " )\n";
	}
	std::cout << "Total distance of a path: " << city.path_distance(path) << "\n";

	//TODO task
}