#ifndef __RESOURCES_H__
#define __RESOURCES_H__

#include <complex>
#include <vector>
#include <utility>
#include <armadillo>

//typedef std::pair<unsigned int, unsigned int> vertex_pair;
//typedef std::pair<std::complex<double>, std::complex<double> > conductor_info;
//typedef std::pair<vertex_pair, conductor_info> conductor;

class conductor{
public:
    std::complex<double> impedance;
    std::complex<double> EMF;
    std::vector<unsigned int> end;
    conductor(const std::complex<double>& _imp, const std::complex<double>& _emf, const unsigned int& end1, const unsigned int& end2): impedance(_imp), EMF(_emf), end{end1, end2}{};
};
#endif
