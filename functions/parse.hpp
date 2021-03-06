/*
 * nwsh
 * By end222
 * File: parse.hpp
 */

#ifndef PARSE_HPP
#define PARSE_HPP

#include "../themes/themes.hpp"

using namespace std;

bool exitShell();

void parseCommand(char* line, themes& appearance, char** envp);

void parseLine(char* line, themes& appearance, char** envp);

#endif
