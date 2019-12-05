/*
 * nwsh
 * By end222
 * File: modules/favs.cpp
 */

#include "favs.hpp"
#include <iostream>
#include <fstream>

#include "../functions/exec.hpp"

fav_entry* firstf = new fav_entry;
fav_entry* lastf = new fav_entry;
char fav_commands[100][1000];
int fav_number = 0;

using namespace std; 

/*
 * Adds the command fav as favorite command
 * params: fav (const char*): command to add
 */

void add_fav(const char* fav)
{	
	fav_entry* aux = new fav_entry;
	aux->command = fav;

	if(fav_number == 0)
	{
		firstf = aux;
		lastf = aux;
		aux->next = NULL;
		aux->former = NULL;
	}
	else
	{
		aux->former = lastf;
		aux->next = NULL;
		lastf->next = aux;
		lastf = aux;
	}
	fav_number++;
	cout << fav_number << endl;
	cout << firstf->command << endl;
	write_favorites();
}


/*
 * Removes a favorite command from the list
 * params: number (int): position of the command to be removed
 *
 * Restrictions:
 * 0 <= number <= fav_number - 1
 */
void remove_fav(int number)
{
	if(number < 0 || number >= fav_number)
	{
		cout << "There is no command at position: " << number << endl;
	}
	else
	{
		cout << number <<endl;
		fav_entry* aux = firstf;
		if(number == 0)
		{
			firstf = firstf->next;
			firstf->former = NULL;
		}
		else if(number == fav_number-1)
		{
			lastf = lastf->former;
			lastf->next = NULL;
		}
		else
		{
			// Using 1 instead of 0 to stop
			// on the one before the one we
			// want to remove
			while(number > 1)
			{
				aux = aux->next;
				number--;
			}
			aux->next->next->former = aux;
			aux->next = aux->next->next;
		}
		fav_number--;	
	}
}


/*
 * Lists all the commands in the favorites list
 */
void list_all_fav()
{
	fav_entry* aux;
	aux = firstf;
	int i = 0;
	cout << "Favorite commands: " << endl;
	cout << "------------------ " << endl;
	while (aux != NULL)
	{
		cout << i << " - "  << aux->command << endl;
		aux = aux->next;
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
		fav_entry* aux;
		aux = firstf;
		while(commandNum > 0)
		{
			aux = aux->next;
			commandNum--;
		}

		char command[256];
		strcpy(command, aux->command.c_str());
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
	fav_entry* aux;
	aux = firstf;
	while(aux != NULL)
	{
		file << aux->command << endl;
		aux = aux->next;
	}
}

/*
 * Loads the favorite commands from a file located 
 * in ~/.config/nwsh/favorites.conf
 */

void load_favorites()
{
	fav_entry* aux;
	fstream file;
	string home = exec("echo ~");
	home.erase(home.length()-1);
	string favs_location = home + "/.config/nwsh/favorites.conf";
	file.open(favs_location);
	for (string line; std::getline(file, line); )
	{
		if (fav_number == 0)
		{
			firstf->command = line;
			firstf->next = NULL;
			firstf->former = NULL;
			lastf->command = line;
			lastf->next = NULL;
			lastf->former = NULL;
		}
		else if (firstf->next == NULL)
		{
			lastf->command = line;
			lastf->former = firstf;
			firstf->next = lastf;
		}
		else
		{
			aux = new fav_entry;
			aux->command = line;
			aux->former = lastf;
			aux->next = NULL;
			lastf->next = aux;
			lastf = aux;
		}
		fav_number++;
	}
}

string get_fav_command(int index)
{
	fav_entry* aux = firstf;
	while(index > 0)
	{
		aux = aux->next;
		index--;
	}
	return aux->command;
}

bool check_fav_index(int index)
{
	return (index >= 0 && index <= (fav_number - 1));
}
