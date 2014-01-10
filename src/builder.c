#include <stdint.h>
#include "builder.h"
#include "entity/board.h"

void _create_small_board(s_board *b, uint8_t *nb_max_players, uint16_t *pawns_per_player);

/**
 * Function to build a board from a board size
 *
 * @param int size The size, can be (BUILDER_SMALL_BOARD|BUILDER_MEDIUM_BOARD|BUILDER_LARGE_BOARD)
 * @param s_board *b The board
 * @param uint8_t *nb_max_players The board max number of players, output variable
 * @param uint16_t *pawns_per_player The number of pawns per players, output variable
 *
 * @return int The result of the creation
 */
int builder_create_board(int size, s_board *b, uint8_t *nb_max_players, uint16_t *pawns_per_player)
{
	int result;

	result = BUILDER_BOARD_CREATED;
	if (size == BUILDER_SMALL_BOARD) {
		_create_small_board(b, nb_max_players, pawns_per_player);
	}
	else {
		result = BUILDER_ERROR_INVALID_BOARD_SIZE;
	}

	return result;
}
/**
 * A small board has 4 cells, and its layout is a square.
 * 1 ----- 2
 * |       |
 * |       |
 * |       |
 * 4 ----- 3
 */
void _create_small_board(s_board *b, uint8_t *nb_max_players, uint16_t *pawns_per_player)
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
