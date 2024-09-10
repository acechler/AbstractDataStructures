#include <iostream>
#include <windows.h>
#include <chrono>
#include <thread>
#include <conio.h>

const int FRAME_RATE = 120;
const int FRAME_DURATION = 1000 / FRAME_RATE;
const int MIN_POSITION = 0;
const int STEP = 1;
const int PADDLE_HEIGHT = 4;
const int PADDLE_WIDTH = 1;

void setCursorPosition(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clearConsole() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    DWORD cellCount;
    COORD homeCoords = { MIN_POSITION, MIN_POSITION };

    if (hConsole == INVALID_HANDLE_VALUE) return;

    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    if (!FillConsoleOutputCharacter(hConsole, (TCHAR)' ', cellCount, homeCoords, &count)) return;
    if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, homeCoords, &count)) return;

    SetConsoleCursorPosition(hConsole, homeCoords);
}

void setCursorVisibility(bool isVisible) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    if (!GetConsoleCursorInfo(hConsole, &cursorInfo)) return;
    cursorInfo.bVisible = isVisible;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void drawPaddle(int x, int y, int height) {
    for (int i = 0; i < height; ++i) {
        setCursorPosition(x, y + i);
        std::cout << '|';
    }
}

void erasePaddle(int x, int y, int height) {
    for (int i = 0; i < height; ++i) {
        setCursorPosition(x, y + i);
        std::cout << ' ';
    }
}

int main() {
    int width, height;
    int ballX, ballY, ballDirX = STEP, ballDirY = STEP;
    int paddleLeftY, paddleRightY;
    int scoreLeft = 0, scoreRight = 0;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        std::cerr << "Error: Failed to retrieve console screen buffer info." << std::endl;
        return 1;
    }

    width = csbi.dwSize.X;
    height = csbi.dwSize.Y;

    ballX = width / 2;
    ballY = height / 2;
    paddleLeftY = height / 2 - PADDLE_HEIGHT / 2;
    paddleRightY = height / 2 - PADDLE_HEIGHT / 2;

    setCursorVisibility(false);

    while (true) {
        auto frameStart = std::chrono::high_resolution_clock::now();

        // Handle paddle movement
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 'w' && paddleLeftY > MIN_POSITION) {
                erasePaddle(2, paddleLeftY, PADDLE_HEIGHT);
                paddleLeftY -= STEP;
            }
            if (ch == 's' && paddleLeftY < height - PADDLE_HEIGHT) {
                erasePaddle(2, paddleLeftY, PADDLE_HEIGHT);
                paddleLeftY += STEP;
            }
            if (ch == 'o' && paddleRightY > MIN_POSITION) {
                erasePaddle(width - 3, paddleRightY, PADDLE_HEIGHT);
                paddleRightY -= STEP;
            }
            if (ch == 'l' && paddleRightY < height - PADDLE_HEIGHT) {
                erasePaddle(width - 3, paddleRightY, PADDLE_HEIGHT);
                paddleRightY += STEP;
            }
        }

        clearConsole();

        // Draw paddles
        drawPaddle(2, paddleLeftY, PADDLE_HEIGHT);
        drawPaddle(width - 3, paddleRightY, PADDLE_HEIGHT);

        // Move the ball
        ballX += ballDirX;
        ballY += ballDirY;

        // Ball collision with top and bottom walls
        if (ballY <= MIN_POSITION || ballY >= height - STEP) {
            ballDirY *= -1;
        }

        // Ball collision with paddles
        if ((ballX <= 3 && ballY >= paddleLeftY && ballY < paddleLeftY + PADDLE_HEIGHT) ||
            (ballX >= width - 4 && ballY >= paddleRightY && ballY < paddleRightY + PADDLE_HEIGHT)) {
            ballDirX *= -1;
        }

        // Ball goes out of bounds (left or right)
        if (ballX <= MIN_POSITION) {
            scoreRight++;
            ballX = width / 2;
            ballY = height / 2;
        }
        else if (ballX >= width - STEP) {
            scoreLeft++;
            ballX = width / 2;
            ballY = height / 2;
        }

        // Draw the ball
        setCursorPosition(ballX, ballY);
        std::cout << 'O';

        // Display the scores
        setCursorPosition(width / 2 - 10, 1);
        std::cout << "Player 1: " << scoreLeft;

        setCursorPosition(width / 2 + 5, 1);
        std::cout << "Player 2: " << scoreRight;

        auto frameEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = frameEnd - frameStart;
        auto sleepDuration = std::chrono::milliseconds(FRAME_DURATION) - elapsed;

        if (sleepDuration.count() > 0) {
            std::this_thread::sleep_for(sleepDuration);
        }
    }

    return 0;
}
