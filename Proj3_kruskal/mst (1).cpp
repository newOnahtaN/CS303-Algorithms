#include "mst.hpp"


void MST::add_edge(const Edge &e){
	wt += e.weight();
	push_back(e);
}



	
