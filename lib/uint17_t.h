#include <cstdint>
#include <iostream>


const uint32_t FIRST_MASK = 0b01111111111111111; // 2 ^ 16 - 1
const uint32_t SECOND_MASK = 0b10000000000000000; // 2 ^ 16
const uint32_t LAST_BIT_POSITION = 16;
const uint32_t BYTE_SIZE = 8;


uint32_t Exponentiation(uint32_t a, uint32_t n);


class uint17_t {
public:
    uint17_t(uint16_t *mas, uint8_t *help_mas, uint32_t id);

    void operator=(uint32_t value);

    friend std::ostream &operator<<(std::ostream &stream, const uint17_t &x);

    operator int();

    friend std::istream& operator>>(std::istream& stream, uint17_t arr);

private:
    uint16_t *mas;
    uint8_t *help_mas;
    uint32_t id;
};