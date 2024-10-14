//
// Created by KoenDR06 on 10/10/24.
//

#include <iostream>
#include "FixedPoint.h"
#include <iomanip>

int main() {
    std::cout << std::setprecision(10);
    int64_t inta = 0b0000000001111111111111111111111111111111111111111111111111111111;
    int64_t intb = 0b0000000001111111111111111111111111111111111111111111111111111111;

    double floatA = -7.43;
    double floatB = 20.5;

    FixedPoint a = FixedPoint(floatA);
    FixedPoint b = FixedPoint(floatB);

    FixedPoint res = a*b;


    std::cout << a.to_double() << std::endl;
    std::cout << b.to_double() << std::endl;
    std::cout << res.to_double() << std::endl;
    std::cout << res.number << std::endl;
    return 0;
}