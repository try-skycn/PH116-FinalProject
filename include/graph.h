#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "resources.h"

class graph {
private:	//For data structures
	struct vertex;

	struct edge {
		vertex *endpoint;
		edge *opposite_edge, *next_edge;
		double direction;
		bool in_tree;
		uint index;
		conductor_info elect_info;

		edge();
	};
	struct vertex {
		edge *first_edge;
		bool bfs_mark;

		vertex();
	};

	vertex *vertex_memory_pool;
	edge *edge_memory_pool;
	uint vertex_number, edge_number;

private:	//For internal functions
	void add_edge(edge *, vertex *, vertex *, conductor_info, char, uint);
	void find_tree_path(uint, vertex *, vertex *, std::vector<edge *> &);

	arma::cx_rowvec flow_conservation_equation(vertex *);
	std::pair<arma::cx_rowvec, comp> circular_equation(vertex *, edge *);
	void bfs(vertex *, arma::cx_mat &, arma::cx_vec &, uint &);
	void find_all_circular(arma::cx_mat &, arma::cx_vec &, uint &);

public:	//For user ports
	graph(uint, const std::vector<conductor> &);
	void get_current(std::vector<comp> &);
	~graph();
};

#endif
