#include <iostream>
#include <memory>
#include <set>
#include <tuple>

#include "Board.h"

Board::Board() : m_active(nullptr), m_board(WIDTH * HEIGHT), m_gameOver(false) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            m_board[i * WIDTH + j] = false;
        }
    }
}

void Board::Render() const {
    if (m_gameOver) {
        std::cout << "GAME OVER." << std::endl;;
    }
    std::cout << "############" << std::endl;

    for (int i = 0; i < HEIGHT; i++) {
        std::cout << "#";
        for (int j = 0; j < WIDTH; j++) {
            bool tetriminoBlock = false;
            if (m_active) {
                const std::vector<std::tuple<int, int>>& coords = m_active->GetCoords();
                for (auto it = coords.begin(); it != coords.end(); it++) {
                    int x = std::get<0>(*it);
                    int y = std::get<1>(*it);
                    if (x == j && y == i) tetriminoBlock = true;
                }
            }
            if (m_board[i * WIDTH + j] || tetriminoBlock) {
                std::cout << "0";
            }
            else {
                std::cout << " ";
            }
        }
        std::cout << "#" << std::endl;
    }

    std::cout << "############" << std::endl;
}

void Board::ProcessCommand(Command c) {
    if (!m_active) return;
    m_active->ProcessCommand(*this, c);
    if (c == Command::HardDrop) {
        system("cls");
        // One tick merge the active tetromino into the board, another to init the new tetromino
        ProcessTick();
        ProcessTick();
        Render();
    }
}

void Board::ClearLines() {
    std::set<int, std::greater<int>> linesToClear;
    for (int i = HEIGHT - 1; i >= 0; i--) {
        bool clearLine = true;
        for (int j = 0; j < WIDTH; j++) {
            if (!GetBoardValue(i, j)) clearLine = false;
        }
        if (clearLine) {
            linesToClear.insert(i);
        }
    }

    std::vector<bool> newBoard(WIDTH * HEIGHT);
    int i_prime = HEIGHT - 1; // index into newBoard
    for (int i = HEIGHT - 1; i >= 0; i--) {
        if (linesToClear.find(i) != linesToClear.end()) {
            continue;
        }
        for (int j = 0; j < WIDTH; j++) {
            newBoard[i_prime * WIDTH + j] = GetBoardValue(i, j);
        }
        i_prime--;
    }
    while (i_prime >= 0) {
        for (int j = 0; j < WIDTH; j++) {
            newBoard[i_prime * WIDTH + j] = false;
        }
        i_prime--;
    }
    m_board = newBoard;
}

void Board::ProcessTick() {
    if (!m_active) {
        TetrominoType t = GetRandomTetromino();
        std::tuple<int, int> startCoord(4, 0);
        m_active = std::make_unique<Tetromino>(t, startCoord);
        if (m_active->HasCollision(*this, m_active->GetCoords())) {
            m_gameOver = true;
        }
        return;
    }
    if (m_active->HasContact(*this)) {
        auto coords = m_active->GetCoords();
        for (auto it = coords.begin(); it != coords.end(); it++) {
            int x = std::get<0>(*it);
            int y = std::get<1>(*it);
            m_board[y * WIDTH + x] = true;
        }
        m_active = nullptr;
        ClearLines();
    }
    else {
        m_active->ProcessCommand(*this, Command::MoveDown);
    }
}

void Board::Reset() {
    m_active = nullptr;
    m_gameOver = false;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            m_board[i * WIDTH + j] = false;
        }
    }
}
