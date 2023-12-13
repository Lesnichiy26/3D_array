#include "uint17_t.h"


uint32_t Exponentiation(uint32_t a, uint32_t n) { // binary exponentiation (O(logn)) a ^ n
    if (n == 0)
        return 1;
    if (n % 2 == 1)
        return Exponentiation(a, n - 1) * a;
    else {
        uint32_t b = Exponentiation(a, n / 2);
        return b * b;
    }
}


uint17_t::uint17_t(uint16_t *mas, uint8_t *help_mas, uint32_t id) :
        mas(mas),
        help_mas(help_mas),
        id(id) {}


void uint17_t::operator=(uint32_t value) {
    mas[id] = value & FIRST_MASK;
    uint32_t last_bit = value & SECOND_MASK; // to take last bit
    uint32_t THIRD_MASK = Exponentiation(2, id % BYTE_SIZE);
    help_mas[id / BYTE_SIZE] &= ~THIRD_MASK;
    if (last_bit) {
        last_bit = 1;
        help_mas[id / BYTE_SIZE] |= Exponentiation(last_bit * 2,id % BYTE_SIZE); // potential bug here (need to check 2 cases)
    }
}


std::ostream &operator<<(std::ostream &stream, const uint17_t &x) {
    uint16_t first_half = x.mas[x.id];
    uint8_t second_half = x.help_mas[x.id / BYTE_SIZE];
    uint32_t THIRD_MASK = Exponentiation(2, x.id % BYTE_SIZE);
    uint32_t last_bit = second_half & THIRD_MASK;
    if (last_bit) {
        last_bit = 1;
    }
    stream << first_half + Exponentiation(last_bit * 2, LAST_BIT_POSITION); // 2 ^ 16 is one 1 and sixteen 0
}


uint17_t::operator int() {
    uint16_t first_half = mas[id];
    uint8_t second_half = help_mas[id / BYTE_SIZE];
    uint32_t THIRD_MASK = Exponentiation(2, id % BYTE_SIZE);
    uint32_t last_bit = second_half & THIRD_MASK;
    if (last_bit) {
        last_bit = 1;
    }
    return first_half + Exponentiation(last_bit * 2, LAST_BIT_POSITION);
}


std::istream &operator>>(std::istream &stream, uint17_t uint17) {

    uint32_t  value;
    stream >> value;

    uint17.mas[uint17.id] = value & FIRST_MASK;
    uint32_t last_bit = value & SECOND_MASK; // to take last bit
    uint32_t THIRD_MASK = Exponentiation(2, uint17.id % BYTE_SIZE);
    uint17.help_mas[uint17.id / BYTE_SIZE] &= ~THIRD_MASK;
    if (last_bit) {
        last_bit = 1;
        uint17.help_mas[uint17.id / BYTE_SIZE] |= Exponentiation(last_bit * 2,uint17.id % BYTE_SIZE); // potential bug here (need to check 2 cases)
    }

    return stream;
}
