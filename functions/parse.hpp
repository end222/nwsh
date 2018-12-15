#ifndef PARSE_HPP
#define PARSE_HPP

#include "../themes/themes.hpp"

using namespace std;

bool exitShell();

void parseLine(char* line, themes& appearance, char** parse);

#endif
