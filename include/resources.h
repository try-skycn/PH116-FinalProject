#ifndef __RESOURCES_H__
#define __RESOURCES_H__

#include <complex>
#include <vector>
#include <utility>
#include <queue>
#include <armadillo>

typedef unsigned int uint;
typedef std::complex<double> comp;
struct vertex_pair {
	uint from, to;
};
struct conductor_info {
	comp imp, emf;
};
struct conductor {
	vertex_pair edge_info;
	conductor_info elect_info;
};

#endif
