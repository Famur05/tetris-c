#ifndef FSM_H
#define FSM_H

#include "backend.h"

void start_game();
void end_game();

void user_input_1(int input);
void user_input_2(int input);

void movement(all_parameters* get_all_parameters);

#endif  // FSM_H