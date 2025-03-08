// YuukaAscii.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#include <algorithm>
#include <iostream>
#include <cmath>
#include <map>
#include <vector>
#include <sstream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "YuukaAscii.h"
int iw, ih, n, termW, termH;
/*
*/
using namespace std;
static int rgb2b(unsigned char r, unsigned char g, unsigned char b) {
	return round(max(max(r, g), b) / 25.5f);
}
int main()
{
	map<int, char> asciiMap = {};
	string asciistr = " -!~*?%#&[$";
	string size = "5", img = "yuuka";
	for (int i = 0;i <= 10;i += 1) {
		asciiMap[i] = asciistr[i];
	}
	int sizeInput = 0, imgInput = 0;
	cout << "Input img size and enter(5half,5,10,15,35,o):" << endl;
	cin >> size;
	cout << "Input yuuka img and enter(yuuka,CH0184,CH0284,NP0109):" << endl;
	cin >> img;
	string path = "./yuukas/" + size + "/" + img + size + ".png";
	unsigned char* idata = stbi_load(path.c_str(), &iw, &ih, &n, 0);
	getTerminalSize(termW, termH);
	cout << "Font height 0.6 for best.\nTry to resize your console if you used Windows Terminal and your fontsize was small" << endl;
	getchar();
	do {
		clearScreen();
		cout << "Wait for the console size to adjust to the yuuka image size;" << endl;
		cout << "Current:" << termW << "x" << termH << endl;
		cout << "Yuuka img:" << iw << "x" << ih << endl;
		getTerminalSize(termW, termH);
		Sleep(100);
	} while (termW <= iw && termH <= ih);

	unsigned bytePerPixel = n;
	vector<string> lines;
	lines.resize(ih);
	clearScreen();
	for (int y = 0;y < ih;y++)
	{
		char lastChar = ' ';
		int spaceCounter = 0;
		bool spaceRelease = false;
		stringstream ss;
		for (int x = 0;x < iw;x++)
		{
			unsigned char* pixelOffset = idata + (x + y * iw) * bytePerPixel;
			unsigned char r = pixelOffset[0];
			unsigned char g = pixelOffset[1];
			unsigned char b = pixelOffset[2];
			unsigned char a = n >= 4 ? pixelOffset[3] : 0xff;
			char c = asciiMap[rgb2b(r, g, b)];
			if (a > 128) {
				if (spaceCounter > 0) {
					for (int i = 0;i < spaceCounter;i += 1) {
						ss << ' ';
					}
					spaceCounter = 0;
				}
				ss << "\033[38;2;" << (int)r << ";" << (int)g << ";" << (int)b << "m" << c;
			}
			else {
				spaceCounter++;
				lastChar = ' ';
			}
		}
		lines[y] = ss.str();
	}
	for (auto& line : lines) {
		cout << line << endl;
	}
	free(idata);
	getchar();
	getchar();
	return 0;
}