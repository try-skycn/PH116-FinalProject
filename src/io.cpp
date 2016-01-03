#include "io.h"
#include <fstream>
#include <string>

enum {DC, AC} type;
ifstream fin("data.txt");
ofstream fout("out.tex");
void draw_circuit(const std::vector <conductor> &);

void output_circuit_current(const std::vector <std::complex<double> > &I, const std::vector <conductor> &w) {
    draw_circuit(w);
    fout << "\begin{tabular}{l|l}" << endl;
    for (uint i = 0; i < I.size(); i++) {
        fout << "$I_{" << i << "}$" << " & $";
        switch (type) {
            DC: 
                fout << I[i].re;
                break;
            RC:
                fout << I[i].re << " + " << I[i].im << "i ";
                break;
        }
        fout << "A$ \\" << endl;
    }
    fout << "\end{tabular}" << endl
         << "\end{document}" << endl;
    fout.close();
}

/*  Read in the circuit from "data.txt". 
 *  Input format:
 *  first line: 
        DC(RC)
 *  represents the type of the circuit(DC circuit or RC circuit)
 *  
 *  rest lines: 
 *      from, to, imp.re, imp.im, emf.re, emf.im  
 */
unsigned int input_circuit_network(std::vector <conductor>& w) {
    std::string str;
    fin >> str;
    if (str == "DC") type = DC; else type = RC;
    uint N = -1;
    while (1) {
        conductor next;
        int f, t;
        
        fin >> f >> t;
        if (f == -1 && t == -1) break;
        
        next.edge_info.from = f;
        next.edge_info.to = t;
        
        switch (type) {
            RC: 
                fin >> next.elect_info.imp.re >> next.elect_info.imp.im
                    >> next.elect_info.emf.re >> next.elect_info.emf.im;
                break;
            DC:
                fin >> next.elect_info.imp.re
                    >> next.elect_info.emf.re;
                break;
        }
        
        N = (f > N) ? f : N;
        N = (t > N) ? t : N;
        w.push_back(next);                 
    }
    
    fin.close();
    return N + 1;
}