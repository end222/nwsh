/*
 * nwsh
 * By end222
 */

#include <iostream>
#include <string>
#include <cstring>
#include <memory>
#include <array>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

char bin[20] = "/bin";
char *path[10] = {bin};
char *args[10];

void read_config()
{

}

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
