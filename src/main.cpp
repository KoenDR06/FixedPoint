//
// Created by KoenDR06 on 10/10/24.
//

#include <iostream>
#include "FixedPoint.h"
#include <iomanip>

int main() {
    int64_t inta = 0b0000000001111111111111111111111111111111111111111111111111111111;
    int64_t intb = 0b0000000001111111111111111111111111111111111111111111111111111111;

    double floatA = 2.4;
    double floatB = -1.3;

    FixedPoint a = FixedPoint(floatA);
    FixedPoint b = FixedPoint(floatB);

    FixedPoint res = a*b;


    std::cout << std::setprecision(100) << a.to_double() << std::endl;
    std::cout << std::setprecision(100) << b.to_double() << std::endl;
    std::cout << std::setprecision(100) << res.to_double() << std::endl;
    std::cout << std::setprecision(100) << res.number << std::endl;
    return 0;
}