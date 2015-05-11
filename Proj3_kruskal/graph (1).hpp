#if !defined(__GRAPH_HPP)
#define __GRAPH_HPP

#include <iostream>
using std::endl;

#include <list>
using std::list;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include "edge.hpp"
#include "mst.hpp"

// The Weighted_Graph class.

class Weighted_Graph {
  friend ostream &operator<<(ostream &os, const Weighted_Graph &G) {
    os << "graph: " << G.name << " {\n";
    os << " V: " << G.V << "\n";
    os << " E: " << G.E << "\n";
    os << " adjacency list = {" << "\n";
    for (unsigned long int v = 0; v < G.V; v++) {
      os << "  " << v << ": ";
      if (!G.adj[v].empty()) {
	for (auto &w : G.adj[v]) {
	  os << w << " ";
	}
      }
      os << endl;
    }
    os << " }" << endl;
    os << "}" << endl;

    return os;
  };

public:
  Weighted_Graph(string name = "G"); // This is an instance of a default function argument.
  
  inline int num_edges() const {return E;}
  inline int num_vertices() const {return V;}
  void add_edge(const Edge &e); // Add an edge by adding it to edges[] and updating adj[], resizing either as needed.
  MST kruskal(string name = "T") const;

protected:

private:
  string name;              // The name of the graph.
  unsigned long int E;      // The number o' edges.
  unsigned long int V;      // The number o' vertices.
  vector<list<Vertex>> adj; // The adjacency list.
  vector<Edge> edges;       // The edges.
};

ostream &operator<<(ostream &os, const Weighted_Graph &G);

#endif
