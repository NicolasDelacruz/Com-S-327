#include <unistd.h>
#include <ncurses.h>
#include <ctype.h>
#include <stdlib.h>

#include "io.h"
#include "field.h"

void io_init_terminal(void)
{
  initscr();
  raw();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  start_color();
  init_pair(COLOR_RED, COLOR_RED, COLOR_BLACK);
  init_pair(COLOR_GREEN, COLOR_GREEN, COLOR_BLACK);
  init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
  init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);
  init_pair(COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(COLOR_CYAN, COLOR_CYAN, COLOR_BLACK);
  init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);
}

void io_reset_terminal(void)
{
  endwin();
}

void io_display(field *f)
{
  int i, j;

  clear();

  /*
  for(i = 0; i < FIELD_SIZE; ++i){
    for(j = 0; j < FIELD_SIZE; ++j){
      switch(f->display_map[i][j]){
      case 'X':
	attron(COLOR_PAIR(COLOR_BLUE));
	mvaddch(i+1, j+1, 'X');
	attroff(COLOR_PAIR(COLOR_BLUE));
	break;
      case '*':
	attron(COLOR_PAIR(COLOR_RED));
        mvaddch(i+1, j+1, '*');
	attroff(COLOR_PAIR(COLOR_RED));
	break;
      default:
	attron(COLOR_PAIR(COLOR_YELLOW));
        mvaddch(i+1, j+1, '0');
	attroff(COLOR_PAIR(COLOR_YELLOW));
	break;
      }
    }
    putchar('\n');
  }
  */
  
  for(i = 0; i < FIELD_SIZE; ++i){
    for(j = 0; j < FIELD_SIZE; ++j){
      attron(COLOR_PAIR(COLOR_BLUE));
      mvaddch(i+1, j+1, f->map[i][j]);
      attroff(COLOR_PAIR(COLOR_BLUE));
    }
  }
  

  refresh();
}
