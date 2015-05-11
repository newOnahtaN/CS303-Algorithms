#if !defined(__MST_HPP)
#define __MST_HPP

#include <iostream>
using std::endl;

#include <vector>
using std::vector;

#include <string>
using std::string;

#include "edge.hpp"

class MST { 
  friend ostream &operator<<(ostream &os, const MST &M) {
    os << "MST: " << M.name << " {\n";
    os << " total weight: " << M.wt << endl;
    os << " edges = {\n";
    for (auto e : M.edges) {
      os << "  " << e << '\n';
    }
    os << " }" << endl;
    os << "}" << endl;
    return os;
  };

public:
  MST(string name = "T") : name(name), wt(0) {}; // This is an instance of a default function argument.
  inline double weight() const {return wt;};
  void add_edge(const Edge &e); // Add an edge to the class member vector<Edge> edges and update wt.
  inline void push_back(const Edge &e) {edges.push_back(e);};
  inline unsigned long int size() {return edges.size();};
  
protected:

private:
  string name; // The name of this MST.
  double wt;   // The total weight of the MST.
  vector<Edge> edges; // The edges in the MST.
};

ostream &operator<<(ostream &os, const MST &M);

#endif
