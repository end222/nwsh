#ifndef THEMES_HPP
#define THEMES_HPP

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
		int theme_format;
		int color[10] = {15,15,15,15,15};

	public:
		themes();
		void printTheme(string hostname, string username, string directory);
		void setTheme(int themeNum);
		void changeColor(int colorNum, int value);
};
#endif
