#include "Plain.h"


class Square {
public:
    Square(uint32_t x_, uint32_t y_, uint32_t z_, uint32_t i, uint16_t *mas, uint8_t *help_mas);

    Plain operator[](uint32_t i);

private:
    uint16_t *mas;
    uint8_t *help_mas;
    uint32_t sq_size_z;
    uint32_t sq_size_y;
    uint32_t sq_size_x;
    uint32_t prev_ind;
};
