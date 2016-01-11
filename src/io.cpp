#include "io.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include "draw.h"

enum { DC, AC } TYPE;
void output_circuit_current(const std::vector <std::complex<double> > &I, const std::vector <conductor> &w) {
    std::cout << std::fixed << std::setprecision(6); 
	for (uint i = 0; i < I.size(); i++) {
		if (TYPE == AC) {
			std::cout << "The current from " << w[i].edge_info.from << " to " << w[i].edge_info.to << " is: " << I[i].real() << (I[i].imag() >= 0. ? " + " : " - ") << fabs(I[i].imag()) << "i A" << std::endl;
		} else {
			std::cout << "The current from " << w[i].edge_info.from << " to " << w[i].edge_info.to << " is: " << I[i].real() << " A" << std::endl;
		}
	}
}

/*  Read in the circuit from "data.txt". 
 *  Input format:
 *  first line: 
        DC(RC)
 *  represents the TYPE of the circuit(DC circuit or RC circuit)
 *  
 *  rest lines: 
 *      from, to, imp.re, imp.im, emf.re, emf.im
 *  
 *  WARNING: input vertex number should be zero-based
 */
unsigned int input_circuit_network(std::vector <conductor>& w) {
    std::string str;
    double real, imag;
    std::cin >> str;
    if (str == "DC") TYPE = DC;
        else TYPE = AC;
    uint N = 0;
    while (1) {
        conductor next;
        int f, t;
        
        std::cin >> f >> t;
        if (f == -1 && t == -1) break;
        
        next.edge_info.from = f;
        next.edge_info.to = t;
        
        if (TYPE == AC){
            std::cin >> real >> imag;
            next.elect_info.imp = std::complex<double>(real, imag);
            std::cin >> real >> imag;
            next.elect_info.emf = std::complex<double>(real, imag);
        }
        else {
            std::cin >> real;
            next.elect_info.imp = std::complex<double>(real);
            std::cin >> real;
            next.elect_info.emf = std::complex<double>(real);
        }
        N = ((unsigned)f > N) ? (unsigned)f : N;
        N = ((unsigned)t > N) ? (unsigned)t : N;
        w.push_back(next);                 
    }
    
    return N + 1;
}