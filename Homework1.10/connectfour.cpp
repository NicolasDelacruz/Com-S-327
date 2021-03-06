#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

#include "grid.h"
#include "io.h"

int main(int argc, char *argv[])
{
  grid g;
  using namespace std;

  init_grid(&g);

  io_init_terminal();


  io_display(&g);

  while(!g.game_over){
    io_handle_input(&g);
  }

  io_reset_terminal();

  if(g.game_end == 't'){
    cout << "TIE GAME!!" << endl;
  }
  else if(g.game_end == '1'){
    cout << "PLAYER 1 WON!!" << endl;
  }
  else if(g.game_end == '2'){
    cout << "PLAYER 2 WON!!" << endl;
  }
  else if(g.game_end == 'q'){
    cout << "Someone quit the game.";
  }

  return 0;
}
