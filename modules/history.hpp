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

void add_hist(const char* fav);

void list_all_hist();

void write_hist();

void load_hist();
#endif