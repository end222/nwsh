#ifndef FAVS_HPP
#define FAVS_HPP

#include <iostream>
#include <cstring>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

class themes
{
	private:
		string theme_format;
		int color1;
		int color2;

	public:
		themes();
		void printTheme();
		void changeColor(int colorNum, int value);
};
#endif
