// decltype by elinao
// Comprehensive guide to C++ decltype rules and examples
//   C++11 and later
 
#include <iostream>
#include <type_traits>
#include <vector>
#include <string>
#include <typeinfo>

// Helper function to print the type name (implementation may vary across compilers)
template <typename T>
void print_type(const T& var, const std::string& var_name) {
    std::cout << var_name << " : " << typeid(var).name() << '\n';
}

// Rule 1: Unparenthesized identifier or class member access
// If the expression is an unparenthesized identifier or class member access,
// decltype yields the declared type of the entity.
void rule1() {
    int x = 0;
    decltype(x) a = 1; // a is int
    print_type(a, "a");
}

// Rule 2: Lvalue expressions result in T&
// If the expression is an lvalue, decltype yields a reference type.
void rule2() {
    int x = 0;
    decltype((x)) b = x; // b is int&
    print_type(b, "b");
}

// Rule 3: Xvalue expressions result in T&&
// If the expression is an xvalue (e.g., std::move), decltype yields an rvalue reference.
int&& get_rvalue() {
    static int val = 42;
    return std::move(val);
}

void rule3() {
    decltype(get_rvalue()) c = get_rvalue(); // c is int&&
    print_type(c, "c");
}

// Rule 4: Prvalue expressions result in T
// If the expression is a prvalue, decltype yields the type T.
void rule4() {
    decltype(42) d = 42; // d is int
    print_type(d, "d");
}

// Function return type deduction using decltype
// Useful in template functions where the return type depends on the parameter types.
template <typename T, typename U>
auto add(T t, U u) -> decltype(t + u) {
    return t + u;
}

void function_return_type() {
    auto sum = add(3, 4.5); // sum is double
    print_type(sum, "sum");
}

// Using decltype with complex types
// Simplifies type declarations for iterators and other complex expressions.
void complex_types() {
    std::vector<int> vec = {1, 2, 3};
    decltype(vec.begin()) it = vec.begin(); // it is std::vector<int>::iterator
    print_type(it, "it");
}

// Demonstrating decltype(auto) introduced in C++14
// Combines the behavior of auto and decltype for type deduction.
int global_var = 10;
int& get_ref() {
    return global_var;
}

auto get_auto() {
    return get_ref(); // Returns by value (int)
}

decltype(auto) get_decltype_auto() {
    return get_ref(); // Returns by reference (int&)
}

void decltype_auto_demo() {
    auto val = get_auto();               // val is int
    decltype(auto) ref = get_decltype_auto(); // ref is int&
    print_type(val, "val");
    print_type(ref, "ref");
}

// Demonstrating the effect of parentheses in decltype
// Parentheses can change the deduced type from non-reference to reference.
void parentheses_effect() {
    int x = 0;
    decltype(x) a = 1;    // a is int
    decltype((x)) b = x;  // b is int&
    print_type(a, "a");
    print_type(b, "b");
}


int   main( ) {
  std::cout << "Rule 1:\n";
  rule1();

  std::cout << "\nRule 2:\n";
  rule2();

  std::cout << "\nRule 3:\n";
  rule3();

  std::cout << "\nRule 4:\n";
  rule4();

  std::cout << "\nFunction Return Type:\n";
  function_return_type();

  std::cout << "\nComplex Types:\n";
  complex_types();

  std::cout << "\ndecltype(auto) Demo:\n";
  decltype_auto_demo();

  std::cout << "\nParentheses Effect:\n";
  parentheses_effect();

  return 0;
}
