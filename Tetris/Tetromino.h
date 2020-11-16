#pragma once

#include <string>

class Board;
enum class Command {
    None,
    MoveUp,
    MoveDown,
    MoveLeft,
    MoveRight,
    RotateCW,
    RotateCCW,
    HardDrop,
    Hold
};

enum class TetrominoType {
    I = 0,
    O = 1,
    T = 2,
    J = 3,
    L = 4,
    S = 5,
    Z = 6
};

enum class Rotation {
    Zero = 0,
    Ninety = 1,
    OneEighty = 2,
    TwoSeventy = 3
};

class Tetromino {
private:
    const TetrominoType m_type;
    std::tuple<int, int> m_position;
    Rotation m_rotation;
    std::vector<std::tuple<int, int>> m_coords;
public:
    Tetromino(TetrominoType t, std::tuple<int, int>& start_coord);
    void ProcessCommand(const Board& board, Command c);
    const std::vector<std::tuple<int, int>>& GetCoords() const;
    bool HasContact(const Board& board) const;
    bool HasCollision(const Board& board, const std::vector<std::tuple<int, int>>& coords) const;
    void Reset(std::tuple<int, int>& startCoord);
    std::string TypeToString() const;
};

TetrominoType GetRandomTetromino();
std::vector<std::tuple<int, int>> GetTetrominoCoordinates(TetrominoType type, std::tuple<int, int> startCoord, Rotation r);
Rotation RotateNext(Rotation r, bool clockwise);
