#include <string>
#include <cstring>
#include <iostream>

#include "builtin.hpp"
#include "../modules/colors.hpp"
#include "../themes/themes.hpp"
#include "favs.hpp"

using namespace std;

void parseBuiltin(char* line, themes& appearance, char** path)
{
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
	if(!strcmp(args[0], ":c"))
	{
		if(args[1] == NULL || args[2] == NULL)
		{
			cout << "Usage: :c numElement numColors" << endl;
		}
		else
		{
			appearance.changeColor(atoi(args[1]), atoi(args[2]));
		}
	}
	else if(!strcmp(args[0], ":t"))
	{
		if(args[1] == NULL)
		{
			cout << "Usage: :t numTheme" << endl;
		}
		else
		{
			appearance.setTheme(atoi(args[1]));
		}
	}
	else if(!strcmp(args[0], ":f"))
	{
		list_all_fav();
	}
	else if(!strcmp(args[0], ":af"))
	{
		// Concat args to get the whole command together
		string completeCommand = args[1];
		i = 2;
		while(args[i] != NULL)
		{
			completeCommand = completeCommand + " " + args[i];
			i++;
		}

		add_fav(completeCommand.c_str());
	}
	else if(!strcmp(args[0], ":ef"))
	{
		exec_fav(atoi(args[1]), appearance, path);
	}
	else if(!strcmp(args[0], ":rf"))
	{
		remove_fav(atoi(args[1]));
	}
	else
	{
		cout << "Nwsh " << paintText("Error", 9) << ": command " << args[0] << " not recognized" << endl;
	}
}
