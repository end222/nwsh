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
#include <cmath>

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
	int h_entry = -1;

	string system_name = exec("hostname");
	string user_name = exec("whoami");
	string directory = exec("pwd");
	string hcommand;
	
	// Remove end of line from the string
	system_name.erase(system_name.length()-1); 
	user_name.erase(user_name.length()-1);
	directory.erase(directory.length()-1);

	bool backslash = false;
	bool lastChar;
	bool arrow;
	// Close the shell when exitShell() equals true
	while (exitShell() == false)
	{
		// Read directory again beacuse it could've changed after executing a 'cd'
		string directory = exec("pwd");
		directory.erase(directory.length()-1);

		if (!backslash) appearance.printTheme(system_name, user_name, directory);
		
		i_line = 0;
		lastChar = true; // Used to stop deleting when the last char of the shell is reached
		c = ' '; // Avoid infinite loop because c is always '\n' after the first iteration
		while( c != '\n')
		{
			c = gchar();
			switch(c)
			{
				case 27:
					// Do not print when an arrow is selected
					ch = '\0';
					// This char does not give any extra information
					c = gchar();
					// This one tells the direction of the arrow pressed
					c = gchar();
					switch(c)
					{
						case 65:
							// Up
							while (i_line != 0)
							{
								cout << "\b \b" << flush;
								i_line--;
							}
							h_entry++;
							if (h_entry >= 0)
							{
								if(!check_history_index(h_entry))
								{
									h_entry--;
								}
								hcommand = get_hist_command(h_entry);
								cout << hcommand << flush;
								strcpy(line, hcommand.c_str());
								i_line = hcommand.length();
							}

							if (h_entry < -1)
							{
								int index = abs(h_entry+2);
								hcommand = get_fav_command(index);
								cout << hcommand << flush;
								strcpy(line, hcommand.c_str());
								i_line = hcommand.length();
							}
							break;
						case 66:
							// Down
							while (i_line != 0)
							{
								cout << "\b \b" << flush;
								i_line--;
							}
							// h_entry is always decreased, it will be used
							// for indexing the history from 0 to n
							// and for indexing the favorites from -2 to -n
							// -1 is the actual command that is being written
							h_entry--;
							if (h_entry > -1)
							{
								hcommand = get_hist_command(h_entry);
								cout << hcommand << flush;
								strcpy(line, hcommand.c_str());
								i_line = hcommand.length();
							}
							else if (h_entry < -1)
							{
								int index = abs(h_entry+2);
								if(!check_fav_index(index))
								{
									h_entry++;
									index = abs(h_entry+2);
								}
								hcommand = get_fav_command(index);
								cout << hcommand << flush;
								strcpy(line, hcommand.c_str());
								i_line = hcommand.length();
							}

							break;
						case 67:
							// Right
							break;
						case 68:
							// Left
							break;
						default:
							break;
					}
					break;
				case 127:
					// Backspace is detected
					if(i_line == 0)
					{
						lastChar = true;
					}
					if (!lastChar)
					{
						i_line--; // Remove the last character
						cout << "\b " << flush; // "\b \b" is equal to the normal behaviour
						// of the backspace
						ch = '\b';
					}
					break;
				case '\n':
					h_entry = -1;
					ch = '\0';
					cout << endl;
					line[i_line] = '\0';
					break;
				default:
					lastChar = false;
					ch = c;                 
					line[i_line] = ch;
					i_line++;
					break;
			}
			if (!lastChar)
			{
				cout << char(ch) << flush;
			}
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
		if(!backslash && strcmp(line,"") != 0)
		{
			add_hist(line); // Add command to the history
			parseLine(command, appearance, env);
		}
		if(strcmp(line,"") == 0)
		{
			cout << endl;
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
