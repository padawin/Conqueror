#include <stdlib.h>
#include <stdint.h>
#include "ai.h"

int ai_select_cell_to_leave(struct s_cell **player_cells, int nb_cells)
{
	return 1;
}

struct s_cell *ai_select_cell_to_go_to(struct s_cell *src_cell)
{
	return NULL;
}

uint16_t ai_select_nb_pawns(struct s_cell *src_cell)
{
	return 1;
}
