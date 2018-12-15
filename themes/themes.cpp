/*
 * nwsh
 * By: end222
 * File: themes/themes.cpp
 */

#include "themes.hpp"
#include "../modules/colors.hpp"

using namespace std;

themes::themes()
{
	theme_format = 0;
}

void themes::printTheme(string hostname, string username)
{
	switch(theme_format)
	{
		case 0:
			cout << paintText(username, color[0]) << paintText("@", color[1]) << paintText(hostname, color[2]) << paintText(" > ", color[3]) << flush;
			break;
		case 1:
			cout << paintText("> ", color[0]) << flush;
			break;
		case 2:
			cout << paintText(username, color[0]) << paintText(" at ", color[1]) << paintText(hostname, color[2]) << paintText(" > ", color[3]) << flush;
			break;
		default:
			cout << "No theme format detected > " << flush;
	}
}

void themes::setTheme(int themeNumber)
{
	theme_format = themeNumber;
}

void themes::changeColor(int colorNum, int value)
{
	color[colorNum] = value;
}
