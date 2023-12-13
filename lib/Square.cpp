#include "Square.h"


Square::Square(uint32_t x_, uint32_t y_, uint32_t z_, uint32_t i, uint16_t *mas, uint8_t *help_mas) :
        sq_size_x(x_),
        sq_size_y(y_),
        sq_size_z(z_),
        prev_ind(i),
        mas(mas),
        help_mas(help_mas) {}


Plain Square::operator[](uint32_t j) {
    Plain plain(sq_size_x, sq_size_y, sq_size_z, prev_ind, j, mas, help_mas);
    if (j >= sq_size_y) {
        throw std::invalid_argument("Out of range.");
    }
    return plain;
}