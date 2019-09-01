/*
 * nwsh
 * By end222
 * File: modules/favs.cpp
 */

#include "favs.hpp"
#include <iostream>
#include <fstream>

#include "../functions/exec.hpp"

char fav_commands[100][1000];
int fav_number = 0;

using namespace std; 

/*
 * Adds the command fav as favorite command
 * params: fav (const char*): command to add
 */

void add_fav(const char* fav)
{
	strcpy(fav_commands[fav_number], fav);
	fav_number++;
	write_favorites();
}


/*
 * Removes a favorite command from the list
 * params: number (int): position of the command to be removed
 *
 * Restrictions:
 * 0 =< number <= fav_number - 1
 */
void remove_fav(int number)
{
	if(number < 0 || number >= fav_number)
	{
		cout << "There is no command at position: " << number << endl;
	}
	else
	{
		while(number < fav_number)
		{
			strcpy(fav_commands[number-1], fav_commands[number]);
			number++;
		}
		fav_number--;
	}
}


/*
 * Lists all the commands in the favorites list
 */
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


/*
 * Executes a favorite command
 * params: commandNum (int): position of the command
 * appearance (themes): themes instance needed if the theme is going to be changed
 * envp (char**)
 *
 * Restrictions:
 * 0 <= commandNum <= fav_number - 1
 */
void exec_fav(int commandNum, themes appearance, char** envp)
{
	if(commandNum < 0 || commandNum >= fav_number)
	{
		cout << "There is no command at position: " << commandNum << endl;
	}
	else
	{
		char command[256];
		strcpy(command, fav_commands[commandNum]);
		parseLine(command, appearance, envp);
	}
}

/*
 * Writes the favorite command list to a config file
 * located in ~/.config/nwsh/favorites.conf
 */

void write_favorites()
{
	fstream file;
	string home = exec("echo ~");
	home.erase(home.length()-1);
	string favs_location = home + "/.config/nwsh/favorites.conf";
	// Open the file this way to erase its content
	// because it will be written again from scratch with the updated favorites
	file.open(favs_location, std::ofstream::out | std::ofstream::trunc);
	int i = 0;
	while(i < fav_number)
	{
		file << fav_commands[i] << endl;
		i++;
	}
}

/*
 * Loads the favorite commands from a file located 
 * in ~/.config/nwsh/favorites.conf
 */

void load_favorites()
{
	fstream file;
	string home = exec("echo ~");
	home.erase(home.length()-1);
	string favs_location = home + "/.config/nwsh/favorites.conf";
	file.open(favs_location);
	int i = 0;
	for (string line; std::getline(file, line); )
	{
		strcpy(fav_commands[i], line.c_str());
		i++;
	}
	fav_number = i;
}
