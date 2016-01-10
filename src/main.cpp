#include "io.h"
#include "graph.h"

int main() {
	std::vector<conductor> graph_edge;
	uint N = input_circuit_network(graph_edge);
	graph *G = new graph(N, graph_edge);

	std::vector<comp> result;
	G->get_current(result);
	output_circuit_current(result, graph_edge);
	delete G;
	return 0;
}
