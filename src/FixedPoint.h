//
// Created by KoenDR06 on 10/10/24.
//

#include <complex>
#include <cstdint>
#include <cstring>
#include <bitset>

#define INTEGER_BITS 13

#define TYPE int64_t
#define BITS 64
#define XL_TYPE __int128
#define XL_BITS 128

class FixedPoint {
public:
    TYPE number;

    FixedPoint() {
        number = 0;
    }

    explicit FixedPoint(TYPE n) {
        number = n;
    }

    explicit FixedPoint(int i) {
        number = (TYPE)i << (BITS - INTEGER_BITS - 1);

        if ((number >> (BITS - INTEGER_BITS - 1)) != i) {
            throw std::runtime_error("Integer constructor out of bounds.");
        }
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

    FixedPoint floor() {
        this->number >>= BITS - INTEGER_BITS - 1;
        this->number <<= BITS - INTEGER_BITS - 1;

        return *this;
    }

    FixedPoint ceil() {
        this->number >>= BITS - INTEGER_BITS - 1;
        this->number++;
        this->number <<= BITS - INTEGER_BITS - 1;

        return *this;
    }

    FixedPoint round() {
        TYPE absNumber = this->number;
        bool negative = false;
        if (this->number < 0) {
            negative = true;
            absNumber = ~absNumber;
            absNumber += 1;
        }

        int firstFractionBit = (int)(absNumber >> (BITS - INTEGER_BITS - 2)) & 0x1;

        if (!((firstFractionBit == 1) ^ !negative)) {
            return this->ceil();
        } else {
            return this->floor();
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

    FixedPoint operator/(FixedPoint other) const {
        FixedPoint result;

        XL_TYPE res = (static_cast<XL_TYPE>(this->number) << (XL_BITS - BITS)) / static_cast<XL_TYPE>(other.number);
        result.number = static_cast<TYPE>(res >> (INTEGER_BITS + 1));

        return result;
    }

    bool operator<(FixedPoint other) const {
        return this->number < other.number;
    }
    bool operator<=(FixedPoint other) const {
        return this->number <= other.number;
    }
    bool operator>(FixedPoint other) const {
        return this->number > other.number;
    }
    bool operator>=(FixedPoint other) const {
        return this->number >= other.number;
    }
    bool operator==(FixedPoint other) const {
        return this->number == other.number;
    }
    bool operator!=(FixedPoint other) const {
        return this->number != other.number;
    }

    bool operator<(int other) const {
        return this->number < FixedPoint(other).number;
    }
    bool operator<=(int other) const {
        return this->number <= FixedPoint(other).number;
    }
    bool operator>(int other) const {
        return this->number > FixedPoint(other).number;
    }
    bool operator>=(int other) const {
        return this->number >= FixedPoint(other).number;
    }
    bool operator==(int other) const {
        return this->number == FixedPoint(other).number;
    }
    bool operator!=(int other) const {
        return this->number != FixedPoint(other).number;
    }

    bool operator<(double other) const {
        return this->number < FixedPoint(other).number;
    }
    bool operator<=(double other) const {
        return this->number <= FixedPoint(other).number;
    }
    bool operator>(double other) const {
        return this->number > FixedPoint(other).number;
    }
    bool operator>=(double other) const {
        return this->number >= FixedPoint(other).number;
    }
    bool operator==(double other) const {
        return this->number == FixedPoint(other).number;
    }
    bool operator!=(double other) const {
        return this->number != FixedPoint(other).number;
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

std::ostream &operator<<(std::ostream &os, FixedPoint const &fp) {
    return os << fp.to_double();
}