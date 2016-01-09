//
//  draw.h
//  PH116
//
//  Created by 游宇榕 on 16/1/9.
//  Copyright © 2016年 游宇榕. All rights reserved.
//

#ifndef draw_h
#define draw_h
#include "resources.h"
#include <fstream>
void draw_circuit(const std::vector <std::complex<double> > &I, const std::vector <conductor>& data, bool TYP){
	enum {DC, AC} TYPE;
	if (TYP) TYPE = AC; else TYPE = DC;
    std::ofstream draw("pic.dot");
    
//    直流电路
    if (TYPE == DC){
        draw << "digraph G{" << std::endl;
        draw << "splines = ortho;" << std::endl;
        draw << "node[style = filled];" << std::endl;
        draw << "node[shape = rectangle];" << std::endl;
        for (int i = 0; i < (int)data.size(); ++i){
			draw << "subgraph cluster_" << i << "{" << std::endl;
            if (data[i].elect_info.imp != std::complex<double>(0,0)){
                draw << "bz" << i << " [label = \"Z" << i << "\"];" << std::endl;
            }
            if (data[i].elect_info.emf != std::complex<double>(0,0)){
                draw << "be" << i << " [label = \"E" << i << "\"];" << std::endl;
            }
            if (data[i].elect_info.emf != std::complex<double>(0,0) && data[i].elect_info.imp != std::complex<double>(0,0)){
                draw << "bz" << i << "->" << "be" << i << ";" << std::endl;
            }
			draw << "}" << std::endl;
        }
        draw << "node[shape = point];" << std::endl;
        for (int i = 0; i < (int)data.size(); ++i){
            //设置电流真实方向，保证图中所绘为 a-(I)->bz->be->b
            uint _f, _t;
            if (I[i].real() >= 0){
                _f = data[i].edge_info.from;
                _t = data[i].edge_info.to;
            }
            else{
                _f = data[i].edge_info.to;
                _t = data[i].edge_info.from;
            }
            //如果既有imp又有emf
            if (data[i].elect_info.emf != std::complex<double>(0,0) && data[i].elect_info.imp != std::complex<double>(0,0)){
                draw << "n" << _f << "->" << "bz" << i << " [label = \"I" << i << "\"];"<< std::endl;
                draw << "be" << i << "->" << "n" << _t << ";" << std::endl;
                continue;
            }
                //只有emf
            if (data[i].elect_info.emf != std::complex<double>(0,0)){
                draw << "n" << _f << "->" << "be" << i << " [label = \"I" << i << "\"];"<< std::endl;
                draw << "be" << i << "->" << "n" << _t << ";" << std::endl;
            }
                //只有imp
            else {
                draw << "n" << _f << "->" << "bz" << i << " [label = \"I" << i << "\"];"<< std::endl;
                draw << "bz" << i << "->" << "n" << _t << ";" << std::endl;
            }
            
        }
        draw << "}" << std::endl;
    }
//    交流电路
    else{
        draw << "graph G{" << std::endl;
		draw << "model = circuit" << std::endl;
        draw << "splines = ortho;" << std::endl;
        draw << "node[style = filled];" << std::endl;
        draw << "node[shape = rectangle];" << std::endl;
        for (int i = 0; i < (int)data.size(); ++i){
			draw << "subgraph cluster_" << i << "{" << std::endl;
            if (data[i].elect_info.imp != std::complex<double>(0,0)){
                draw << "bz" << i << " [label = \"Z" << i << "\"];" << std::endl;
            }
            if (data[i].elect_info.emf != std::complex<double>(0,0)){
                draw << "be" << i << " [label = \"E" << i << "\"];" << std::endl;
            }
            if (data[i].elect_info.emf != std::complex<double>(0,0) && data[i].elect_info.imp != std::complex<double>(0,0)){
                draw << "bz" << i << "--" << "be" << i << ";" << std::endl;
            }
			draw << "}" << std::endl;
        }
        draw << "node[shape = point];" << std::endl;
        for (int i = 0; i < (int)data.size(); ++i){
            //如果既有imp又有emf
            if (data[i].elect_info.emf != std::complex<double>(0,0) && data[i].elect_info.imp != std::complex<double>(0,0)){
                draw << "n" << data[i].edge_info.from << "--" << "bz" << i << " [label = \"I" << i << "\"];"<< std::endl;
                draw << "be" << i << "--" << "n" << data[i].edge_info.to << ";" << std::endl;
                continue;
            }
            //只有emf
            if (data[i].elect_info.emf != std::complex<double>(0,0)){
                draw << "n" << data[i].edge_info.from << "--" << "be" << i << " [label = \"I" << i << "\"];"<< std::endl;
                draw << "be" << i << "--" << "n" << data[i].edge_info.to << ";" << std::endl;
            }
            //只有imp
            else {
                draw << "n" << data[i].edge_info.from << "--" << "bz" << i << " [label = \"I" << i << "\"];"<< std::endl;
                draw << "bz" << i << "--" << "n" << data[i].edge_info.to << ";" << std::endl;
            }
            
        }
        draw << "}" << std::endl;
    }
    
    draw.close();
}

#endif /* draw_h */
