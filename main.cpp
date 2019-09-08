/*
 * nwsh
 * By end222
 * File: main.cpp
 */

#include <iostream>
#include <memory>
#include <array>
#include <fstream>
#include <cstring>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <termios.h>

#include "modules/history.hpp"
#include "modules/favs.hpp"
#include "themes/themes.hpp"
#include "functions/parse.hpp"
#include "functions/exec.hpp"

using namespace std;

themes appearance;

/*
 * Get a character and return its ascii code
 */
int gchar()
{
	struct termios oldt,newt;
	int ch;
	tcgetattr( STDIN_FILENO, &oldt );
	newt = oldt;
	newt.c_lflag &= ~( ICANON | ECHO );
	tcsetattr( STDIN_FILENO, TCSANOW, &newt );
	ch = getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
	return ch;
}

/*
 * Removes a character of a string, putting a blank space in its place
 * Used in backslash treatment
 */
void eraseChar(char *array, char charToRemove)
{
	int i = 0;
	while(array[i] != '\0')
	{
		if(array[i] == charToRemove)
		{
			array[i] = ' ';
		}
		i++;
	}
}

/*
 * Read NWSH configuration file, which is located in ~/.nwshrc
 * and other config files such as favorite commands (~/.config/nwsh/favorites.conf)
 */
void read_config(char **env)
{
	char *args[10];
	char line[100];

	ifstream config_file;
	string home = exec("echo ~");
	home.erase(home.length()-1);
	string config_location = home + "/.nwshrc";
	config_file.open(config_location);
	config_file.getline(line, 100);

	/*
	 * Read config file, line to line
	 * and apply configurations
	 */
	while (!config_file.eof())
	{
		parseLine(line, appearance, env);
		config_file.getline(line, 100);
	}

	/*
	 * Read the favorite commands
	 */
	load_favorites();
	load_hist();
}

/*
 * Execute the main command loop
 * Stop whenever an "exit" command is executed, such as 
 * :q, exit or bye
 */
void command_loop(char **env)
{
	char line[256];
	char command[256]; // Line that will be executed, important for commands with backslashes
	char buffer[256]; // To store the path of the current directory

	// Variables used in text input
	int ch,c;
	int i_line; // Iterate over line to insert the characters

	string system_name = exec("hostname");
	string user_name = exec("whoami");
	string directory = exec("pwd");
	
	// Remove end of line from the string
	system_name.erase(system_name.length()-1); 
	user_name.erase(user_name.length()-1);
	directory.erase(directory.length()-1);

	bool backslash = false;
	// Close the shell when exitShell() equals true
	while (exitShell() == false)
	{
		// Read directory again beacuse it could've changed after executing a 'cd'
		string directory = exec("pwd");
		directory.erase(directory.length()-1);

		if (!backslash) appearance.printTheme(system_name, user_name, directory);
		
		// Total rewrite of text input in order to detect arrow keys
		// Old version is down here, commented
		/*
		 * cin.getline(line,256);
		 */

		i_line = 0;
		c = ' '; // Avoid infinite loop because c is always '\n' after the first iteration
		while( c != '\n')
		{
			switch( c = gchar() )
			{
				case 127:
					// Backspace is detected
					i_line--; // Remove the last character
					cout << "\b " << flush; // "\b \b" is equal to the normal behaviour
								// of the backspace
					ch = '\b';
					break;
				case '\n':
					ch = c;
					line[i_line] = '\0';
					break;
				default:
					ch = c;                 
					line[i_line] = ch;
					i_line++;
					break;
			}
			cout << char(ch) << flush;
		}
		if(!backslash)
		{
			strcpy(command, line);
		}
		else
		{
			strcat(command, line);
		}
		if(strchr(line, '\\') != NULL)
		{
			// If a backslash is detected, remove it and put a black space in its place
			eraseChar(command, '\\');	
			backslash = true;
		}
		else
		{
			backslash = false;
		}
		if(!backslash)
		{
			add_hist(line); // Add command to the history
			parseLine(command, appearance, env);
		}
	}
}

int main(int argc, char *argv[], char **envp)
{
	if (argc > 1)
	{
		if (!strcmp(argv[1],"-h") || !strcmp(argv[1],"--help"))
		{
			cout << "nwsh -v | --version: show information about the version of Nwsh" << endl;
			cout << "nwsh -h | --help: show this help page" << endl;
		}
		else if (!strcmp(argv[1], "-v") || !strcmp(argv[1], "--version"))
		{
			cout << "Nwsh Alpha 0.1b" << endl;
			cout << "By end222" << endl;
		}
	}
	else
	{
		read_config(envp);
		command_loop(envp);
	}
}
