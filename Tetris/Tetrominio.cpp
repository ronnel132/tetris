#include <vector>
#include <tuple>

#include "Tetromino.h"
#include "Board.h"


TetrominoType GetRandomTetromino() {
    return static_cast<TetrominoType>(rand() % static_cast<int>(TetrominoType::Z));
}

std::vector<std::tuple<int, int>> GetTetrominoCoordinates(TetrominoType type, std::tuple<int, int> startCoord, Rotation r) {
    std::vector<std::tuple<int, int>> newCoords;
    int startX = std::get<0>(startCoord);
    int startY = std::get<1>(startCoord);
    switch (type) {
    case TetrominoType::I:
        if (r == Rotation::Zero || r == Rotation::OneEighty) {
            newCoords.push_back({ startX, startY });
            newCoords.push_back({ startX, startY + 1 });
            newCoords.push_back({ startX, startY + 2 });
            newCoords.push_back({ startX, startY + 3 });
        }
        else {
            newCoords.push_back({ startX, startY });
            newCoords.push_back({ startX + 1, startY });
            newCoords.push_back({ startX + 2, startY });
            newCoords.push_back({ startX + 3, startY });
        }
        break;
    case TetrominoType::O:
        newCoords.push_back({ startX, startY });
        newCoords.push_back({ startX, startY + 1 });
        newCoords.push_back({ startX + 1, startY });
        newCoords.push_back({ startX + 1, startY + 1 });
        break;
    case TetrominoType::T:
        if (r == Rotation::Zero) {
            newCoords.push_back({ startX - 1, startY });
            newCoords.push_back({ startX, startY });
            newCoords.push_back({ startX + 1, startY });
            newCoords.push_back({ startX, startY + 1 });
        }
        else if (r == Rotation::Ninety) {
            newCoords.push_back({ startX + 1, startY });
            newCoords.push_back({ startX + 1, startY + 1 });
            newCoords.push_back({ startX + 1, startY + 2 });
            newCoords.push_back({ startX, startY + 1 });
        }
        else if (r == Rotation::OneEighty) {
            newCoords.push_back({ startX, startY });
            newCoords.push_back({ startX - 1, startY + 1 });
            newCoords.push_back({ startX, startY + 1 });
            newCoords.push_back({ startX + 1, startY + 1 });
        }
        else if (r == Rotation::TwoSeventy) {
            newCoords.push_back({ startX - 1, startY });
            newCoords.push_back({ startX - 1, startY + 1 });
            newCoords.push_back({ startX - 1, startY + 2 });
            newCoords.push_back({ startX, startY + 1 });
        }
        break;
    case TetrominoType::J:
        if (r == Rotation::Zero) {
            newCoords.push_back({ startX, startY });
            newCoords.push_back({ startX, startY + 1 });
            newCoords.push_back({ startX, startY + 2 });
            newCoords.push_back({ startX - 1, startY + 2 });
        }
        else if (r == Rotation::Ninety) {
            newCoords.push_back({ startX - 1, startY });
            newCoords.push_back({ startX - 1, startY + 1 });
            newCoords.push_back({ startX, startY + 1 });
            newCoords.push_back({ startX + 1, startY + 1 });
        }
        else if (r == Rotation::OneEighty) {
            newCoords.push_back({ startX, startY });
            newCoords.push_back({ startX, startY + 1 });
            newCoords.push_back({ startX, startY + 2 });
            newCoords.push_back({ startX + 1, startY });
        }
        else if (r == Rotation::TwoSeventy) {
            newCoords.push_back({ startX - 1, startY });
            newCoords.push_back({ startX, startY });
            newCoords.push_back({ startX + 1, startY });
            newCoords.push_back({ startX + 1, startY + 1});
        }
        break;
    case TetrominoType::L:
        if (r == Rotation::Zero) {
            newCoords.push_back({ startX, startY });
            newCoords.push_back({ startX, startY + 1 });
            newCoords.push_back({ startX, startY + 2 });
            newCoords.push_back({ startX + 1, startY + 2 });
        }
        else if (r == Rotation::Ninety) {
            newCoords.push_back({ startX - 1, startY });
            newCoords.push_back({ startX, startY });
            newCoords.push_back({ startX + 1, startY });
            newCoords.push_back({ startX - 1, startY + 1 });
        }
        else if (r == Rotation::OneEighty) {
            newCoords.push_back({ startX - 1, startY });
            newCoords.push_back({ startX, startY });
            newCoords.push_back({ startX, startY + 1 });
            newCoords.push_back({ startX, startY + 2 });
        }
        else if (r == Rotation::TwoSeventy) {
            newCoords.push_back({ startX - 1, startY + 1 });
            newCoords.push_back({ startX, startY + 1 });
            newCoords.push_back({ startX + 1, startY + 1 });
            newCoords.push_back({ startX + 1, startY });
        }
        break;
    case TetrominoType::S:
        if (r == Rotation::Zero || r == Rotation::OneEighty) {
            newCoords.push_back({ startX, startY });
            newCoords.push_back({ startX + 1, startY });
            newCoords.push_back({ startX, startY + 1 });
            newCoords.push_back({ startX - 1, startY + 1 });
        }
        else if (r == Rotation::Ninety || r == Rotation::TwoSeventy) {
            newCoords.push_back({ startX - 1, startY });
            newCoords.push_back({ startX - 1, startY + 1 });
            newCoords.push_back({ startX, startY + 1 });
            newCoords.push_back({ startX, startY + 2 });
        }
        break;
    case TetrominoType::Z:
        if (r == Rotation::Zero || r == Rotation::OneEighty) {
            newCoords.push_back({ startX, startY });
            newCoords.push_back({ startX - 1, startY });
            newCoords.push_back({ startX, startY + 1 });
            newCoords.push_back({ startX + 1, startY + 1 });
        }
        else if (r == Rotation::Ninety || r == Rotation::TwoSeventy) {
            newCoords.push_back({ startX - 1, startY + 1 });
            newCoords.push_back({ startX - 1, startY + 2 });
            newCoords.push_back({ startX, startY + 1 });
            newCoords.push_back({ startX, startY });
        }
        break;
    default:
        perror("Invalid Tetromino Type");
    }
    return newCoords;
}

Rotation RotateNext(Rotation r, bool clockwise) {
    int index = static_cast<int>(r);
    int delta = clockwise ? 1 : -1;
    return static_cast<Rotation>(((index + delta) % 4 + 4) % 4);
}

Tetromino::Tetromino(TetrominoType t, std::tuple<int, int>& start_coord) : m_type(t), m_rotation(Rotation::Zero), m_position(start_coord) {
    m_coords = GetTetrominoCoordinates(m_type, m_position, Rotation::Zero);
}

bool Tetromino::HasCollision(const Board& board, const std::vector<std::tuple<int, int>>& coords) const {
    for (auto& coord : coords) {
        int x = std::get<0>(coord);
        int y = std::get<1>(coord);
        if (y == board.GetHeight()) return true;
        if (x == -1) return true;
        if (x == board.GetWidth()) return true;
        if (board.GetBoardValue(y, x)) return true;
    }
    return false;
}

void Tetromino::ProcessCommand(const Board& board, Command c) {
    Rotation newRotation = m_rotation;
    std::vector<std::tuple<int, int>> newCoords(m_coords);
    int dx = 0, dy = 0;
    switch (c) {
    case Command::MoveUp:
        dy -= 1;
        break;
    case Command::MoveDown:
        dy += 1;
        break;
    case Command::MoveLeft:
        dx -= 1;
        break;
    case Command::MoveRight:
        dx += 1;
        break;
    case Command::RotateCW:
        newRotation = RotateNext(m_rotation, true);
        newCoords = GetTetrominoCoordinates(m_type, m_position, newRotation);
        break;
    case Command::RotateCCW:
        newRotation = RotateNext(m_rotation, false);
        newCoords = GetTetrominoCoordinates(m_type, m_position, newRotation);
        break;
    case Command::HardDrop:
        while (!HasContact(board)) {
            ProcessCommand(board, Command::MoveDown);
        }
        return;
    }
    for (auto& coord : newCoords) {
        std::get<0>(coord) += dx;
        std::get<1>(coord) += dy;
    }
    if (!HasCollision(board, newCoords)) {
        m_coords = newCoords;
        m_rotation = newRotation;
        std::get<0>(m_position) += dx;
        std::get<1>(m_position) += dy;
    }
}

const std::vector<std::tuple<int, int>>& Tetromino::GetCoords() const {
    return m_coords;
}

bool Tetromino::HasContact(const Board& board) const {
    for (auto it = m_coords.begin(); it != m_coords.end(); it++) {
        int x = std::get<0>(*it);
        int y = std::get<1>(*it);
        if (y == (board.GetHeight() - 1)) return true;
        if (board.GetBoardValue(y + 1, x)) return true;
    }
    return false;
}
