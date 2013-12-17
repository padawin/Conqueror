#include <stdlib.h>
#include <stdio.h>
#include "entity/player.h"
#include "entity/cell.h"
#include "entity/board.h"
#include "builder.h"

#define NB_CELLS 4
#define NB_PAWNS_PER_PLAYER 3

int main()
{
	s_board b;
	s_player p1;

	create_small_board(&b);
	init_player(&p1, "Player 1", 1, STRATEGY_NONE, NB_PAWNS_PER_PLAYER, NB_CELLS);

	printf("Nb cells: %d\n", b.nb_cells);
	printf("Player name: %s\n", p1.name);
	printf("Player pawns number: %d\n", p1.nb_pawns);

	free_board(&b);
	free_player(&p1);

	return EXIT_SUCCESS;
}
