#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "resources.h"

class graph {
private:
    //For data structures
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
    
    //For memory pools
    //All zero_based
	vertex *vertex_pool;
	edge *edge_pool;
    //All zero_based
    int vec_tot;
    int edge_tot;

    //For internal functions
    //Modified Reason: conductor class (in resource.h) contain the two ends of edges
	edge *add_edge(conductor);
	bool find_tree_path(vertex *, vertex *, vertex *, std::vector<edge *> &);

    //Modified Reason: Can reach the vertex by index
	arma::cx_rowvec flow_conservation_equation(int index) const;
	std::pair<arma::cx_rowvec, std::complex<double> > circular_equation(int ini_vec, edge* start);
	void bfs(int ini_vec, arma::cx_mat &, arma::cx_vec &, unsigned int &);
	void find_all_circular(arma::cx_mat &, arma::cx_vec &, unsigned int &);

public:	//For user ports
	graph(unsigned int, const std::vector<conductor> &);
	void get_current(std::vector<std::complex<double> > &);
};

#endif
