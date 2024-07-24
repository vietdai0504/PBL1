#include <iostream>
#include <windows.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
using namespace std;

void gotoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

std::vector<std::string> ReadFile(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::string> lines;
    std::string line;

    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    return lines;
}

COORD GetConsoleSize() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    COORD size;
    size.X = columns;
    size.Y = rows;
    return size;
}

void DisplayCenteredText(const std::vector<std::string>& lines) {
    COORD consoleSize = GetConsoleSize();
    int totalLines = lines.size();
    int startY = (consoleSize.Y - totalLines) / 2;

    for (int i = 0; i < totalLines; ++i) {
        int startX = (consoleSize.X - lines[i].length()) / 2;
        gotoXY(startX + 1, startY + i - 4);
        std::cout << lines[i];
    }
}

void Nocursortype() {
    CONSOLE_CURSOR_INFO Info;
    Info.bVisible = FALSE;
    Info.dwSize = 20;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

int randomnum() {
	return rand()%18 + 1;
}

void SetColor(int color, int mode) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    WORD attributes = csbi.wAttributes;
    attributes &= 0xFFF0; // Xóa các bit c?a màu ch?
    attributes |= color;  // Thi?t l?p màu ch? m?i
    SetConsoleTextAttribute(hConsole, attributes);
}

void SetBackgroundColor(int colorIndex, int mode) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    WORD attributes = csbi.wAttributes;
    attributes &= 0xFF0F;
    attributes |= (colorIndex << 4);
    SetConsoleTextAttribute(hConsole, attributes);
}
void loadingbar() {
	Nocursortype();
	gotoXY(17,20);
	int sum = 0;
	srand(time(0));
	while (true) {
		int c = randomnum();
		SetColor(3,0);
		SetBackgroundColor(3,0);
		for (int i=0;i<c;i++) {
			cout<<(char) 196;
		}
		Sleep(1000);
		sum += c;
		if (sum >= 78)
			break;
	}
}
