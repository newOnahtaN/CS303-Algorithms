#include "edge.hpp"

Vertex Edge::other(const Vertex vertex) const{
	if (vertex != v) {
		return v;
	}

	return w;
}

