/*
 * nwsh
 * By end222
 * File: modules/favs.hpp
 */

#ifndef HISTORY_HPP
#define HISTORY_HPP

#include "../themes/themes.hpp"
#include "builtin.hpp"
#include "../functions/parse.hpp"

#include <string>

struct hist_entry
{
	string command;
	hist_entry* next;
	hist_entry* former;
};

void add_hist(const char* fav);

void list_all_hist();

void write_hist();

void load_hist();

string get_hist_command(int index);

bool check_history_index(int index);
#endif
