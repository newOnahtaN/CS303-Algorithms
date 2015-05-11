#if !defined(__UNION_FIND_HPP)
#define __UNION_FIND_HPP

#include <vector>
using std::vector;

using Site = unsigned long int;
using Component = unsigned long int;

class Union_Find {
public:
  Union_Find(unsigned long int N); // Create a union-find object for N items.

  Component find (const Site p);               // Component identifier for p.
  void onion (const Site p, const Site q);     // Add a connection between p and q.
  inline bool connected (const Site p, const Site q) {  // Are p and q are in the same component?
    return (find(p) == find(q));
  };

protected:

private:
  unsigned long int num_components;  // No. of connected components.
  vector<Site> id;
  vector<unsigned long int> sz;      // sz[i] = size of tree (component) containing i.
};

#endif
