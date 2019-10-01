/*
 * nwsh
 * By end222
 * File: modules/history.cpp
 */

#include "history.hpp"
#include <iostream>
#include <fstream>

#include "../functions/exec.hpp"

hist_entry* first = NULL;
hist_entry* last = NULL;
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
	hist_entry* aux;
	aux = last;
	int i = 0;
	cout << "History: " << endl;
	cout << "-------- " << endl;
	while (aux != NULL)
	{
		cout << i << " - "  << aux->command << endl;
		aux = aux->former;
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
	hist_entry* aux;
	fstream file;
	string home = exec("echo ~");
	string line;
	home.erase(home.length()-1);
	string hist_location = home + "/.config/nwsh/history";
	file.open(hist_location);

	int i = 0;
	for (string line; std::getline(file, line); )
	{
		if (first == NULL)
		{
			first->command = line;
			first->next = NULL;
			first->former = NULL;
			last->command = line;
			last->next = NULL;
			last->former = NULL;
		}
		else if (first->next == NULL)
		{
			first->command = line;
			first->next = last;
			last->former = first;
		}
		else
		{
			aux = new hist_entry;
			aux->command = line;
			aux->next = first;
			aux->former = NULL;
			first = aux;
		}
		strcpy(history[i], line.c_str());
		i++;
	}
	hist_number = i;
}
