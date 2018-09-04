//
// Created by wein on 18/08/18.
//

// source
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4066.htm
// The problem is that the delimiter in the ostream_iterator constructor
// call is better described as a suffix than a delimiter.

// NOTE 1
// while using universal reference, how can one use T::value_type as
// a parameter now that T will always be a reference?
// see:
// https://stackoverflow.com/questions/35407243/using-a-class-template-in-a-function-template-with-universal-reference-parameter
// key: std::remove_reference<T>::type

// NOTE 2
// if the value_type of the container is a user-defined class, there
// must an overloaded ostream operator<< for this type (required by 
// the ostream object wrapped by the iterator)

#include <algorithm>
#include <vector>
#include <iterator>
#include <iostream>

template <class T>
void prt(T &&container, const char *delimit, const char *open__ = nullptr,
         const char *close__ = nullptr) {
  if (!container.empty()) {
    if (!open__) {
      open__ = "(";
    }
    if (!close__) {
      close__ = ")";
    }
    std::cout << open__;
    std::copy(container.cbegin(), container.cend() - 1,
              std::ostream_iterator<
                  typename std::remove_reference<T>::type::value_type>(
                  std::cout, delimit));
    std::copy(container.cend() - 1, container.cend(),
              std::ostream_iterator<
                  typename std::remove_reference<T>::type::value_type>(
                  std::cout, ""));
    std::cout << close__;
  }
}

void test_empty() {
    prt(std::vector<int>{}, "", "(", ")\n");
}

void test_lvalue_ref() {
    auto a = std::vector<double>{1.010, 2.13, 142.12};
    prt(a, ", ");
    std::cout << std::endl;
}

void test_rvalaue_ref() {
    prt(std::vector<double>{1.010, 2.13, 142.12}, ", ");
    std::cout << std::endl;
}

namespace CustomType {

class A {
public:
    char label = 'A';
};

std::ostream& operator<< (std::ostream& os, const A& a) {
    os << a.label;
    return os;
}

}


void test_custom_type() {
    prt(std::vector<CustomType::A>(10), "");
    std::cout << std::endl;
}


int main() {
    test_empty();
    test_lvalue_ref();
    test_rvalaue_ref();
    test_custom_type();
    return 0;
}
