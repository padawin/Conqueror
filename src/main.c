#include <stdlib.h>
#include "entity/player.h"
#include "entity/board.h"
#include "game.h"
#include "builder.h"

#define NB_PAWNS_PER_PLAYER 8

int main()
{
	s_board b;
	s_player p1, p2;

	builder_create_small_board(&b);
	init_player(&p1, 1, "Player 1", 1, STRATEGY_NONE, NB_PAWNS_PER_PLAYER);
	init_player(&p2, 2, "Player 2", 1, STRATEGY_NONE, NB_PAWNS_PER_PLAYER);

	board_add_player(&b, &p1);
	board_add_player(&b, &p2);

	game_start(&b);

	free_board(&b);

	return EXIT_SUCCESS;
}
