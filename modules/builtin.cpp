#include <string>
#include <cstring>
#include <iostream>

#include "builtin.hpp"
#include "../themes/themes.hpp"
#include "favs.hpp"

using namespace std;

void parseBuiltin(char* line, themes& appearance)
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
		appearance.changeColor(atoi(args[1]), atoi(args[2]));
	}
	else if(!strcmp(args[0], ":t"))
	{
		appearance.setTheme(atoi(args[1]));
	}
	else if(!strcmp(args[0], ":f"))
	{
		list_all_fav();
	}
	else if(!strcmp(args[0], ":af"))
	{
		add_fav(args[1]);
	}
}
