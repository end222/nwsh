/*
 * nwsh
 * By end222
 * File: modules/favs.cpp
 */

#include "favs.hpp"
#include <iostream>

char* fav_commands[100];
int fav_number = 0;

using namespace std; 
void add_fav(char* fav)
{
	fav_commands[fav_number] = fav;
	fav_number++;
}

void list_all_fav()
{
	int i = 0;
	while (i < fav_number)
	{
		cout << i << " - "  << fav_commands[i] << endl;
		i++;
	}
}
