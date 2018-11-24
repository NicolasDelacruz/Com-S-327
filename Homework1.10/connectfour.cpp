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

  //io_reset_terminal();
  
  return 0;
}
