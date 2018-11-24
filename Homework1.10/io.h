#ifndef IO_H
# define IO_H

class grid;

void io_init_terminal(void);
void io_reset_terminal(void);
void io_display(grid *g);

#endif
