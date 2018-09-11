#include <iostream>
#include "numbers/number.hpp"

/// \file sandbox.cpp
/// \brief In this file you can experiment with cjr without exiting the project.
/// \note Code in file has no effect on library behaviour.

int main() {
    std::cout << "cjr sandbox environment" << std::endl;

    // here you can test cjr

//    cjr::number<> a = -145002123, b = 1667778088;
//    a.multiply(b);
//    a.print();

    cjr::number<> a = 678;
    a.power(123);
    a.print();

    return 0;
}