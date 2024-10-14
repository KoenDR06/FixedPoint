//
// Created by KoenDR06 on 10/10/24.
//

#include <complex>

#define INTEGER_BITS 1

#define TYPE int64_t
#define BITS 64
#define XL_TYPE __int128

class FixedPoint {
public:
    TYPE number;

    FixedPoint() {
        number = 0;
    }

    explicit FixedPoint(TYPE n) {
        number = n;
    }

    explicit FixedPoint(double d) {
        unsigned long long bits = *reinterpret_cast<unsigned long long*>(&d);
        int signBit = bits >> 63;
        int exponent = ((bits >> 52) & 0x7FF) - 1023;
        unsigned long long mantissa = (bits & 0xFFFFFFFFFFFFF) + 4503599627370496;

        number = mantissa << 11;
        number >>= -1 * exponent + 1;
    }

    FixedPoint operator+(FixedPoint other) const {
        return FixedPoint(this->number + other.number);
    }

    FixedPoint operator-(FixedPoint other) const {
        return FixedPoint(this->number - other.number);
    }

    FixedPoint operator*(FixedPoint other) const {
        FixedPoint result;

        XL_TYPE res = static_cast<XL_TYPE>(this->number) * static_cast<XL_TYPE>(other.number);
        result.number = static_cast<TYPE>(res >> (BITS - INTEGER_BITS - 1));

        return result;
    }

    bool operator<(FixedPoint other) const {
        return this->number < other.number;
    }

    bool operator>(FixedPoint other) const {
        return this->number > other.number;
    }

    bool operator==(FixedPoint other) const {
        return this->number == other.number;
    }

    bool operator!=(FixedPoint other) const {
        return this->number != other.number;
    }

    double to_double() const {
        double res = 0;
        TYPE positiveNumber = this->number;
        if (this->number>>(BITS-1) == 0x1) {
            positiveNumber = ~positiveNumber;
            positiveNumber++;
        }

        int i = BITS - 2;
        while (i >= 0) {
            int bit = (this->number >> (i--)) & 0x1;
            if (bit == 1) {
                res += std::exp(std::log(2) * (i-BITS+3));
            }
        }

        if (this->number>>(BITS-1) == -1) {
            res *= -1;
        }

        res *= 1L<<(INTEGER_BITS-1);

        return res;
    }
};