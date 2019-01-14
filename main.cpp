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

#include "modules/favs.hpp"
#include "themes/themes.hpp"
#include "functions/parse.hpp"
#include "functions/exec.hpp"

using namespace std;

char *vars[100];
char *path[100];
themes appearance;

/*
 * Read NWSH configuration file, which is located in ~/.nwshrc
 */
void read_config()
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
		parseLine(line, appearance, path);
		config_file.getline(line, 100);
	}

	/*
	 * Read the favorite commands
	 */
	load_favorites();
}

void command_loop()
{
	char line[256];
	char buffer[256]; // To store the path of the current directory

	string system_name = exec("hostname");
	string user_name = exec("whoami");
	system_name.erase(system_name.length()-1); // Remove end of line from the string
	user_name.erase(user_name.length()-1);

	// Close the shell when exitShell() equals true
	while (exitShell() == false)
	{
		appearance.printTheme(system_name, user_name, buffer);
		cin.getline(line,256);
		parseLine(line, appearance, path);
	}
}

int main(int argc, char *argv[])
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
		read_config();
		command_loop();
	}
}
