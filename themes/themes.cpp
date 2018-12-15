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

void themes::printTheme(string hostname, string username, string directory)
{
	switch(theme_format)
	{
		case 0:
			cout << paintText(username, color[0]) << paintText("@", color[1]) << paintText(hostname, color[2]) << " " << paintText(directory, color[3]) << paintText(" > ", color[4]) << flush;
			break;
		case 1:
			cout << paintText("> ", color[0]) << flush;
			break;
		case 2:
			{
				// Shorten the directory string to the last directory
				// in order to get a more minimal theme
				int iterator = 0;
				const char s[2] = "/";
				char* token;
				string shortenedDir;
				char directoryChar[1024];
				strcpy(directoryChar, directory.c_str());
				// Split the string and get the last directory
				token = strtok(directoryChar, s);
				while (token != NULL)
				{
					shortenedDir = token;
					token = strtok(NULL, s);
				}
				cout << paintText(username, color[0]) << paintText(" at ", color[1]) << paintText(hostname, color[2]) << " " << paintText(shortenedDir, color[3]) << paintText(" > ", color[4]) << flush;
				break;
			}

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
