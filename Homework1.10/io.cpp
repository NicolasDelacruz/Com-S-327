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


void io_handle_input(grid *g)
{
  int key, location;

  location = 2;
  
  io_reset_terminal();
  io_display(g);
  attron(COLOR_PAIR(g->turn));
  mvaddch(0, location, 'O');
  attroff(COLOR_PAIR(g->turn));

  key = getch();

  while (key != 't') {
    switch(key){
    case 'a':
    case '4':
      if(location > 2){
	location--;
      }
      io_reset_terminal();
      io_display(g);
      attron(COLOR_PAIR(g->turn));
      mvaddch(0, location, 'O');
      attroff(COLOR_PAIR(g->turn));
      break;
    case 'd':
    case '6':
      if(location < 8){
	location++;
      }
      io_reset_terminal();
      io_display(g);
      attron(COLOR_PAIR(g->turn));
      mvaddch(0, location, 'O');
      attroff(COLOR_PAIR(g->turn));
      break;
    case 's':
    case '5':
      if(g->turn == 1){
	g->turn = 2;
      }
      else if(g->turn == 2){
	g->turn = 1;
      }


      io_reset_terminal();
      io_display(g);
      attron(COLOR_PAIR(g->turn));
      mvaddch(0, location, 'O');
      attroff(COLOR_PAIR(g->turn));
      break;
    case 'q':
      g->game_over = 1;
      break;
    }
    key = getch();
  }

}
