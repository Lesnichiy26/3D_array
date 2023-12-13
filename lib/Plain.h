#include "uint17_t.h"


class Plain {
public:
    Plain(uint32_t x_, uint32_t y_, uint32_t z_, uint32_t i, uint32_t j, uint16_t *mas, uint8_t *help_mas);

    uint17_t operator[](uint32_t k);

private:
    uint16_t *mas;
    uint8_t *help_mas;
    uint32_t pl_size_z;
    uint32_t pl_size_y;
    uint32_t pl_size_x;
    uint32_t prev_ind_i;
    uint32_t prev_ind_j;
};
