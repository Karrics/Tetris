#ifndef TETROMINO_H
#define TETROMINO_H

#include <vector>
#include <memory>

template <typename T>
class Tetromino {
public:
    Tetromino(const std::vector<std::vector<T>>& shape, T x = 0, T y = 0);
    void rotate();
    void move(int dx, int dy);
    const std::vector<std::vector<T>>& getShape() const;
    T getX() const { return x; }
    T getY() const { return y; }

private:
    std::vector<std::vector<T>> shape;
    T x, y;
};

#endif // TETROMINO_H