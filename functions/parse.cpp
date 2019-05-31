/*
 * nwsh
 * By end222
 * File: parse.cpp
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>

#include "parse.hpp"
#include "../themes/themes.hpp"
#include "../modules/colors.hpp"
#include "../modules/builtin.hpp"
#include "../modules/variables.hpp"

using namespace std;

bool exit_shell = false;

bool exitShell()
{
	return exit_shell;
}

void parseCommand(char* line, themes& appearance, char** envp)
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

	// Line is commented
	if(args[0][0] == '#');

	// Change the theme of the shell
	else if(!strcmp(args[0], "theme"))
	{
		if(args[1] == NULL)
		{
			cout << "Usage: theme numTheme" << endl;
		}
		else
		{
			appearance.setTheme(atoi(args[1]));
		}
	}
	else if(!strcmp(args[0], "color"))
	{
		if(args[1] == NULL || args[2] == NULL)
		{
			cout << "Usage: color numElement numColor" << endl;
		}
		else
		{
			appearance.changeColor(atoi(args[1]), atoi(args[2]));
		}
	}
	else if(!strcmp(args[0], "cd"))
	{
		int returnCode = chdir(args[1]);
		if(returnCode != 0)
		{
			cout << "Unexpected error ocurred, error code: " << returnCode << endl;
		}
	}
	else if(!strcmp(args[0], "exit") || (!strcmp(args[0], "bye")) || (!strcmp(args[0], ":q")))
	{
		exit_shell = true;
	}
	else if(args[0][0] == ':')
	{
		parseBuiltin(command, appearance, envp);
	}
	else
	{
		int status;
		pid_t pid, wait_pid;
		if ((pid = fork()) == 0) // Child
		{
			execvpe(args[0],args,envp);
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

void parseLine(char* line, themes& appearance, char** envp)
{
	// TODO: parse pipelines and file redirection here
	if(strchr(line, '|') != NULL)
	{
		cout << "Pipeline found but not treated (to be implemented)" << endl;
	}
	if(strchr(line, '>') != NULL)
	{
		cout << "Redirection to a file found but not treated (to be implemented)" << endl;
	}
	if(strchr(line, '?') != NULL)
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

		i = 0;
		while(args[i] != NULL)
		{
			if (args[i][0] == '?')
			{
				string var = readVar(args[i]);
				strcpy(args[i], var.c_str());
			}
			i++;
		}

		i = 0;
		string newline = "";
		while(args[i] != NULL)
		{
			newline += string(args[i]);
			newline += " ";
			i++;
		}

		// Write the new line in "line"
		strcpy(line, newline.c_str());

	}
	parseCommand(line, appearance, envp);
}
