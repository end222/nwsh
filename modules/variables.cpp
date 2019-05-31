#include <string>
#include <cstring>
#include <iostream>
#include <dirent.h>
#include "../functions/exec.hpp"
#include "variables.hpp"

using namespace std;

/*
 * There are 2 types of variables:
 *
 * $variable: will be stored in memory and are lost whenever the shell
 * session is closed
 *
 * ?variable: will be stored in disk inside the ~/.config/nwsh folder.
 * They are available in different nwsh session and can also be used
 * to connect 2 nwsh sessions.
 * They are stored using a tree scheme, like a filesystem. Then, a leaf can
 * be accesed by ?notleafnode/leaf
 */

string readVar(char* variable)
{
	char command[100];

	string home = exec("echo ~");
	home.erase(home.length()-1);
	string var_location = home + "/.config/nwsh/variables/";
	// Command to get the content of the variable
	string varStr = string(variable);
	varStr.erase(0,1);
	string command_str = "cat " + var_location + varStr;
	strcpy(command, command_str.c_str());	
	string value = exec(command);
	value.erase(value.length()-1); 
	return value;
}
