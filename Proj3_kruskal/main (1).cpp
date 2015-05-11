#include "edge.hpp"
#include "graph.hpp"
#include "mst.hpp"

using std::cin;
using std::cout;
using std::endl;

int main (int argc, char **argv)
{
  Edge e;
  Weighted_Graph G;

  while (cin >> e) {
    cout << e << endl;
    G.add_edge(e);
  }
  cout << G;

  MST M = G.kruskal();
  cout << M;

  return 0;
}
