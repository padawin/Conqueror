#ifndef S_BOARD
#define S_BOARD

#include "cell.h"

typedef struct {
	int nb_cells;
	s_cell *cells;
} s_board;

int init_board(s_board *b, int nb_cells);
void free_board(s_board *b);
int board_add_player(s_player * p);

#endif
