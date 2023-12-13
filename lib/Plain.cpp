#include "Plain.h"


Plain::Plain(uint32_t x_, uint32_t y_, uint32_t z_, uint32_t i, uint32_t j, uint16_t *mas, uint8_t *help_mas) :
        pl_size_x(x_),
        pl_size_y(y_),
        pl_size_z(z_),
        prev_ind_i(i),
        prev_ind_j(j),
        mas(mas),
        help_mas(help_mas) {}


uint17_t Plain::operator[](uint32_t k) {
    uint17_t num(mas, help_mas, prev_ind_i * pl_size_z * pl_size_y + prev_ind_j * pl_size_z + k);
    if (k >= pl_size_z) {
        throw std::invalid_argument("Out of range.");
    }
    return num;
}
