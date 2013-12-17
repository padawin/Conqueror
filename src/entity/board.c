#include <stdlib.h>
#include "cell.h"
#include "board.h"

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
	//find a free cell
	//set its owner
	//set the cell's pawns number (== player's pawn number)
}
