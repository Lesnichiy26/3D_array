#include "Square.h"


class Cube {
public:
    Cube(uint32_t x, uint32_t y, uint32_t z);

    static Cube MakeArray(uint32_t x, uint32_t y, uint32_t z);

    Cube(const Cube &other);

    ~Cube();

    friend Cube operator+(const Cube &my, const Cube &other);

    friend Cube operator-(const Cube &my, const Cube &other);

    friend Cube operator*(const Cube &my, uint32_t mult);

    friend Cube operator*(uint32_t mult, const Cube &my);

    friend bool EqualSize(const Cube &my, const Cube &other);

    friend std::ostream &operator<<(std::ostream &stream, Cube& my);

    friend std::istream &operator>>(std::istream &stream, Cube& my);

    Square operator[](uint32_t i);

    Cube &operator=(const Cube &other);

private:
    uint32_t GetValue(uint32_t id) const;

    void WriteValue(uint32_t x, uint32_t id);

    uint32_t size_x;
    uint32_t size_y;
    uint32_t size_z;
    uint8_t *help_mas;
    uint16_t *mas;
};