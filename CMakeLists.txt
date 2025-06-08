cmake_minimum_required(VERSION 3.14)
project(Tetris)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)

# Подключаем Google Test
find_package(GTest REQUIRED)

# Исполняемый файл игры
add_executable(Tetris
    src/main.cpp
    src/Game.cpp
    src/Board.cpp
    src/Tetromino.cpp
    src/InputHandler.cpp
    src/MainMenu.cpp
    include/Game.hpp
    include/Board.hpp
    include/Tetromino.hpp
    include/InputHandler.hpp
    include/MainMenu.hpp
    resources/resources.qrc
)

target_link_libraries(Tetris PRIVATE
    Qt6::Widgets
    Qt6::Core
    Qt6::Gui
)

# Тесты
if(BUILD_TESTS)
    add_executable(TetrisTests
        tests/BoardTests.cpp
        src/Board.cpp
        src/Tetromino.cpp
    )

    target_link_libraries(TetrisTests PRIVATE
        Qt6::Core
        Qt6::Widgets
        Qt6::Gui
        GTest::gtest
        GTest::gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(TetrisTests)
endif()