#include <iostream>

// source
// https://stackoverflow.com/questions/476272/how-to-properly-overload-the-operator-for-an-ostream

namespace FooNS {
    struct Foo {
        int m_value;
    };

    std::ostream& operator<< (std::ostream& os, const Foo& foo) {
        os << "Inside namespace{Foo}" << std::endl;
        os << foo.m_value << std::endl;
        return os;
    }
} // namespace Foo

int main() {
    // overload the ostream operator in the global namespace is a BAD
    // idea and will not compile in this case;
    // compiler throws an error about ambiguous overload
    
    // 1) use a namespace to encapsulate the class
    // 2) define the overloaded stream operator in that namespace

    FooNS::Foo foo{10};
    std::cout << foo << std::endl;;
    return 0;
}
