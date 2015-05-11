#include "graph.hpp"
#include "union_find.hpp"
#include <queue>

using std::cout; //for testing

class CompareEdge{
	public:
	bool operator()(Edge &edgeOne, Edge &edgeTwo){
		if (edgeOne.weight() > edgeTwo.weight()){
			return true;
		}
		return false;
	}
};

Weighted_Graph::Weighted_Graph(string name){
	//This constructor isn't really necessary, I just
	//wrote it for practice with constructors in C++.
	V = 0;
	E = 0;
	vector<list<Vertex>> temp (V, list<Vertex>(0));
	adj = temp;
}

void Weighted_Graph::add_edge(const Edge &e){
	Vertex v = e.either();
	Vertex w = e.other(v);
	Vertex big = std::max(v,w);
	//to account for the fact that we don't know how many vertices there are
	if (big + 1 > V){
		V = big + 1;
		adj.resize(V + 1);
	}
	
	adj[v].push_front(w);
	adj[w].push_front(v);
	edges.push_back(e);
	E++; //page 526

}

MST Weighted_Graph::kruskal(string name) const{ //page 627

	MST mst;
	std::priority_queue<Edge, vector<Edge>, CompareEdge> queue;
	for (unsigned int i=0; i<E; i++){
		queue.push(edges[i]);
	} 
	Union_Find uf(V);

	while (!queue.empty() && mst.size() < V-1){
		Edge e = queue.top();
		queue.pop();
		Vertex v = e.either();
		Vertex w = e.other(v);
		if (!uf.connected(v,w)){
			uf.onion(v,w);
			mst.add_edge(e);
		}
	}

	return mst;

	
}

