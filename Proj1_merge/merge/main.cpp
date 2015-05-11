#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <vector>

using std::cin;  // using (namespaces): pg 35, 482
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;

#include "sort.hpp"

template <typename T> void test(long int &n); // function prototype
template <> void test<string>(long int &n); // function prototype

int main (int argc, char **argv) {
  long int n;

  // Prompt the user for the size of the list.
  cout << "Enter the problem size: ";   // cout: pg 36
  cin >> n;                             // cin:  pg 46

  if (n < 0) {
    cerr << "Bogus problem size specified. Say \"bye-bye\" to the nice program!" << endl; // cerr: pg 1067; endl: pg 37
    return (16);
  }

  //---------------------------------------------
  // Test integer instantiation.
  cout << "---------------------------------------------------\n";
  cout << "Testing integer instantiation...\n" << endl;
  test<int>(n); // Implicit instantiation of template function: pg 429

  //---------------------------------------------
  // Test double instantiation.
  cout << "---------------------------------------------------\n";
  cout << "Testing double instantiation...\n" << endl;
  test<double>(n);

  //---------------------------------------------
  // Test string instantiation.
  cout << "---------------------------------------------------\n";
  cout << "Testing string instantiation...\n" << endl;
  test<string>(n);

  return 0;
}

template <typename T>
void test(long int &n)  // Function template: pg 419
{
  //----------------------
  // Initialization. 

  // Exception handling?  we don't need no stinkin' exception handling...
  vector<T> v0(n); // vector: pg 1012

  // Fill v0 with random numbers. 
  std::mt19937 e(0); // Everyone's favorite pseudo-random number engine: the Mersenne twister.
  std::uniform_int_distribution<int> u(-1000,1000); // Convert engine output to a uniform integer distribution.
  for (auto &w : v0) { // Range-for: pg 233 (new in C++11)
    w = u(e);
  }

  //----------------------------------------------------------------
  // Use the vector member function sort() to check our work.

  vector<T> v1(v0); // Copy constructor for the vector template class; v1 is a clone of v0.
  
  auto t_start = std::chrono::high_resolution_clock::now(); // love them colons...
  std::sort(v1.begin(), v1.end());
  auto t_end = std::chrono::high_resolution_clock::now();
  cout << "Library sort:\n";
  cout << "  Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t_end-t_start).count() <<  "ms\n";

  //---------------------------------
  // Apply a recursive mergesort.

  auto v2(v0); // auto: pg 370 (new in C++11)---let the initialization determine the type for v2.

  t_start = std::chrono::high_resolution_clock::now();
  //iterative_mergesort(v2);
  recursive_mergesort(v2);
  //rml_insertion_sort(v2);
  t_end = std::chrono::high_resolution_clock::now();
  cout << "Recursive mergesort<" << typeid(v0[0]).name() << ">:\n";
  cout << "  Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t_end-t_start).count() <<  "ms\n";
  cout << "  Correctly sorted? " << (are_identical(v1, v2) ? "yes" : "no") << "\n";

  //---------------------------------
  // Apply a user-supplied sort.

  auto v3(v0); // auto: pg 370 (new in C++11)---let the initialization determine the type for v2.

  t_start = std::chrono::high_resolution_clock::now();
  iterative_mergesort(v3);
  //recursive_mergesort(v2);
  //rml_insertion_sort(v2);
  t_end = std::chrono::high_resolution_clock::now();
  cout << "Iterative mergesort<" << typeid(v0[0]).name() << ">:\n";
  cout << "  Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t_end-t_start).count() <<  "ms\n";
  cout << "  Correctly sorted? " << (are_identical(v1, v2) ? "yes" : "no") << "\n";

  // No need to clean up---the vector objects and associated resource are freed automagically!
}

template <>
void test<string>(long int &n)  // Explicit template specialization: pg 425. 
{
  //----------------------
  // Initialization. 

  // The specialization for strings is needed since generating random strings can't be done with the code above.
  // (Well, you can use the code above to generate random strings, but they aren't printable.)
  // However, I'm too lazy to implement random string generation, so I'll just hardwire the test case.

  vector<string> v0 {"fum", "fie", "fee", "foo", "foe", "bar", "ick", "ack", "yuck"};

  //----------------------------------------------------------------
  // Use the vector member function sort() to check our work.

  vector<string> v1(v0); // Copy constructor for the vector template class; v1 is a clone of v0.
  
  auto t_start = std::chrono::high_resolution_clock::now();
  std::sort(v1.begin(), v1.end());
  auto t_end = std::chrono::high_resolution_clock::now();
  cout << "Library sort:\n";
  cout << "  Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t_end-t_start).count() <<  "ms\n";

  //---------------------------------
  // Apply Resursive mergesort.

  auto v2(v0); // auto: pg 370 (new in C++11)---let the initialization determine the type for v2.

  t_start = std::chrono::high_resolution_clock::now();
  //iterative_mergesort(v2);
  recursive_mergesort(v2);
  //rml_insertion_sort(v2);
  t_end = std::chrono::high_resolution_clock::now();
  cout << "Recursive mergesort<" << typeid(v0[0]).name() << ">:\n";
  cout << "  Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t_end-t_start).count() <<  "ms\n";
  cout << "  Correctly sorted? " << (are_identical(v1, v2) ? "yes" : "no") << "\n";

    //---------------------------------
  // Apply Iterative mergesort.

  auto v3(v0); 

  t_start = std::chrono::high_resolution_clock::now();
  iterative_mergesort(v3);
  //recursive_mergesort(v2);
  //rml_insertion_sort(v2);
  t_end = std::chrono::high_resolution_clock::now();
  cout << "Iterative mergesort<" << typeid(v0[0]).name() << ">:\n";
  cout << "  Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t_end-t_start).count() <<  "ms\n";
  cout << "  Correctly sorted? " << (are_identical(v1, v2) ? "yes" : "no") << "\n";

  
}
