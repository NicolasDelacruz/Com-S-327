#include <unistd.h>
#include <ncurses.h>
#include <ctype.h>
#include <stdlib.h>

#include "io.h"
#include "grid.h"

static void check_game_over(grid *g, int y, int x)
{
  int i, j, tie, down, mindown, horizontal;
  char player_turn, not_turn;

  down = 0;
  mindown = 0;
  horizontal = 0;
  

  tie = 1;

  if(g->turn == 1){
    player_turn = '2';
    not_turn = '1';
  }
  else if(g->turn == 2){
    player_turn = '1';
    not_turn = '2';
  }

  //check if game is tied
  for(i = 0; i < GRID_HEIGHT; ++i){
    for(j = 0; j < GRID_WIDTH; ++j){
      if(g->map[i][j] == 0){
	tie = 0;
      }
    }
  }
  
  //checks tie
  if(tie){
    g->game_end = 't';
    g->game_over = 1;
  }
  

  //check straight down win
  mindown = y + 4;
  if(mindown >= GRID_HEIGHT){
    mindown = GRID_HEIGHT-1;
  }

  for(i = y; i <= mindown; ++i){
    if(g->map[i][x] == player_turn){
      down++;
    }
  }

  //check horizontal win (---)

  for(i = 0; i < GRID_WIDTH; ++i){
    if(g->map[y][i] == player_turn){
      horizontal++;
    }
    else if(g->map[y][i] == not_turn){
      horizontal = 0;
    }

    if(g->map[y][i] == 0){
      break;
    }
  
    if(horizontal > 3){
      break;
    }
  }

  //check right win (--->)

  //check top left win

  //check top right win

  if(down >= 4 || horizontal >= 4){
    g->game_end = player_turn;
    g->game_over = 1;
  }

}

static int get_lowest_location(grid *g, int x)
{
  int y;
  for(y = GRID_HEIGHT-1; y > -1; --y){
    if(g->map[y][x] == 0){
      return y;
    }
  }
  return -1;
}

static int place_move(grid *g, int x){
  int y;

  y = get_lowest_location(g, x);
  if(y == -1){
    return y;
  }
  if(g->turn == 1){
    g->map[y][x] = '1';
  }else{
    g->map[y][x] = '2';
  }

  return y;
}


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
      case '1':
	attron(COLOR_PAIR(1));
	mvaddch(i+2, j+2, 'O');
	attroff(COLOR_PAIR(1));
	break;
      case '2':
	attron(COLOR_PAIR(2));
	mvaddch(i+2, j+2, 'O');
	attroff(COLOR_PAIR(2));
      }
    }
    putchar('\n');
  }

  putchar('\n');

  refresh();
}


void io_handle_input(grid *g)
{
  int key, location, ylocation;

  location = 2;
  
  io_reset_terminal();
  io_display(g);
  attron(COLOR_PAIR(g->turn));
  mvaddch(0, location, 'O');
  attroff(COLOR_PAIR(g->turn));

  while (!g->game_over) {
    switch(key = getch()){
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
      //add new thing
      //if place_move failed then end case
      ylocation = place_move(g, location-2);
      if(ylocation == -1){
	break;
      }

      //switch turns
      if(g->turn == 1){
	g->turn = 2;
      }
      else if(g->turn == 2){
	g->turn = 1;
      }

      //display new map
      io_reset_terminal();
      io_display(g);
      attron(COLOR_PAIR(g->turn));
      mvaddch(0, location, 'O');
      attroff(COLOR_PAIR(g->turn));


      check_game_over(g, ylocation, location - 2);
      break;
    case 'q':
      g->game_end = 'q';
      g->game_over = 1;
      break;
    }
  }

}
