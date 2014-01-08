#include <stdint.h>
#include "builder.h"
#include "entity/board.h"

/**
 * A small board has 4 cells, and its layout is a square.
 * 1 ----- 2
 * |       |
 * |       |
 * |       |
 * 4 ----- 3
 */
void builder_create_small_board(s_board *b, uint8_t *nb_max_players, uint16_t *pawns_per_player)
{
	int c;

	*nb_max_players = 2;
	*pawns_per_player = 8;
	init_board(b, SMALL_BOARD_NB_CELLS, *nb_max_players);

	for (c = 0; c < SMALL_BOARD_NB_CELLS; c++) {
		b->cells[c].neighbours[0] = &b->cells[(SMALL_BOARD_NB_CELLS + c - 1) % SMALL_BOARD_NB_CELLS];
		b->cells[c].neighbours[1] = &b->cells[(c + 1) % SMALL_BOARD_NB_CELLS];
		b->cells[c].nb_neighbours = 2;
	}
}
