//
// Created by KoenDR06 on 10/10/24.
//

#include <complex>
#include <cstdint>
#include <cstring>
#include <bitset>

#define INTEGER_BITS 16

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
        uint64_t data = *reinterpret_cast<uint64_t*>(&d);
        number = (int64_t)((data & 0xFFFFFFFFFFFFF) + 4503599627370496);

        int shift = 11 - INTEGER_BITS;
        if (shift > 0) {
            number <<= shift;
        } else {
            number >>= -shift;
        }

        int exponent = (int)(((data >> 52) & 0x7FF) - 1023);

        if (exponent > 0) {
            number <<= exponent;
        } else {
            number >>= -exponent;
        }

        int signBit = (int)(data >> 63);
        if (signBit == 1) {
            number *= -1;
        }

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

    [[nodiscard]] double to_double() const {
        double res = 0;
        TYPE absNumber = this->number;
        bool negative = false;
        if (this->number < 0) {
            negative = true;

            absNumber = ~absNumber;
            absNumber += 1;
        }

        int i = BITS - 2;
        while (i >= 0) {
            int bit = (int)((absNumber >> (i--)) & 0x1);
            if (bit == 1) {
                res += std::exp(std::log(2) * (i-BITS+3));
            }
        }

        res *= 1L<<(INTEGER_BITS-1);

        if (negative) {
            res *= -1;
        }

        return res;
    }
};