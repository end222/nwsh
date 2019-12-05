/*
 * nwsh
 * By end222
 * File: modules/favs.hpp
 */

#ifndef FAVS_HPP
#define FAVS_HPP

#include "../themes/themes.hpp"
#include "builtin.hpp"
#include "../functions/parse.hpp"

struct fav_entry
{
	string command;
	fav_entry* next;
	fav_entry* former;
};

void add_fav(const char* fav);

void remove_fav(int number);

void list_all_fav();

void exec_fav(int commandNum, themes appearance, char** envp);

void write_favorites();

void load_favorites();

string get_fav_command(int index);

bool check_fav_index(int index);
#endif
