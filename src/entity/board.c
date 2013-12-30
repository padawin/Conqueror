#include <stdlib.h>
#include "cell.h"
#include "board.h"
#include "../utils.h"

/**
 * Function to initalise the board.
 *
 * @param s_board *b The board to initialise
 * @param uint8_t nb_cells The board's number of cells
 * @param uint8_t nb_players The number of players
 *
 * @return int 1 if the board is correctly initialised,
 * 		ERROR_INIT_BOARD_INVALID_CELLS_NUMBER if the cells number is lower than
 * 		1, ERROR_INIT_BOARD_INVALID_PLAYERS_NUMBER if the players number is
 * 		lower than 1.
 */
int init_board(s_board *b, uint8_t nb_cells, uint8_t nb_players)
{
	int c;

	if (nb_cells < 1) {
		return ERROR_INIT_BOARD_INVALID_CELLS_NUMBER;
	}

	if (nb_players < 1) {
		return ERROR_INIT_BOARD_INVALID_PLAYERS_NUMBER;
	}

	b->nb_cells = nb_cells;
	b->cells = (s_cell*) calloc((size_t) nb_cells, sizeof(s_cell));

	b->nb_total_players = nb_players;
	b->nb_players = 0;
	b->players = (s_player **) calloc((size_t) nb_players, sizeof(s_player *));

	for (c = 0; c < nb_cells; c++) {
		init_cell(&b->cells[c], c + 1, nb_cells);
	}

	return 1;
}

/**
 * Function to free the memory used by a board. Will free the board's cells and
 * players, which have been allocated with a calloc.
 *
 * @param s_board *b The board to free
 *
 * @return void
 */
void free_board(s_board *b)
{
	free(b->cells);
	free(b->players);
	b->cells = NULL;
	b->players = NULL;
}

/**
 * Add a player to the board.
 *
 * @param s_board *b
 * @param s_player *p
 *
 * @return int -1 if the board can not have more players, the player index in
 * 		the players' list else.
 */
int board_add_player(s_board *b, s_player *p)
{
	int cell_index = -1;

	if (b->nb_players == b->nb_total_players) {
		return cell_index;
	}

	//find a free cell
	do {
		cell_index = (int) utils_get_random_int(0, (unsigned int) b->nb_cells);
	} while (cell_index == -1 || b->cells[cell_index].owner != NULL);

	b->cells[cell_index].owner = p;
	b->cells[cell_index].nb_pawns = p->nb_pawns;

	b->players[b->nb_players] = p;
	b->nb_players++;
	p->nb_cells++;

	return cell_index;
}

/**
 * Function to get the list of the cells belonging to a given player.
 *
 * @param s_board *b The board
 * @param s_player *p The current player
 * @param s_cell **player_cells The cells list to populate
 *
 * @return int The player's number of cells
 */
int board_get_player_cells(s_board *b, s_player *p, s_cell **player_cells)
{
	int c, nb_cells;

	nb_cells = 0;
	for (c = 0; c < b->nb_cells; c++) {
		if (b->cells[c].owner != NULL && b->cells[c].owner->id == p->id) {
			player_cells[nb_cells++] = &b->cells[c];
		}
	}

	return nb_cells;
}
