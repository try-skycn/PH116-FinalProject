#include "graph.h"

void graph::add_edge(edge *e, vertex *from, vertex *to, conductor_info elect_info, double direction, uint index) {
	e->endpoint = to;
	e->next_edge = from->first_edge;
	from->first_edge = e;
	e->direction = direction;
	e->in_tree = false;
	e->index = index;
	e->elect_info = elect_info;
}

arma::cx_rowvec graph::flow_conservation_equation(vertex *x) {
	arma::cx_rowvec edgedir;
	for (edge *e = x->first_edge; e; e = e->next_edge) {
		edgedir(e->index) = e->direction;
	}
	return edgedir;
}

std::pair<arma::cx_rowvec, comp> graph::circular_equation(vertex *from, edge *e) {
	std::vector<edge *> path;
	find_tree_path(from, e->endpoint, path);
	path.push_back(e->opposite_edge);

	arma::cx_rowvec edgeimp;
	comp totemf;

	for (std::vector<edge *>::iterator it = path.begin(); it != path.end(); ++it) {
		edgeimp((*it)->index) = (*it)->direction * (*it)->conductor_info->imp;
		totemf += (*it)->direction * (*it)->conductor_info->emf;
	}
	return std::pair<arma::cx_rowvec, comp>(edgeimp, totemf);
}

void graph::bfs(vertex *start, arma::cx_mat &A, arma::cx_vec &b, uint &current_row) {
	queue<vertex *> Q;
	Q.push(start);
	start->bfs_mark = true;
	while (!Q.empty()) {
		x = Q.front();
		Q.pop();
		for (edge *e = x->first_edge; e; e = e->next_edge) {
			if (!x->bfs_mark) {
				Q.push(x);
				x->bfs_mark = true;
				e->in_tree = true;
				e->opposite_edge->in_tree = true;

				arma::cx_rowvec edgedir = flow_conservation_equation(x);
				A.row(current_row++) = edgedir;
			}
		}
	}
}

void graph::find_all_circular(arma::cx_mat &A, arma::cx_vec &b, uint &current_row) {
	for (uint i = 0; i < vertex_number; ++i) {
		vertex *x = vertex_memory_pool[i];
		for (edge *e = x->first_edge; e; e != e->next_edge) {
			if (!e->in_tree && e->direction > 0.0) {
				std::pair<arma::cx_rowvec, comp> equa = circular_equation(x, e);
				A.row(current_row) = equa.first;
				b(current_row) = equa.second;
				++current_row;
			}
		}
	}
}

graph::graph(uint V, const std::vector<conductor> &conductors) {
	vertex_number = V;
	vertex_memory_pool = new vertex[vertex_number];
	edge_number = conductors.size();
	edge_memory_pool = new edge[2 * edge_number];
	for (uint i = 0; i < edge_number; ++i) {
		vertex *x = conductors[i].edge_info.from, *y = conductors[i].edge_info.to;
		edge *ep = edge + (2 * i), *en = edge + (2 * i + 1);
		addedge(ep, x, y, conductors[i].elect_info,  1.0, i);
		addedge(en, y, x, conductors[i].elect_info, -1.0, i);
		ep->opposite_edge = en;
		en->opposite_edge = ep;
	}
}

void graph::get_current(std::vector<comp> &current) {
	arma::cx_mat A(edge_number, edge_number, fill::zeros);
	arma::cx_vec b(edge_number, fill::zeros);
	uint current_row = 0;
	for (uint i = 0; i < vertex_number; ++i) {
		if (!vertex_memory_pool[i].bfs_mark) {
			bfs(vertex_memory_pool + i, A, b, current_row);
		}
	}
	find_all_circular(A, b, current_row);
	arma::cx_vec I = arma::solve(A, b);
	for (uint i = 0; i < edge_number; ++i) {
		current.push_back(I(i));
	}
}

graph::edge::edge() {
	in_tree = false;
}

graph::vertex::vertex() {
	first_edge = NULL;
	bfs_mark = false;
}
