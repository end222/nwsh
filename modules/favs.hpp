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

void add_fav(const char* fav);

void remove_fav(int number);

void list_all_fav();

void exec_fav(int commandNum, themes appearance, char** path);

void write_favorites();

#endif
