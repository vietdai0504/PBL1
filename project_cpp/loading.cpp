#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "loading_bar.cpp"
#include <thread>

using namespace std;

void ResetColor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // M?c d?nh là màu n?n den (0) và ch? tr?ng (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void loading() {
	Nocursortype();
	while (true) {
    	std::vector<std::string> lines = ReadFile("loading1.txt");
    	DisplayCenteredText(lines);
    	Sleep(1000);
    	system("cls");
    	lines = ReadFile("loading2.txt");
    	DisplayCenteredText(lines);
    	Sleep(1000);
		system("cls");
    	lines = ReadFile("loading3.txt");
    	DisplayCenteredText(lines);
    	Sleep(1000);
    	system("cls");
    	break;
	}
	vector<string> lines = ReadFile("welcomev4.txt");
	DisplayCenteredText(lines);
	Sleep(2000);
//	system("cls");
	loadingbar();
	ResetColor();
	system("cls");
	Sleep(500);
}

void closing() {
	Nocursortype();
	while (true) {
    	std::vector<std::string> lines = ReadFile("end1.txt");
    	DisplayCenteredText(lines);
    	Sleep(1200);
    	system("cls");
    	lines = ReadFile("end2.txt");
    	DisplayCenteredText(lines);
    	Sleep(1200);
		system("cls");
    	lines = ReadFile("end3.txt");
    	DisplayCenteredText(lines);
    	Sleep(1200);
    	system("cls");
    	lines = ReadFile("end4.txt");
    	DisplayCenteredText(lines);
    	Sleep(1200);
    	system("cls");
	}
}
//int main() {
//	closing();
//}
