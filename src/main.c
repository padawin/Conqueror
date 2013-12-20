#include <stdlib.h>
#include "entity/player.h"
#include "entity/cell.h"
#include "entity/board.h"
#include "game.h"
#include "builder.h"

#define NB_CELLS 4
#define NB_PAWNS_PER_PLAYER 8

int main()
{
	s_board b;
	s_player p1, p2;

	builder_create_small_board(&b, 2);
	init_player(&p1, "Player 1", 1, STRATEGY_NONE, NB_PAWNS_PER_PLAYER, NB_CELLS);
	init_player(&p2, "Player 2", 1, STRATEGY_OFFENCE, NB_PAWNS_PER_PLAYER, NB_CELLS);

	p1.id = 1;
	p2.id = 2;

	board_add_player(&b, &p1);
	board_add_player(&b, &p2);

	game_start(&b);

	free_board(&b);
	free_player(&p1);

	return EXIT_SUCCESS;
}
