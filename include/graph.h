#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "resources.h"

class graph {
public:
	graph(unsigned int, const std::vector<conductor> &);
	void get_current(std::vector<std::complex<double> > &);
};

#endif
