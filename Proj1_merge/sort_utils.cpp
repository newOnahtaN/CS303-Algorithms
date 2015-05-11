#include <string> // The string class: pg 131
#include <vector> // The vector class: pg 1012

// The standard namespace (std::): pg 59
using std::string;
using std::vector;

#include "sort.hpp"

// C++ templates are very powerful.  They are also very confusing.  See the discussion starting on pg 419 in Prata.

//----------------------
// Insertion sort.

template <typename T> // template, typename: pg 419
void rml_insertion_sort (vector<T> &a) { // vector: pg 1012; & (reference): pg 383
  for (unsigned long int i = 1; i < a.size(); i++) {
    for (unsigned long int j = i; (j > 0) && (a[j] < a[j-1]); j--) {
      std::swap(a[j], a[j-1]);  // swap: pg 1294, 1297
    }
  }
}

//--------------------------------------------
// Check whether two vectors are identical.

template <typename T>
bool are_identical (vector<T> &a, vector<T> &b)
{
  for (unsigned long int k = 0; k < a.size(); k++) {
    if (a[k] != b[k]) {
      return false;
    }
  }
  return true;
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

template void rml_insertion_sort<int>(vector<int>&);
template void rml_insertion_sort<double>(vector<double>&);
template void rml_insertion_sort<string>(vector<string>&);

template bool are_identical<int>(vector<int>&, vector<int>&);
template bool are_identical<double>(vector<double>&, vector<double>&);
template bool are_identical<string>(vector<string>&, vector<string>&);

