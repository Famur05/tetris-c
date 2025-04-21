#include "frontend.h"

int main() {
  int input = 0;
  ncurses_time_parametrs();
  start_game();
  while (game_status() == GAME_IS_ON) {
    input = getch();
    user_input_1(input);
    all_parameters* get_all_parameters = getting_all_parameters();
    if (get_all_parameters->ENTER) {
      if (get_all_parameters->game_parametrs.pause == 1) {
        user_input_2(input);
        timer_for_fall(get_all_parameters);
        movement(get_all_parameters);
        // вывод поля, фигуры и доп информации
        GameInfo_t info_for_field = updateCurrentState();
        // erase();
        clear();
        print_field(info_for_field);
        print_figure(get_all_parameters);
        print_additional_information(get_all_parameters);
      } else {
        print_space();
      }
    } else {
      print_enter();
    }
    refresh();
    napms(50);
  }
  endwin();
  end_game();
  return 0;
}

void ncurses_time_parametrs() {
  srand(time(0));  // для рандом числа
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, 1);
  nodelay(stdscr, 1);
  curs_set(0);
  scrollok(stdscr, 1);
  start_color();
  init_pair(1, COLOR_YELLOW, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(4, COLOR_CYAN, COLOR_BLACK);
}

void print_field(GameInfo_t info_for_field) {
  for (int i = 0; i < HEIGHT + 2; i++) {
    for (int j = 0; j < WIDTH + 2; j++) {
      if (i == 0 || i == HEIGHT + 1 || j == 0 || j == WIDTH + 1) {
        attron(COLOR_PAIR(2));
        printw("%s", "[ ]");
        attroff(COLOR_PAIR(2));
      } else {
        if (info_for_field.field[i - 1][j - 1] == 1) {
          attron(COLOR_PAIR(4));
          printw("[*]");
          attroff(COLOR_PAIR(4));
        } else {
          attron(COLOR_PAIR(1));
          printw(" . ");
          attroff(COLOR_PAIR(1));
        }
      }
    }
    printw("\n");
  }
}

void print_figure(all_parameters* get_all_parameters) {
  attron(COLOR_PAIR(1));
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (get_all_parameters->figure_parameters.arr[i][j] == 1) {
        int x_field = get_all_parameters->figure_parameters.x + j;
        int y_field = get_all_parameters->figure_parameters.y + i;
        mvprintw(y_field + 1, (x_field + 1) * 3, "[.]");
      }
    }
  }
  attroff(COLOR_PAIR(1));
}

void print_additional_information(all_parameters* get_all_parameters) {
  attron(COLOR_PAIR(2));
  mvprintw(0, 39, "[ ][ ][ ][ ][ ][ ]");
  mvprintw(21, 39, "[ ][ ][ ][ ][ ][ ]");
  for (int i = 0; i < HEIGHT + 2; i++) {
    mvprintw(i, 36, "[ ]");
    mvprintw(i, 57, "[ ]");
  }
  attroff(COLOR_PAIR(2));
  attron(COLOR_PAIR(3));
  mvprintw(1, 39, "%s %d", "LEVEL:", get_all_parameters->game_parametrs.level);
  mvprintw(3, 39, "%s %d",
           "HIGH SCORE:", get_all_parameters->game_parametrs.high_score);
  mvprintw(5, 39, "%s %d", "SCORE:", get_all_parameters->game_parametrs.score);
  mvprintw(7, 39, "%s%d", "SPEED: x", get_all_parameters->game_parametrs.speed);
  mvprintw(9, 39, "NEXT:");
  attroff(COLOR_PAIR(3));
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (get_all_parameters->game_parametrs.next[i][j] == 1) {
        attron(COLOR_PAIR(1));
        mvprintw(9 + i, 42 + (j * 3), "[.]");
        attroff(COLOR_PAIR(1));
      }
    }
  }
}

void print_enter() {
  erase();
  // clear();
  for (int i = 0; i < HEIGHT + 2; i++) {
    for (int j = 0; j < WIDTH + 2; j++) {
      if (i == 0 || i == HEIGHT + 1 || j == 0 || j == WIDTH + 1) {
        attron(COLOR_PAIR(2));
        printw("%s", "[ ]");
        attroff(COLOR_PAIR(2));
      } else {
        printw("   ");
      }
    }
    printw("\n");
  }
  int RGB = (rand() % 4) + 1;
  attron(COLOR_PAIR(RGB));
  mvprintw(10, 7, "%s", "Press <Enter> to start");
  attroff(COLOR_PAIR(RGB));
  mvprintw(13, 8, "%s", "Press <Esc> to exit");
  mvprintw(14, 4, "%s", "Press <Left or Right> to move");
  mvprintw(15, 6, "%s", "Press <Down> to speed up");
  mvprintw(17, 7, "%s", "Press </> to teleport");
  mvprintw(16, 8, "%s", "Press <w> to rotate");
}

void print_space() {
  int RGB = (rand() % 4) + 1;
  attron(COLOR_PAIR(RGB));
  mvprintw(10, 6, "%s", "Press <Space> to continue");
  attroff(COLOR_PAIR(RGB));
}