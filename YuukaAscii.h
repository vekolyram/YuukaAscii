#pragma once
#ifdef _WIN32
#include <windows.h>
#include <stdlib.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

void getTerminalSize(int& cols, int& rows) {
#ifdef _WIN32
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#else
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	cols = size.ws_col;
	rows = size.ws_row;
#endif
}
void clearScreen() {
#ifdef _WIN32
	system("cls");
#else
	cout << "\033[2J\033[1;1H";
#endif
}