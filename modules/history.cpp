/*
 * nwsh
 * By end222
 * File: modules/history.cpp
 */

#include "history.hpp"
#include <iostream>
#include <fstream>

#include "../functions/exec.hpp"

hist_entry* first = new hist_entry;
hist_entry* last = new hist_entry;
char history[100][1000];
int hist_number = 0;

using namespace std; 

/*
 * Adds the command to the history
 * params: command (const char*): command to add
 */

void add_hist(const char* command)
{
	hist_entry* aux = new hist_entry;
	aux->command = command;
	aux->former = NULL;
	aux->next = first;
	first->former = aux;
	first = aux;
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
	hist_entry* hist_pointer = last;
	string home = exec("echo ~");
	home.erase(home.length()-1);
	string hist_location = home + "/.config/nwsh/history";

	// Open the file this way to erase its content
	// because it will be written again from scratch with the updated history
	file.open(hist_location, std::ofstream::out | std::ofstream::trunc);
	while(hist_pointer != NULL)
	{
		file << hist_pointer->command << endl;
		hist_pointer = hist_pointer->former;
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

	for (string line; std::getline(file, line); )
	{
		if (hist_number == 0)
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
			first->former = aux;
			first = aux;
		}
		hist_number++;
	}
}

string get_hist_command(int index)
{
	hist_entry* aux = first;
	while(index > 0)
	{
		aux = aux->next;
		index--;
	}
	return aux->command;
}
