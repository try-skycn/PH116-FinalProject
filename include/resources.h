#ifndef __RESOURCES_H__
#define __RESOURCES_H__

#include <complex>
#include <vector>
#include <utility>
#include <queue>
#include <armadillo>

typedef unsigned int uint;
typedef std::complex<double> comp;
enum {DC, AC} TYPE;

struct vertex_pair {
	uint from, to;
    
//    vertex_pair();
//    vertex_pair(const uint& _from, const uint& _to): from(_from), to(_to){}
};
struct conductor_info {
	comp imp, emf;
    
//    conductor_info();
//    conductor_info(const comp& _imp, const comp& _emf): imp(_imp), emf(_emf){}
};

struct conductor {
	vertex_pair edge_info;
	conductor_info elect_info;
    
//    conductor();
//    conductor(const comp& imp, const comp& emf, const uint& from, const uint& to): elect_info(imp, emf), edge_info(from, to){}
};

#endif
