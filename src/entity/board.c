#include <stdlib.h>
#include "cell.h"
#include "board.h"
#include "../utils.h"

int init_board(s_board *b, int nb_cells, int nb_players)
{
	int c;

	b->nb_cells = nb_cells;
	b->cells = (s_cell*) calloc((size_t) nb_cells, sizeof(s_cell));

	b->nb_total_players = nb_players;
	b->players = (s_player **) calloc((size_t) nb_players, sizeof(s_player *));

	for (c = 0; c < nb_cells; c++) {
		init_cell(&b->cells[c], c + 1, nb_cells);
	}

	return 1;
}

void free_board(s_board *b)
{
	free(b->cells);
	free(b->players);
}

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

	return cell_index;
}

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
