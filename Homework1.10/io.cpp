#include <unistd.h>
#include <ncurses.h>
#include <ctype.h>
#include <stdlib.h>

#include "io.h"
#include "grid.h"


static void place_border(void)
{
  int i, j, width, height;
  
  width = GRID_WIDTH + 2;
  height = GRID_HEIGHT + 2;


  for(i = 0; i < height; ++i){
    for(j = 0; j < width; ++j){
      
      if((i == 0 && j == 0) || (i== height-1 && j == width -1) || (i == 0 && j == width -1) || (i== height-1 && j == 0)){
	attron(COLOR_PAIR(3));
	mvaddch(i+1, j+1, '*');
	attroff(COLOR_PAIR(3));
      }
      else if((i == 0 && j > 0) || (i == height - 1 && j > 0)){
	attron(COLOR_PAIR(1));
	mvaddch(i+1, j+1, '-');
	attroff(COLOR_PAIR(1));
      }
      else if( (i > 0 && j == 0) || (i > 0 && j == width -1) ){
	attron(COLOR_PAIR(1));
	mvaddch(i+1, j+1, '|');
	attroff(COLOR_PAIR(1));
      }
    
    }
  }
}

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

void io_display(grid *g)
{
  int i, j;

  clear();

  place_border();

  for(i = 0; i < GRID_HEIGHT; ++i){
    for(j = 0; j < GRID_WIDTH; ++j){
      switch(g->map[i][j]){
      case 'O':
	attron(COLOR_PAIR(g->color_map[i][j]));
	mvaddch(i+2, j+2, 'O');
	attroff(COLOR_PAIR(g->color_map[i][j]));
	break;      
      default:
	attron(COLOR_PAIR(6));
        mvaddch(i+2, j+2, 'X');
	attroff(COLOR_PAIR(6));
	break;
      }
    }
    putchar('\n');
  }

  putchar('\n');

  refresh();
}
