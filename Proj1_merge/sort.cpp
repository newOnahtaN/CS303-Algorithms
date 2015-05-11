#include <string> 
#include <vector> 


using std::string;
using std::vector;

#include "sort.hpp"

//----------------------
// Prototypes

template <typename T> 
void sub_recursive_mergesort (vector<T> &a, int low, int high, vector<T> &aux);

template <typename T> 
void merge (vector<T> &a, int low, int mid, int high, vector<T> &aux);

//----------------------
// Recursive merge sort.

template <typename T> 
void recursive_mergesort (vector<T> &a) { 
  vector<T> aux(a.size());
  sub_recursive_mergesort(a,0,a.size()-1, aux);
}

template <typename T> 
void sub_recursive_mergesort (vector<T> &a, int low, int high, vector<T> &aux) { 
  if (high <= low)
    return;
  int mid = low + (high - low)/2;
  sub_recursive_mergesort(a, low, mid, aux);
  sub_recursive_mergesort(a, mid+1, high, aux);
  merge(a, low, mid, high, aux);
}

//----------------------
// Iterative merge sort.

template <typename T> 
void iterative_mergesort (vector<T> &a) { 
  int n = a.size();
  vector<T> aux(a.size());
  for (int subSize = 1; subSize < n; subSize = subSize+subSize)
    for (int low = 0; low < n-subSize; low += subSize+subSize)
      if (low+subSize+subSize-1 < n-1)
        merge(a, low, low+subSize-1, low+subSize+subSize-1, aux);
      else
        merge(a, low, low+subSize-1, n-1, aux);
}

//----------------------
// Merging method.

template <typename T> 
void merge (vector<T> &a, int low, int mid, int high, vector<T> &aux) { 
  int i = low;
  int j = mid+1;

  for (int k = low; k <= high; k++)
    aux[k] = a[k];

  for (int k = low; k <= high; k++){

    if (i > mid)
      a[k] = aux[j++];

    else if (j > high)
      a[k] = aux[i++];

    else if (aux[j] < aux[i])
      a[k] = aux[j++];

    else
      a[k] = aux[i++];

  }  

}

// Provoke the instantiation of various classes (explicit instantiation of template function: pg 429).
//
// The preceding templates are just that---templates.  We still need to bring specific instances into existence (this
// is one instance of <<instantiation>>.
//
// The references below refer to specific instances of the template functions above.  This causes the appropriate code
// to be generated automagically by the compiler.
//
// If you want to learn more about how g++ handles template instantiation, see 
// https://gcc.gnu.org/onlinedocs/gcc/Template-Instantiation.html

template void recursive_mergesort<int>(vector<int>&);
template void recursive_mergesort<double>(vector<double>&);
template void recursive_mergesort<string>(vector<string>&);

template void sub_recursive_mergesort<int>(vector<int>&, int, int, vector<int>&);
template void sub_recursive_mergesort<double>(vector<double>&, int, int, vector<double>&);
template void sub_recursive_mergesort<string>(vector<string>&, int, int, vector<string>&);

template void merge<int>(vector<int>&, int, int, int, vector<int>&);
template void merge<double>(vector<double>&, int, int, int, vector<double>&);
template void merge<string>(vector<string>&, int, int, int, vector<string>&);

template void iterative_mergesort<int>(vector<int>&);
template void iterative_mergesort<double>(vector<double>&);
template void iterative_mergesort<string>(vector<string>&);