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

using namespace std;

char *vars[100];
char *path[100];
themes appearance;

string exec(const char* cmd) {
	array<char, 128> buffer;
	string result;
	shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);	
	if (!pipe) throw runtime_error("popen() failed!");
	while (!feof(pipe.get())) 
	{
		if (fgets(buffer.data(), 128, pipe.get()) != nullptr) result += buffer.data();
	}
	return result;
}


/*
 * Read NWSH configuration file, which is located in ~/.nwshrc
 */
void read_config()
{
	char *args[10];
	char line[100];
	int path_dirs = 0;
	ifstream config_file;
	string home = exec("echo ~");
	home.erase(home.length()-1);
	string config_location = home + "/.nwshrc";

	config_file.open(config_location);
	config_file.getline(line, 100);

	// TODO: remove, just for debug
	cout << "Reading config files..." << endl;

	/*
	 * Read config file, line to line
	 * and apply configurations
	 */
	while (!config_file.eof())
	{
		// TODO: remove, just for debug
		cout << line << endl;
		int i = 0;
		const char s[2] = " ";
		char* token;
		token = strtok(line, s);
		while (token != NULL)
		{
			args[i] = token;
			token = strtok(NULL, s);
			i++;
		}
		args[i] = NULL;
		// Add a directory to the path
		if (!strcmp(args[0], "addtopath"))
		{
			path[path_dirs] = args[1];
			path_dirs++;
		}
		// Change the theme of the shell
		else if(!strcmp(args[0], "theme"))
		{
			appearance.setTheme(atoi(args[1]));
		}
		else if(!strcmp(args[0], "color"))
		{
			appearance.changeColor(atoi(args[1]), atoi(args[2]));
		}
		config_file.getline(line, 100);
	}
	// TODO: remove, just for debug
	cout << "Finished reading config files..." << endl;
}

void command_loop()
{
	bool exit = false;
	char line[256];
	char buffer[256];

	string system_name = exec("hostname");
	string user_name = exec("whoami");
	system_name.erase(system_name.length()-1); // Remove end of line from the string
	user_name.erase(user_name.length()-1);

	while (exit == false)
	{
		getcwd(buffer, sizeof(buffer));
		appearance.printTheme(system_name, user_name, buffer);
		cin.getline(line,256);
		if (!strcmp(line,"exit"))
		{
			exit = true;
		}
		else
		{
			char *args[10];
			int i = 0;
			const char s[2] = " ";
			char* token;
			token = strtok(line, s);
			while (token != NULL)
			{
				args[i] = token;
				token = strtok(NULL, s);
				i++;
			}
			args[i] = NULL;
			if(!strcmp(args[0], "cd"))
			{
				chdir(args[1]);
			}
			else
			{
				int status;
				pid_t pid, wait_pid;
				if ((pid = fork()) == 0) // Child
				{
					execvpe(args[0],args,path);
				}
				else // Parent
				{
					do {
						wait_pid = waitpid(pid, &status, WUNTRACED);
					} while (!WIFEXITED(status) && !WIFSIGNALED(status));
				}
			}
		}
	}
}

int main(int argc, char *argv[])
{
	if (argc > 1)
	{
		if (!strcmp(argv[1],"-h") || !strcmp(argv[1],"--help"))
		{
			cout << "Help page" << endl;
		}
		else if (!strcmp(argv[1], "-v") || !strcmp(argv[1], "--version"))
		{
			cout << "Nwsh Alpha 0.1a" << endl;
			cout << "By end222" << endl;
		}
	}
	else
	{
		read_config();
		command_loop();
	}
}
