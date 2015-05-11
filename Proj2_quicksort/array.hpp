#if !defined(__array_hpp)
#define __cs303_vector_hpp

#include <initializer_list>
#include <iostream>
#include <memory>

using std::istream;
using std::ostream;

namespace cs303 { // This allows our class array to peacefully coexist with other classes named array (e.g., std::array). (p. 483)
  template<typename T> class array { // Classes can be templated just like functions for the purposes of generic programming. (p. 830)
    friend ostream &operator<<(ostream &os, const array &v) { // The << operator overloaded as a friend function. (p. 581)
      // Print the array to an output stream.
      for (long i = 0; i < v.size(); i++) {
	os << v[i] << '\n';
      }
      return os;
    };

  public: // Publicly accessible elements. (p. 511)
    array(long int N);        // Constructor: create an array to hold N things. (p. 524)
    array(const array<T> &v); // Constructor: create an array the same size as v and copy the contents of v (i.e., clone v).
    // array(std::initializer_list<T> il); // Constructor: new in C++11---initializer lists! (p. 1051)
  
    ~array(); // Destructor. (p. 528)

    inline T& operator[](int i) const {return a[i];}; // Overloaded array reference operator. (p. 564)
    array<T>& operator=(const array<T> &v);           // Overloaded assignment operator: copy the contents of v into the array. 
  
    inline long int size() const {return n;}          // Return the number of elements in the array.

    void quicksort(); // Quicksort!

  protected: // Elements accessible only to member functions of this class or derived classes. (p. 745)
    long int n;
    T *a;

    void quicksort(long int lo, long int hi);
    long int partition(long int lo, long int hi);

  private: // Elements accessible only to member functions of this class. (p. 511)
  };
}
#endif
