# 🎮 Tetris на Qt

![Игра Tetris](https://avatars.mds.yandex.net/i?id=64a83fc24ddecbd524de22a0e08b54b1_l-4554202-images-thumbs&n=13)  

---

## 📌 Описание 

Классическая игра **Tetris** с использованием **Qt**.  
Падающие фигуры, главное меню и обработка завершения игры.

---

## 🚀 Запуск игры

1. **Скачайте проект**:
    ```bash
    git clone https://github.com/Karrics/Tetris.git

2. **Соберите проект**:
    ```bash
    mkdir build
    cd build
    cmake ..
    make

3. **Запустите игру**:
    ```bash
    ./Tetris

---

## 🎬 Управление

- **Стрелки ←/→** : Двигать фигуру
- **Стрелка ↓** : Ускорить падение
- **Стрелка ↑** : Повернуть фигуру
- **Esc** : Выйти в меню

---

## 📂 Структура проекта

<pre>
Tetris/
├── include/
│   ├── Board.h
│   ├── Game.h
│   ├── MainMenu.h
│   ├── Tetromino.h
│   └── InputHandler.h
├── src/
│   ├── Board.cpp
│   ├── Game.cpp
│   ├── MainMenu.cpp
│   ├── Tetromino.cpp
│   └── InputHandler.cpp
├── resources/
│   └── resources.qrc
├── tests/
│   └── BoardTests.cpp
├── CMakeLists.txt
└── README.md
</pre>    

---

## 💡 Лицензия

MIT License — делайте с проектом что угодно, но сохраняйте упоминание автора.