#ifndef IO_H
# define IO_H


typedef struct dungeon dungeon_t;
typedef struct pc pc_t;

void io_init_terminal(void);
void io_reset_terminal(void);
void io_display(dungeon_t *d, pc_t *vision_pc);
void io_handle_input(dungeon_t *d, pc_t *vision_pc);
void io_queue_message(const char *format, ...);

#endif
