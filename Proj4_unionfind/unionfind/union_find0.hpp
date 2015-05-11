#if !defined(__UNION_FIND_HPP)
#define __UNION_FIND_HPP

#include <vector>
using std::vector;

using Site = unsigned long int;
using Component = unsigned long int;

// This is a class derivation hierarchy that implements quick find, quick union, weighted quick union, and
// weighted quick union with path compression.
//
// All the classes are ultimately derived from the abstract base class Union_Find:
//   Union_Find -> Quick_Find
//   Union_Find -> Quick_Union -> Weighted_Quick_Union -> Weighted_Quick_Union_with_Path_Compression
// The functions find() and onion() in Union_Find are pure virtual functions (pg 748 in Prata).

class Union_Find {
public:
  Union_Find(unsigned long int N); // Create a base union-find object for N items.

  virtual Component find (const Site &p) = 0;       // Component identifier for p.
  virtual void onion (const Site &p, const Site &q) = 0;  // Add a connection between p and q.
  inline bool connected (const Site &p, const Site &q) {  // Are p and q are in the same component?
    return (find(p) == find(q));
  };

protected:
  unsigned long int num_components;  // No. of connected components.
  vector<Site> id;                   // This array is common to all the classes.
};

class Quick_Find : public Union_Find {
public:
  Quick_Find(unsigned long int N) : Union_Find(N) {};

  Component find (const Site &p);
  void onion (const Site &p, const Site &q);
};

class Quick_Union : public Union_Find {
public:
  Quick_Union(unsigned long int N) : Union_Find(N) {};

  Component find (const Site &p);
  void onion (const Site &p, const Site &q);
};

class Weighted_Quick_Union : public Quick_Union {
public:
  Weighted_Quick_Union(unsigned long int N) : Quick_Union(N), sz(N,1) {};

  void onion (const Site &p, const Site &q);
protected:
  vector<unsigned long int> sz;
};

class Weighted_Quick_Union_with_Path_Compression : public Weighted_Quick_Union {
public:
  Weighted_Quick_Union_with_Path_Compression(unsigned long int N) : Weighted_Quick_Union(N) {};

  Component find (const Site &p);
};

#endif
