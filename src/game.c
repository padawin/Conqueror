#include <stdlib.h>
#include "game.h"
#include "entity/board.h"
#include "entity/player.h"
#include "entity/cell.h"
#include "utils.h"

int select_starting_player(int nb_players);

s_player *game_start(s_board *b)
{
	int current_player_index, player_nb_cells, cell_to_leave, nb_pawns_to_move;
	s_player *winner, *current;
	struct s_cell **player_cells;
	struct s_cell *cell_to_goto;

	winner = NULL;
	player_cells = calloc((size_t) b->nb_cells, sizeof(struct s_cell *));

	// select starting player
	current_player_index = select_starting_player(b->nb_players);

	do {
		current = b->players[current_player_index];

		player_nb_cells = board_get_player_cells(b, current, player_cells);

		// Here the player can list his cells, see the neighbours of any of his
		// cells, select a cell to leave
		// cell_to_leave = cell index in player_cells
		cell_to_leave = player_select_cell_to_leave(current, player_cells, player_nb_cells);

		// Select a neighbours cell of cell_to_leave to go there
		// cell_to_goto = cell struct of the cell to go to
		cell_to_goto = player_select_cell_to_go_to(current, player_cells[cell_to_leave]);

		// Select the number of pawns to move
		nb_pawns_to_move = player_select_nb_pawns(current, player_cells[cell_to_leave]);

		if (winner == NULL)
			current_player_index = (current_player_index + 1) % b->nb_players;
	} while (winner == NULL);

	return winner;
}

int select_starting_player(int nb_players)
{
	return (int) utils_get_random_int(0, (unsigned int) nb_players);
}
