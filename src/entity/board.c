#include <stdlib.h>
#include "cell.h"
#include "board.h"

int init_board(s_board *b, int nb_cells)
{
	int c;

	b->nb_cells = nb_cells;
	b->cells = (s_cell*) calloc((size_t) nb_cells, sizeof(s_cell));

	for (c = 0; c < nb_cells; c++) {
		b->cells[c].id = c + 1;
	}

	return 1;
}

void free_board(s_board *b)
{
	free(b->cells);
}
