#include "io.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <iomanip>
#include "draw.h"
std::ofstream fout("out.tex");
using std::cin;

enum { DC, AC } TYPE;
void output_circuit_current(const std::vector <std::complex<double> > &I, const std::vector <conductor> &w) {
    draw_circuit(I, w, (TYPE == AC));
	fout << "\\documentclass[14px]{article}" << std::endl
		<< "\\usepackage{graphicx}" << std::endl
		<< "\\begin{document}" << std::endl
		<< "\\includegraphics[height = 5cm]{pic.eps}" << std::endl
		<< "\\begin{table}[!htb]" << std::endl
		<< "\\begin{tabular}{|l|l|}" << std::endl
		<< "\\hline" << std::endl;
    
    //改成小数表示
    fout << std::fixed << std::setprecision(6);
    for (uint i = 0; i < I.size(); i++) {
        fout << "$I_{" << i << "}$" << " & $";
        if (TYPE == DC){
            fout << fabs(I[i].real());
        }
        else {
            fout << "(" << I[i].real() << (I[i].imag() > 0 ?" + ": " - ") << fabs(I[i].imag()) << "i) ";
        }
		fout << "A$ \\\\" << std::endl
			<< "\\hline" << std::endl;
    }
	fout << "\\end{tabular}" << std::endl;
    fout << "\\end{table}" << std::endl;
    
    fout << "\\begin{table}[!htb]" << std::endl;
	fout << "\\begin{tabular}{|l|l|}" << std::endl
		<< "\\hline" << std::endl;

	for (uint i = 0; i < w.size(); i++) {
		std::complex <double> Z = w[i].elect_info.imp;
		if (Z == std::complex <double>(0., 0.)) continue;
		fout << "$Z_{" << i << "}$" << "& $";
		if (TYPE == DC) {
			fout << Z.real();
		}
		else {
			fout << "(" << Z.real() << (Z.imag() > 0 ? " + " : " - ") << fabs(Z.imag()) << "i) ";
		}
		fout << "\\Omega$ \\\\" << std::endl
			<< "\\hline" << std::endl;
	}
	fout << "\\end{tabular}" << std::endl;
    fout << "\\end{table}" << std::endl;

    fout << "\\begin{table}[!htb]" << std::endl;
	fout << "\\begin{tabular}{|l|l|}" << std::endl
		<< "\\hline" << std::endl;

	for (uint i = 0; i < w.size(); i++) {
		std::complex <double> E = w[i].elect_info.emf;
		if (E == std::complex <double>(0., 0.)) continue;
		fout << "$E_{" << i << "}$" << "& $";
		if (TYPE == DC) {
			fout << E.real();
		}
		else {
			fout << "(" << E.real() << (E.imag() > 0 ? " + " : " - ") << fabs(E.imag()) << "i) ";
		}
		fout << "V$ \\\\" << std::endl
			<< "\\hline" << std::endl;
	}
	fout << "\\end{tabular}" << std::endl;

	fout << "\\end{table}" << std::endl
		<< "\\end{document}" << std::endl;
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
    cin >> str;
    if (str == "DC") TYPE = DC;
        else TYPE = AC;
    uint N = 0;
    while (1) {
        conductor next;
        int f, t;
        
        cin >> f >> t;
        if (f == -1 && t == -1) break;
        
        next.edge_info.from = f;
        next.edge_info.to = t;
        
        if (TYPE == AC){
            cin >> real >> imag;
            next.elect_info.imp = std::complex<double>(real, imag);
            cin >> real >> imag;
            next.elect_info.emf = std::complex<double>(real, imag);
        }
        else {
            cin >> real;
            next.elect_info.imp = std::complex<double>(real);
            cin >> real;
            next.elect_info.emf = std::complex<double>(real);
        }
        N = ((unsigned)f > N) ? (unsigned)f : N;
        N = ((unsigned)t > N) ? (unsigned)t : N;
        w.push_back(next);                 
    }
    
    return N + 1;
}