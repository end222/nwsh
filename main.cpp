/*
 * nwsh
 * By end222
 */

#include <iostream>
#include <string>
#include <cstring>
#include <memory>
#include <array>
#include <fstream>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "modules/favs.hpp"

using namespace std;

char *path[10];
int path_dirs = 0;
char *args[10];

string exec(const char* cmd) {
	array<char, 128> buffer;
	string result;
	shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);	
	if (!pipe) throw runtime_error("popen() failed!");
		while (!feof(pipe.get())) {
			if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
				result += buffer.data();
		}
	return result;
}

void read_config()
{
	char line[100];
	ifstream config_file;
	string home = exec("echo ~");
	home.erase(home.length()-1);
	string config_location = home + "/.nwshrc";
	config_file.open(config_location);
	while (!config_file.eof())
	{
		config_file.getline(line, 100);
		cout << line << endl;
	}
}

void command_loop()
{
	bool exit = false;
	char line[256];

	string system_name = exec("hostname");
	string user_name = exec("whoami");
	system_name.erase(system_name.length()-1); // Remove end of line from the string
	user_name.erase(user_name.length()-1);

	while (exit == false)
	{
		cout << user_name << " at " << system_name << " ~ " << flush;
		cin.getline(line,256);
		if (!strcmp(line,"exit"))
		{
			exit = true;
		}
		else
		{
			int status;
			pid_t pid, wait_pid;
			if ((pid = fork()) == 0) // Child
			{
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
				execvpe(line,args,path);
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

int main(int argc, char *argv[])
{
	if (argc > 1)
	{
		if (!strcmp(argv[1],"-h") || !strcmp(argv[1],"--help"))
		{
			cout << "Help page" << endl;
		}
		else if (argv[1] == "-v" || argv[1] == "--version")
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
