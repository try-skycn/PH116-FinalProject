#include "io.h"
#include "resources.h"
#include <fstream>
#include <string>
#include "draw.h"
std::ifstream fin("data.txt");
std::ofstream fout("out.tex");


void output_circuit_current(const std::vector <std::complex<double> > &I, const std::vector <conductor> &w) {
    draw_circuit(I,w);
    fout << "\begin{table}[!htb]" << std::endl;
    fout << "\begin{tabular}{l|l}" << std::endl;
    for (uint i = 0; i < I.size(); i++) {
        fout << "$I_{" << i << "}$" << " & $";
        if (TYPE == DC){
            fout << I[i].real();
        }
        else {
            fout << I[i].real() << " + " << I[i].imag() << "i ";
        }
        fout << "A$ \\" << std::endl;
    }
    fout << "\end{tabular}" << std::endl;
    fout << "\end{table}" << std::endl;
    fout.close();
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
    fin >> str;
    if (str == "DC") TYPE = DC;
        else TYPE = AC;
    uint N = -1;
    while (1) {
        conductor next;
        int f, t;
        
        fin >> f >> t;
        if (f == -1 && t == -1) break;
        
        next.edge_info.from = f;
        next.edge_info.to = t;
        
        if (TYPE == AC){
            fin >> real >> imag;
            next.elect_info.imp = std::complex<double>(real, imag);
            fin >> real >> imag;
            next.elect_info.emf = std::complex<double>(real, imag);
        }
        else {
            fin >> real;
            next.elect_info.imp = std::complex<double>(real);
            fin >> real;
            next.elect_info.emf = std::complex<double>(real);
        }
        N = (f > N) ? f : N;
        N = (t > N) ? t : N;
        w.push_back(next);                 
    }
    
    fin.close();
    return N + 1;
}