#include "Cube.h"


Cube::Cube(uint32_t x, uint32_t y, uint32_t z) :
        size_x(x),
        size_y(y),
        size_z(z),
        mas(new uint16_t[x * y * z]),
        help_mas(new uint8_t[(x * y * z + BYTE_SIZE - 1) / BYTE_SIZE]) {}


Cube Cube::MakeArray(uint32_t x, uint32_t y, uint32_t z) {
    return Cube(x, y, z);
}


Cube::Cube(const Cube &other) {
    if (this != &other) {
        size_x = other.size_x;
        size_y = other.size_y;
        size_z = other.size_z;
        mas = new uint16_t[size_x * size_y * size_z];
        help_mas = new uint8_t[(size_x * size_y * size_z + BYTE_SIZE - 1) / BYTE_SIZE];
        for (uint32_t i = 0; i < size_x * size_y * size_z; i++) {
            mas[i] = other.mas[i];
        }
        for (uint32_t i = 0; i < (size_x * size_y * size_z + BYTE_SIZE - 1) / BYTE_SIZE; i++) {
            help_mas[i] = other.help_mas[i];
        }
    }
}


Cube::~Cube() {
    delete[] mas;
    delete[] help_mas;
}


std::ostream &operator<<(std::ostream &stream, Cube &my) {
    for (uint32_t i = 0; i < my.size_x; i++) {
        for (uint32_t j = 0; j < my.size_y; j++) {
            for (uint32_t k = 0; k < my.size_z; k++) {
                uint32_t num = my.GetValue(i * my.size_z * my.size_y + j * my.size_z + k);
                stream << num << ' ';
            }
        }
    }
    return stream;
}


std::istream &operator>>(std::istream &stream, Cube &my) {
    while (!stream.eof()) {
        for (uint32_t i = 0; i < my.size_x; i++) {
            for (uint32_t j = 0; j < my.size_y; j++) {
                for (uint32_t k = 0; k < my.size_z; k++) {
                    uint32_t num;
                    stream >> num;
                    my.WriteValue(num, i * my.size_z * my.size_y + j * my.size_z + k);
                }
            }
        }
    }
    return stream;
}


Cube &Cube::operator=(const Cube &other) {
    if (this == &other) {
        return *this;
    }
    size_x = other.size_x;
    size_y = other.size_y;
    size_z = other.size_z;
    delete [] mas;
    delete [] help_mas;
    mas = new uint16_t[size_x * size_y * size_z];
    help_mas = new uint8_t[(size_x * size_y * size_z + BYTE_SIZE - 1) / BYTE_SIZE];
    for (uint32_t i = 0; i < size_x * size_y * size_z; i++) {
        mas[i] = other.mas[i];
    }
    for (uint32_t i = 0; i < (size_x * size_y * size_z + BYTE_SIZE - 1) / BYTE_SIZE; i++) {
        help_mas[i] = other.help_mas[i];
    }
    return *this;
}


uint32_t Cube::GetValue(uint32_t id) const {
    uint16_t first_half = mas[id];
    uint8_t second_half = help_mas[id / BYTE_SIZE];
    uint32_t THIRD_MASK = Exponentiation(2, id % BYTE_SIZE);
    uint32_t last_bit = second_half & THIRD_MASK;
    if (last_bit) {
        last_bit = 1;
    }
    return first_half + Exponentiation(last_bit * 2, LAST_BIT_POSITION); // 2 ^ 16 is one 1 and sixteen 0
}


void Cube::WriteValue(uint32_t x, uint32_t id) {
    mas[id] = x & FIRST_MASK; // to take first 16 bits
    uint32_t last_bit = x & SECOND_MASK; // to take last bit
    uint32_t THIRD_MASK = Exponentiation(2, id % BYTE_SIZE);
    help_mas[id / BYTE_SIZE] &= ~THIRD_MASK;
    if (last_bit) {
        last_bit = 1;
        help_mas[id / BYTE_SIZE] |= Exponentiation(last_bit * 2,id % BYTE_SIZE); // potential bug here (need to check 2 cases)
    }
}


bool EqualSize(const Cube &my, const Cube &other) {
    return (my.size_x == other.size_x && my.size_y == other.size_y && my.size_z == other.size_z);
}


Cube operator+(const Cube &my, const Cube &other) {
    if (!EqualSize(my, other)) {
        throw std::invalid_argument("Not equal size.");
    }
    Cube res = Cube::MakeArray(my.size_x, my.size_y, my.size_z);
    for (uint32_t i = 0; i < my.size_x; i++) {
        for (uint32_t j = 0; j < my.size_y; j++) {
            for (uint32_t k = 0; k < my.size_z; k++) {
                uint32_t num = my.GetValue(i * my.size_z * my.size_y + j * my.size_z + k);
                num = num + other.GetValue(i * my.size_z * my.size_y + j * my.size_z + k);
                res.WriteValue(num, i * my.size_z * my.size_y + j * my.size_z + k);
            }
        }
    }
    return res;
}


Cube operator-(const Cube &my, const Cube &other) {
    if (!EqualSize(my, other)) {
        throw std::invalid_argument("Not equal size.");
    }
    Cube res = Cube::MakeArray(my.size_x, my.size_y, my.size_z);
    for (uint32_t i = 0; i < my.size_x; i++) {
        for (uint32_t j = 0; j < my.size_y; j++) {
            for (uint32_t k = 0; k < my.size_z; k++) {
                uint32_t num = my.GetValue(i * my.size_z * my.size_y + j * my.size_z + k);
                num -= other.GetValue(i * my.size_z * my.size_y + j * my.size_z + k);
                res.WriteValue(num, i * my.size_z * my.size_y + j * my.size_z + k);
            }
        }
    }
    return res;
}


Cube operator*(const Cube &my, uint32_t mult) {
    Cube res = Cube::MakeArray(my.size_x, my.size_y, my.size_z);
    for (uint32_t i = 0; i < my.size_x; i++) {
        for (uint32_t j = 0; j < my.size_y; j++) {
            for (uint32_t k = 0; k < my.size_z; k++) {
                uint32_t num = my.GetValue(i * my.size_z * my.size_y + j * my.size_z + k);
                num = num * mult;
                res.WriteValue(num, i * my.size_z * my.size_y + j * my.size_z + k);
            }
        }
    }
    return res;
}


Cube operator*(uint32_t mult, const Cube &my) {
    Cube res = Cube::MakeArray(my.size_x, my.size_y, my.size_z);
    for (uint32_t i = 0; i < my.size_x; i++) {
        for (uint32_t j = 0; j < my.size_y; j++) {
            for (uint32_t k = 0; k < my.size_z; k++) {
                uint32_t num = my.GetValue(i * my.size_z * my.size_y + j * my.size_z + k);
                num = num * mult;
                res.WriteValue(num, i * my.size_z * my.size_y + j * my.size_z + k);
            }
        }
    }
    return res;
}


Square Cube::operator[](uint32_t i) {
    Square square(size_x, size_y, size_z, i, mas, help_mas);
    if (i >= size_x) {
        throw std::invalid_argument("Out of range.");
    }
    return square;
}