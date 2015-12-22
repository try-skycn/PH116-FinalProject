#ifndef __RESOURCES_H__
#define __RESOURCES_H__

#include <complex>
#include <vector>
#include <utility>
#include <armadillo>

typedef std::pair<unsigned int, unsigned int> vertex_pair;
typedef std::pair<std::complex<double>, std::complex<double> > conductor_info;
typedef std::pair<vertex_pair, conductor_info> conductor;

#endif
