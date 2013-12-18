#include <stdlib.h>
#include "game.h"
#include "entity/board.h"
#include "entity/player.h"
#include "entity/cell.h"
#include "utils.h"

int select_starting_player(int nb_players);

s_player *game_start(s_board *b)
{
	int current_player_index, player_nb_cells, cell_to_leave;
	s_player *winner, *current;
	struct s_cell **player_cells;
	struct s_cell *cell_to_goto;

	winner = NULL;
	player_cells = calloc((size_t) b->nb_cells, sizeof(struct s_cell *));

	// select starting player
	current_player_index = select_starting_player(b->nb_players);

	do {
		current = b->players[current_player_index];
		// current player must choose one if its cells (C1)
		player_nb_cells = board_get_player_cells(b, current, player_cells);
		cell_to_leave = player_select_cell_to_leave(current, player_cells, player_nb_cells);
			// must be able to select a cell ID, list it's cells
		cell_to_goto = player_select_cell_to_go_to(current, player_cells[cell_to_leave]);
		// Current player must choose a neighbour cell from C1, C2
		// Current player must choose a number of n pawns to move
		// Move n pawns to C2

		if (winner == NULL)
			current_player_index = (current_player_index + 1) % b->nb_players;
	} while (winner == NULL);

	return winner;
}

int select_starting_player(int nb_players)
{
	return (int) utils_get_random_int(0, (unsigned int) nb_players);
}
