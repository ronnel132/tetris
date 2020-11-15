#include <vector>

#include "Tetromino.h"

class Board {
private:
    Tetromino* m_active;
    std::vector<bool> m_board;
    static const int WIDTH = 10;
    static const int HEIGHT = 20;

    void ClearLines();
public:
    Board();
    ~Board();

    inline int GetWidth() const { return WIDTH; }
    inline int GetHeight() const { return HEIGHT; }
    inline bool GetBoardValue(size_t row, size_t column) const {
        return m_board[row * WIDTH + column];
    }

    void Render() const;
    void ProcessCommand(Command c);
    void ProcessTick();
};
