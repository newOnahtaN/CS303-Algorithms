#if !defined(__EDGE_HPP)
#define __EDGE_HPP

#include <iostream>
#include <stdexcept>

using std::istream;
using std::ostream;

using Vertex = unsigned long int;

class Edge {
  friend istream &operator>>(istream &is, Edge &e) {
    is >> e.v >> e.w >> e.wt;
    return is;
  };
  friend ostream &operator<<(ostream &os, const Edge &e) {
    os << e.v << "--" << e.w << " (" << e.wt << ")";
    return os;
  };

public:
  Edge () {};
  Edge (Vertex v, Vertex w, double weight) : v(v), w(w), wt(weight) {};
  Edge (const Edge &e) : v(e.v), w(e.w), wt(e.wt) {};

  inline double weight(void) const {return wt;}  // Return the weight of the edge.
  inline Vertex either(void) const {return v;}   // Return endpoint v of the edge.
  Vertex other(const Vertex vertex) const;       // Return the endpoint other than vertex.

protected:

private:
  Vertex v, w;  // The vertices connected by the edge.
  double wt;    // The weight of the edge.
};

istream &operator>>(istream &is, Edge &e);
ostream &operator<<(ostream &os, const Edge &e);

#endif
