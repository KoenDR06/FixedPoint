//
// Created by KoenDR06 on 10/10/24.
//

#include <iostream>
#include "FixedPoint.h"
#include <iomanip>

int main() {
    std::cout << std::setprecision(10);
    constexpr double floatA = -45.23;
    constexpr double floatB = 3;

    FixedPoint a = FixedPoint(floatA);
    FixedPoint b = FixedPoint(floatB);

    std::cout << a.to_double() << std::endl;
    std::cout << b.to_double() << std::endl;
    std::cout << (a/b).to_double() << std::endl;
    return 0;
}