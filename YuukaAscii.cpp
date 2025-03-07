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
using namespace std;
static int rgb2b(unsigned char r, unsigned char g, unsigned char b) {
	return round(max(max(r, g), b) / 25.5f);
}
int main()
{
	printf("Hello World!\n");
	map<int, char> asciiMap = {};
	string asciistr = " -!~*?%#&[$";
	for (int i = 0;i <= 10;i += 1) {
		asciiMap[i] = asciistr[i];
		cout << asciiMap[i] << endl;
	}
	unsigned char* idata = stbi_load("./yuukaquarter.png", &iw, &ih, &n, 0);
	getTerminalSize(termW, termH);
	while (termW <= iw && termH <= ih) {
		cout << "\033[2J\033[1;1H";
		cout << "waiting for size" << termW << "x" << termH << endl;
		cout << "waiting for size" << iw << "x" << ih << endl;
		getTerminalSize(termW, termH);
		Sleep(1000);
	}
	unsigned bytePerPixel = n;
	std::vector<std::string> lines;
	lines.resize(ih);

	for (int y = 0;y < ih;y++)
	{
		stringstream ss;
		for (int x = 0;x < iw;x++)
		{
			unsigned char* pixelOffset = idata + (x + y * iw) * bytePerPixel;
			unsigned char r = pixelOffset[0];
			unsigned char g = pixelOffset[1];
			unsigned char b = pixelOffset[2];
			unsigned char a = n >= 4 ? pixelOffset[3] : 0xff;
			if (a > 128) {
				ss << "\033[38;2;" << (int)r << ";" << (int)g << ";" << (int)b << "m" << asciiMap[(int)rgb2b(r, g, b)];
			}
			else {
				ss << " ";
			}
		}
		lines[y] = ss.str();
		cout << ss.str() << endl;
	}
	for (auto& line : lines) {
		//cout << line << endl;
	}
	free(idata);
	return 0;
}