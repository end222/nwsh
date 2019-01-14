/*
 * nwsh
 * By end222
 * File: modules/history.cpp
 */

#include "history.hpp"
#include <iostream>
#include <fstream>

#include "../functions/exec.hpp"

char history[100][1000];
int hist_number = 0;

using namespace std; 

/*
 * Adds the command to the history
 * params: command (const char*): command to add
 */

void add_hist(const char* command)
{
	strcpy(history[hist_number], command);
	hist_number++;
	write_hist();
}


/*
 * Lists all the commands in the history
 */
void list_all_hist()
{
	int i = 0;
	cout << "History: " << endl;
	cout << "-------- " << endl;
	while (i < hist_number)
	{
		cout << i << " - "  << history[i] << endl;
		i++;
	}
}


/*
 * Updates the file where the history is, which is
 * located in ~/.config/nwsh/history
 */

void write_hist()
{
	fstream file;
	string home = exec("echo ~");
	home.erase(home.length()-1);
	string hist_location = home + "/.config/nwsh/history";
	// Open the file this way to erase its content
	// because it will be written again from scratch with the updated history
	file.open(hist_location, std::ofstream::out | std::ofstream::trunc);
	int i = 0;
	while(i < hist_number)
	{
		file << history[i] << endl;
		i++;
	}
}

/*
 * Loads the favorite commands from a file located 
 * in ~/.config/nwsh/favorites.conf
 */

void load_hist()
{
	fstream file;
	string home = exec("echo ~");
	home.erase(home.length()-1);
	string hist_location = home + "/.config/nwsh/history";
	file.open(hist_location);
	int i = 0;
	for (string line; std::getline(file, line); )
	{
		strcpy(history[i], line.c_str());
		i++;
	}
	hist_number = i;
}
