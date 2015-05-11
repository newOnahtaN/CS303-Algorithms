#if !defined(__UNION_FIND_HPP)
#define __UNION_FIND_HPP

#include <iostream>
using std::cout;
#include <vector>
using std::vector;

using Site = unsigned long int;
using Component = unsigned long int;

class Union_Find {
public:
  Union_Find(unsigned long int N);

  Component find (Site &p) {cout << ":p\n"; return 0;};
  void onion (Site &p, Site &q) {cout << ":p\n";};
  inline bool connected (Site &p, Site &q) {  // Are p and q are in the same component?
    return (find(p) == find(q));
  };

protected:
  unsigned long int num_components;
  vector<Site> id;
};

class Quick_Find : public Union_Find {
public:
  Quick_Find(unsigned long int N) : Union_Find(N) {};

  inline bool connected (const Site &p, const Site &q) {return (find(p) == find(q));};
  void onion (const Site &p, const Site &q);
  Component find (const Site &p);
};

class Quick_Union : public Union_Find {
public:
  Quick_Union(unsigned long int N) : Union_Find(N) {};

  inline bool connected (const Site &p, const Site &q) {return (find(p) == find(q));};
  void onion (const Site &p, const Site &q);
  inline Component find (const Site &p);
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

  inline Component find (const Site &p);
};

#endif
