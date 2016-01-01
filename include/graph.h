#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "resources.h"

class graph {
private:	//For data structures
	struct vertex;

	struct edge {
		vertex *endpoint;
		edge *opposite_edge, *next_edge;
		char direction;
		bool in_tree;
		unsigned int index;
		std::complex<double> impedance, electromotive_force;
	};
	struct vertex {
		edge *first_edge;
		bool bfs_mark;
	};

	vertex *vertex_memory_pool;
	edge *edge_memory_pool;

private:	//For internal functions
	edge *add_edge(vertex *, vertex *, conductor_info);
	bool find_tree_path(vertex *, vertex *, vertex *, std::vector<edge *> &);

	arma::cx_rowvec flow_conservation_equation(vertex *);
	std::pair<arma::cx_rowvec, std::complex<double> > circular_equation(vertex *, edge *);
	void bfs(vertex *, arma::cx_mat &, arma::cx_vec &, unsigned int &);
	void find_all_circular(arma::cx_mat &, arma::cx_vec &, unsigned int &);

public:	//For user ports
	graph(unsigned int, const std::vector<conductor> &);
	void get_current(std::vector<std::complex<double> > &);
	~graph();
};

#endif
