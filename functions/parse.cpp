#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>

#include "parse.hpp"
#include "../themes/themes.hpp"
#include "../modules/colors.hpp"
#include "../modules/builtin.hpp"

using namespace std;

bool exit_shell = false;

bool exitShell()
{
	return exit_shell;
}

void parseLine(char* line, themes& appearance, char** path)
{
	char command[200];
	strcpy(command, line); // Copy of line, just in case it is needed after having used strtok
	int i = 0;
	const char s[2] = " ";
	char* token;
	char* args[10];
	token = strtok(line, s);
	while (token != NULL)
	{
		args[i] = token;
		token = strtok(NULL, s);
		i++;
	}
	args[i] = NULL;
	// Change the theme of the shell
	if(!strcmp(args[0], "theme"))
	{
		appearance.setTheme(atoi(args[1]));
	}
	else if(!strcmp(args[0], "color"))
	{
		appearance.changeColor(atoi(args[1]), atoi(args[2]));
	}
	else if(!strcmp(args[0], "cd"))
	{
		chdir(args[1]);
	}
	else if(!strcmp(args[0], "exit") || (!strcmp(args[0], "bye")) || (!strcmp(args[0], ":q")))
	{
		exit_shell = true;
	}
	else if(args[0][0] == ':')
	{
		parseBuiltin(command, appearance);
	}
	else
	{
		int status;
		pid_t pid, wait_pid;
		if ((pid = fork()) == 0) // Child
		{
			execvpe(args[0],args,path);
			cout << "Nwsh " << paintText("Error", 9) << ": command " << args[0] << " not recognized" << endl; 
			exit(0);
		}
		else // Parent
		{
			do {
				wait_pid = waitpid(pid, &status, WUNTRACED);
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}
	}
}
