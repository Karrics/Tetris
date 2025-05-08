#include "../include/Tetromino.h"

template <typename T>
Tetromino<T>::Tetromino(const std::vector<std::vector<T>>& shape, T x, T y)
    : shape(shape), x(x), y(y) {}

template <typename T>
void Tetromino<T>::rotate() {
    std::vector<std::vector<T>> rotated(shape[0].size(), std::vector<T>(shape.size()));
    for (size_t i = 0; i < shape.size(); ++i) {
        for (size_t j = 0; j < shape[i].size(); ++j) {
            rotated[j][shape.size() - 1 - i] = shape[i][j];
        }
    }
    shape = rotated;
}

template <typename T>
void Tetromino<T>::move(int dx, int dy) {
    x += dx;
    y += dy;
}

template <typename T>
const std::vector<std::vector<T>>& Tetromino<T>::getShape() const {
    return shape;
}

// Явная специализация для int (обязательно для компиляции)
template class Tetromino<int>;