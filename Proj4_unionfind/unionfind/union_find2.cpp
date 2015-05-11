#include <algorithm> // Needed for the PRNG routines.
#include <chrono>    // Needed for the timing routines.
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <string>
using std::string;

#include "union_find2.hpp"

Union_Find::Union_Find (unsigned long int N) : num_components(N), id(N) {
  for (unsigned long int i = 0; i < N; i++) {
    id[i] = {i};
  }
}

void Quick_Find::onion (const Site &p, const Site &q) {
  auto p_id = find(p);
  auto q_id = find(q);

  if (p_id == q_id) {
    return;
  }

  for (unsigned long int i = 0; i < id.size(); i++) {
    if (id[i] == p_id) {
      id[i] = q_id;
    }
  }
  num_components--;
}

void Quick_Union::onion (const Site &p, const Site &q) {
  auto i = find(p);
  auto j = find(q);

  if (i == j) return;

  id[i] = j;
  num_components--;
}

void Weighted_Quick_Union::onion (const Site &p, const Site &q) {
  auto i = find(p);
  auto j = find(q);

  if (i == j) {
    return;
  }

  if (sz[i] < sz[j]) {
    id[i] = j;
    sz[j] += sz[i];
  }
  else {
    id[j] = i;
    sz[i] += sz[j];
  }

  num_components--;
}

void Weighted_Quick_Union_with_Path_Compression::onion (const Site &p, const Site &q) {
  auto i = find(p);
  auto j = find(q);

  if (i == j) {
    return;
  }

  if (sz[i] < sz[j]) {
    id[i] = j;
    sz[j] += sz[i];
  }
  else {
    id[j] = i;
    sz[i] += sz[j];
  }

  num_components--;
}

int main (int argc, char **argv) {
  unsigned long int E, V;

  cout << "Enter the number of vertices (sites):    ";
  cin >> V;

  cout << "Enter the number of edges (connections): ";
  cin >> E;

  Quick_Find  qf(V);
  Quick_Union qu(V);
  Weighted_Quick_Union wqu(V);
  Weighted_Quick_Union_with_Path_Compression wqupc(V);

  vector<Site> p(E), q(E), r(E);

  //---------------------------------------------------------------------------------------------------------
  // Fill p and q with random integers. 
  std::mt19937 e(0); // Everyone's favorite pseudo-random number engine: the Mersenne twister.
  std::uniform_int_distribution<unsigned long int> u(0,V-1); // Convert engine output to a uniform integer distribution.
  auto t_start = std::chrono::high_resolution_clock::now();
  for (auto &w : p) {
    w = u(e);
  }
  for (auto &w : q) {
    w = u(e);
  }
  for (auto &w : r) {
    w = u(e);
  }
  auto t_end = std::chrono::high_resolution_clock::now();
  cout << "Initialization:\n";
  cout << "  Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t_end-t_start).count() <<  "ms\n";

  auto N = p.size();

  //#ifdef FOO
  //---------------------------------------------------------------------------------------------------------
  // Quick find.
  t_start = std::chrono::high_resolution_clock::now();
  for (Site i = 0; i < N; i++) {
    qf.onion(p[i], q[i]);
  }
  t_end = std::chrono::high_resolution_clock::now();
  cout << "-----------------------------------------------------------\n";
  cout << "Quick find union:\n";
  cout << "  Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t_end-t_start).count() <<  "ms\n";

  t_start = std::chrono::high_resolution_clock::now();
  for (Site i = 0; i < N; i++) {
    qf.connected(p[i], q[i]);
    qf.connected(p[i], r[i]);
  }
  t_end = std::chrono::high_resolution_clock::now();
  cout << "Quick find connected:\n";
  cout << "  Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t_end-t_start).count() <<  "ms\n";

  //---------------------------------------------------------------------------------------------------------
  // Quick union.
  t_start = std::chrono::high_resolution_clock::now();
  for (Site i = 0; i < N; i++) {
    qu.onion(p[i], q[i]);
  }
  t_end = std::chrono::high_resolution_clock::now();
  cout << "-----------------------------------------------------------\n";
  cout << "Quick union union:\n";
  cout << "  Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t_end-t_start).count() <<  "ms\n";

  t_start = std::chrono::high_resolution_clock::now();
  for (Site i = 0; i < N; i++) {
    qu.connected(p[i], q[i]);
    qu.connected(p[i], r[i]);
  }
  t_end = std::chrono::high_resolution_clock::now();
  cout << "Quick union connected:\n";
  cout << "  Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t_end-t_start).count() <<  "ms\n";
//#endif
  //---------------------------------------------------------------------------------------------------------
  // Weighted quick union without path compression.
  t_start = std::chrono::high_resolution_clock::now();
  for (Site i = 0; i < N; i++) {
    wqu.onion(p[i], q[i]);
  }
  t_end = std::chrono::high_resolution_clock::now();
  cout << "-----------------------------------------------------------\n";
  cout << "Weighted quick union (without path compression) union:\n";
  cout << "  Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t_end-t_start).count() <<  "ms\n";

  t_start = std::chrono::high_resolution_clock::now();
  for (Site i = 0; i < N; i++) {
    wqu.connected(p[i], q[i]);
    wqu.connected(p[i], r[i]);
  }
  t_end = std::chrono::high_resolution_clock::now();
  cout << "Weighted quick union (without path compression) connected:\n";
  cout << "  Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t_end-t_start).count() <<  "ms\n";

  //---------------------------------------------------------------------------------------------------------
  // Weighted quick union with path compression.
  t_start = std::chrono::high_resolution_clock::now();
  for (Site i = 0; i < N; i++) {
    wqupc.onion(p[i], q[i]);
  }
  t_end = std::chrono::high_resolution_clock::now();
  cout << "-----------------------------------------------------------\n";
  cout << "Weighted quick union (with path compression) union:\n";
  cout << "  Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t_end-t_start).count() <<  "ms\n";

  t_start = std::chrono::high_resolution_clock::now();
  for (Site i = 0; i < N; i++) {
    wqupc.connected(p[i], q[i]);
    wqupc.connected(p[i], r[i]);
  }
  t_end = std::chrono::high_resolution_clock::now();
  cout << "Weighted quick union (with path compression) connected:\n";
  cout << "  Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t_end-t_start).count() <<  "ms\n";
}
