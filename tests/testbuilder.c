#include <stdlib.h>
#include <stdio.h>
#include "testbuilder.h"
#include "entity/board.h"
#include "builder.h"
#include "test.h"

void test_builder(void)
{
	printf("\ntest_builder\n");
	s_board b;
	int c;
	uint8_t nb_players_max;
	uint16_t nb_pawns_per_player;

	builder_create_board(BUILDER_SMALL_BOARD, &b, &nb_players_max, &nb_pawns_per_player);

	assert_int_equals(nb_players_max, 2);
	assert_int_equals(nb_pawns_per_player, 8);
	for (c = 0; c < SMALL_BOARD_NB_CELLS; c++) {
		assert_int_equals(b.cells[c].nb_neighbours, 2);
		assert_int_equals(b.cells[c].neighbours[0]->id, b.cells[(SMALL_BOARD_NB_CELLS + c - 1) % SMALL_BOARD_NB_CELLS].id);
		assert_int_equals(b.cells[c].neighbours[1]->id, b.cells[(c + 1) % SMALL_BOARD_NB_CELLS].id);
	}

	free_board(&b);
}
