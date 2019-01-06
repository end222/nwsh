/*
 * nwsh
 * By end222
 * File: modules/favs.cpp
 */

#include "favs.hpp"
#include <iostream>

char fav_commands[100][100];
int fav_number = 0;

using namespace std; 
void add_fav(const char* fav)
{
	strcpy(fav_commands[fav_number], fav);
	fav_number++;
}

void list_all_fav()
{
	int i = 0;
	cout << "Favorite commands: " << endl;
	cout << "------------------ " << endl;
	while (i < fav_number)
	{
		cout << i << " - "  << fav_commands[i] << endl;
		i++;
	}
}

void exec_fav(int commandNum, themes appearance, char** path)
{
	parseLine(fav_commands[commandNum], appearance, path);
}
