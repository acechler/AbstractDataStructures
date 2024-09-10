# Art


## Bouncing Ball
```cpp


#include <iostream>
#include "Bag.hpp"
#include "RandomBag.hpp"
#include "Stack.hpp"
#include <windows.h>
#include <chrono>
#include <thread>
// Function to set cursor position in the console
void setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Function to set the color of the text in the console
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void bagTest() {
    Bag<int> myBag(10);

    // Add elements to the bag
    myBag.add(5);
    myBag.add(10);
    myBag.add(5);

    std::cout << "Current size: " << myBag.getCurrentSize() << std::endl;
    std::cout << "Is empty: " << std::boolalpha << myBag.isEmpty() << std::endl;
    std::cout << "Frequency of 5: " << myBag.getFrequencyOf(5) << std::endl;
    std::cout << "Contains 10: " << std::boolalpha << myBag.contains(10) << std::endl;

    // Remove an element
    myBag.remove(5);
    std::cout << "Removed one occurrence of 5" << std::endl;
    std::cout << "Frequency of 5: " << myBag.getFrequencyOf(5) << std::endl;

    // Clear the bag
    myBag.clear();
    std::cout << "Bag cleared. Current size: " << myBag.getCurrentSize() << std::endl;
}


void stackTest() {
    Stack<int> myStack;

    myStack.push(1);
    myStack.push(2);
    myStack.push(3);

    std::cout << "Top element: " << *myStack.peek() << std::endl;

    std::cout << "Popped element: " << *myStack.pop() << std::endl;
    std::cout << "Popped element: " << *myStack.pop() << std::endl;

    std::cout << "Top element: " << *myStack.peek() << std::endl;

    myStack.empty();
    std::cout << "Stack emptied." << std::endl;

    try {
        std::cout << "Top element: " << *myStack.peek() << std::endl;
    }
    catch (const std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    }
}


void showAscii() {
    for (int i = 33; i <= 225; i++) {
        std::cout << i << ": " << char(i) << "\t";
        if (i % 8 == 0) {
            std::cout << std::endl;
        }
    }
}



// Function to clear the console
void clearConsole() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    DWORD cellCount;
    COORD homeCoords = { 0, 0 };

    if (hConsole == INVALID_HANDLE_VALUE) return;

    // Get the number of cells in the current buffer
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    // Fill the entire buffer with spaces
    if (!FillConsoleOutputCharacter(hConsole, (TCHAR)' ', cellCount, homeCoords, &count)) return;

    // Fill the entire buffer with the current colors and attributes
    if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, homeCoords, &count)) return;

    // Move the cursor to the home position
    SetConsoleCursorPosition(hConsole, homeCoords);
}

// Function to hide the console cursor
void hideCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE; // Set the cursor visibility to false
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

// Function to show the console cursor
void showCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = TRUE; // Set the cursor visibility to true
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}
int main() {
    

    const int frameRate = 120; // 60 FPS
    const int frameDuration = 1000 / frameRate; // Duration of each frame in milliseconds

    int x = 0, y = 0;
    int xDirection = 1, yDirection = 1;
    const int width = 80, height = 25; // Console dimensions

    hideCursor();
    while (true) {
        auto frameStart = std::chrono::high_resolution_clock::now();

        // Clear the console
        clearConsole();

        // Update the position
        x += xDirection;
        y += yDirection;

        // Check for collision with console edges
        if (x <= 0 || x >= width - 1) xDirection *= -1;
        if (y <= 0 || y >= height - 1) yDirection *= -1;

        // Draw the ball
        setCursorPosition(x, y);
        std::cout << 'O';

        // Calculate the time taken for the frame
        auto frameEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = frameEnd - frameStart;

        // Sleep for the remaining time to maintain the frame rate
        std::this_thread::sleep_for(std::chrono::milliseconds(frameDuration) - elapsed);
    }

    return 0;
}




```

## Spinner

```cpp
#include <iostream>
#include <windows.h>
#include <chrono>
#include <thread>

// Function to set cursor position in the console
void setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Function to clear the console
void clearConsole() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    DWORD cellCount;
    COORD homeCoords = { 0, 0 };

    if (hConsole == INVALID_HANDLE_VALUE) return;

    // Get the number of cells in the current buffer
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    // Fill the entire buffer with spaces
    if (!FillConsoleOutputCharacter(hConsole, (TCHAR)' ', cellCount, homeCoords, &count)) return;

    // Fill the entire buffer with the current colors and attributes
    if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, homeCoords, &count)) return;

    // Move the cursor to the home position
    SetConsoleCursorPosition(hConsole, homeCoords);
}

// Function to hide the console cursor
void hideCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE; // Set the cursor visibility to false
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

// Function to show the console cursor
void showCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = TRUE; // Set the cursor visibility to true
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void loadingSpinner() {
    const char spinnerChars[] = { '|', '/', '-', '\\' };
    const int spinnerLength = sizeof(spinnerChars) / sizeof(spinnerChars[0]);
    const int frameRate = 10; // 10 FPS
    const int frameDuration = 1000 / frameRate; // Duration of each frame in milliseconds

    hideCursor();
    for (int i = 0; i < 100; ++i) { // Run the spinner for 100 frames
        auto frameStart = std::chrono::high_resolution_clock::now();

        // Draw the spinner
        setCursorPosition(0, 0);
        std::cout << spinnerChars[i % spinnerLength] << std::flush;

        // Calculate the time taken for the frame
        auto frameEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = frameEnd - frameStart;

        // Sleep for the remaining time to maintain the frame rate
        std::this_thread::sleep_for(std::chrono::milliseconds(frameDuration) - elapsed);
    }
    showCursor();
}

int main() {
    std::cout << "Loading... ";
    loadingSpinner();
    std::cout << "Done!" << std::endl;

    return 0;
}
```