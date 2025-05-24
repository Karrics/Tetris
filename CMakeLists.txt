cmake_minimum_required(VERSION 3.14)
project(Tetris)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)  # Включаем автоматическую генерацию moc-файлов

# Явно указываем путь к Qt
set(Qt6_DIR "/opt/homebrew/Cellar/qt")

# Поиск компонентов Qt
find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)


include_directories(
    include
    /opt/homebrew/Cellar/qt/6.9.0/include
    /opt/homebrew/Cellar/qt/6.9.0/include/QtWidgets
    /opt/homebrew/Cellar/qt/6.9.0/include/QtCore
    /opt/homebrew/Cellar/qt/6.9.0/include/QtGui

)

# Создаем исполняемый файл
add_executable(Tetris
    src/main.cpp
    src/Game.cpp
    src/Board.cpp
    src/Tetromino.cpp
    src/InputHandler.cpp    
    include/Board.hpp
    include/Game.hpp
    include/InputHandler.hpp
    include/Tetromino.hpp
)

# Линкуем библиотеки Qt
target_link_libraries(Tetris PRIVATE
    Qt6::Widgets
    Qt6::Core
    Qt6::Gui
)