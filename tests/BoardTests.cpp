#include "../include/Board.hpp"
#include "../include/Tetromino.hpp"
#include <gtest/gtest.h>

// Тест 1: Проверка начального состояния доски
TEST(BoardTest, InitialState) {
    Board board(nullptr);
    EXPECT_FALSE(board.isGameOver()); 
    for (int y = 0; y < Board::HEIGHT; ++y) {
        for (int x = 0; x < Board::WIDTH; ++x) {
            EXPECT_EQ(board.getColorAt(x, y), Qt::transparent); 
        }
    }
}

// Тест 2: Проверка коллизии при выходе за границы
TEST(BoardTest, CollisionOutOfBounds) {
    Board board(nullptr);
    Tetromino tetromino;
    tetromino.setX(-1); 
    EXPECT_TRUE(board.isCollision(tetromino));

    tetromino.setX(Board::WIDTH); 
    EXPECT_TRUE(board.isCollision(tetromino));
}

// Тест 3: Проверка очистки строк
TEST(BoardTest, ClearLines) {
    Board board(nullptr);

    for (int x = 0; x < Board::WIDTH; ++x) {
        board.placeBlock(x, 18, Qt::red);
        board.placeBlock(x, 19, Qt::red);
    }
    EXPECT_EQ(board.clearLines(), 2); 
    EXPECT_EQ(board.getColorAt(0, 19), Qt::transparent); 
}

// Тест 4: Проверка завершения игры
TEST(BoardTest, GameOver) {
    Board board(nullptr);
    for (int x = 0; x < Board::WIDTH; ++x) {
        board.placeBlock(x, 0, Qt::red);
    }
    board.checkGameOver();
    EXPECT_TRUE(board.isGameOver()); 
}