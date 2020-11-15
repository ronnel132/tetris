// Tetris.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <conio.h>
#include <chrono>
#include <condition_variable>
#include <deque>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

#include "Board.h"
#include "Tetromino.h"

class GameController {
private:
    static const unsigned int TICK_INTERVAL_MS = 1000;
    static char GetKeyPress()
    {
		// http://www.cplusplus.com/forum/general/52803/#msg286178
        char key = 127;

        key = _getch();
        if (key == 0 || key == -32)  {
            key = _getch();

            if (key == 72) //up arrow
            {
                key = 'u';
            }
            else if (key == 75) //left arrow
            {
                key = 'l';
            }
            else if (key == 77) //right
            {
                key = 'r';
            }
            else if (key == 80) //down
            {
                key = 'd';
            }
        }
        return key;
    }
public:
    static void Run() {
        Board board;
        using clock = std::chrono::high_resolution_clock;
        std::condition_variable cv;
        std::mutex mutex;
        std::deque<char> commands; // protected by m

        // I/O thread
        // https://gist.github.com/vmrob/ff20420a20c59b5a98a1
        std::thread io{ [&] {
            char key;
            while (true) {
                key = GetKeyPress();
                std::lock_guard<std::mutex> lock{ mutex };
                commands.push_back(key);
                cv.notify_one();
            }
        } };

        std::deque<char> toProcess;
        auto lastTick = clock::now();
        while (true) {
            {
                std::unique_lock<std::mutex> lock{ mutex };
                if (cv.wait_for(lock, std::chrono::seconds(0), [&] { return !commands.empty(); })) {
                    std::swap(commands, toProcess);
                }
            }

            if (!toProcess.empty()) {
                for (auto&& key: toProcess) {
                    Command c;
                    switch (key) {
                    case 'u':
                        c = Command::RotateCW;
                        break;
                    case 'z':
                        c = Command::RotateCCW;
                        break;
                    case 'd':
                        c = Command::MoveDown;
                        break;
                    case 'l':
                        c = Command::MoveLeft;
                        break;
                    case 'r':
                        c = Command::MoveRight;
                        break;
                    default:
                        c = Command::None;
                        break;
                    }
                    board.ProcessCommand(c);
                }
                system("cls");
                board.Render();
                toProcess.clear();
            }

            auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - lastTick);
            if (delta.count() >= TICK_INTERVAL_MS) {
                lastTick = clock::now();
				system("cls");
				board.ProcessTick();
				board.Render();
            }
        }
    }
};

int main()
{
    srand(time(nullptr));
    GameController::Run();
}

