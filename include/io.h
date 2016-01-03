#ifndef __IO_H__
#define __IO_H__

#include "resources.h"
#include <vector>

unsigned int input_circuit_network(std::vector<conductor> &);
void output_circuit_current(const std::vector<std::complex<double> > &, const std::vector <conductor> &);

#endif
