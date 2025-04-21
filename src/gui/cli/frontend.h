#ifndef FRONTEND_H
#define FRONTEND_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#include "../../brick_game/tetris/backend.h"
#include "../../brick_game/tetris/fsm.h"
#include "../../brick_game/tetris/tetris_lib.h"

void ncurses_time_parametrs();
void print_field(GameInfo_t info_for_field);
void print_figure(all_parameters* get_all_parameters);
void print_additional_information(all_parameters* get_all_parameters);
void print_enter();
void print_space();

#endif  // FRONTEND_H
