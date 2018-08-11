/*
 * nwsh
 * By end222
 */

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

void command_loop()
{
	bool exit = false;
	char line[256];
	while (exit == false)
	{
		cout << "Name@Home > " << flush;
		cin.getline(line,256);
		cout << line << endl;
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
		command_loop();
	}
}
