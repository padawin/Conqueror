#include <stdlib.h>
#include <stdio.h>
#include "builder.h"
#include "entity/board.h"
#include "entity/player.h"
#include "testboard.h"
#include "test.h"

void test_init_board(void)
{
	printf("\ntest_init_board\n");
	s_board b;
	int result;

	result = init_board(&b, 4, 2);

	assert_int_equals(result, INIT_BOARD_OK);
	assert_int_equals(b.nb_cells, 4);
	assert_int_equals(b.nb_players, 0);
	assert_int_equals(b.nb_total_players, 2);

	free_board(&b);
}

void test_free_board(void)
{
	printf("\ntest_free_board\n");
	s_board b;

	init_board(&b, 4, 2);

	free_board(&b);

	assert_null(b.cells);
	assert_null(b.players);
}

void test_board_add_player(void)
{
	printf("\ntest_board_add_player\n");
	s_board b;
	int index_p1, index_p2, index_p3;
	uint8_t nb_cells;
	s_player p1, p2, p3;

	nb_cells = 4;
	init_board(&b, nb_cells, 2);

	builder_create_small_board(&b, 2);
	init_player(&p1, "Player 1", 1, STRATEGY_NONE, 1);
	init_player(&p2, "Player 2", 1, STRATEGY_OFFENCE, 1);
	init_player(&p2, "Player 3", 1, STRATEGY_OFFENCE, 1);

	p1.id = 1;
	p2.id = 2;
	p2.id = 3;

	index_p1 = board_add_player(&b, &p1);
	assert_int_equals(b.nb_players, 1);
	assert_int_equals(b.players[0]->nb_cells, 1);
	assert_int_not_equals(index_p1, -1);

	index_p2 = board_add_player(&b, &p2);
	assert_int_equals(b.nb_players, 2);
	assert_int_equals(b.players[1]->nb_cells, 1);
	assert_int_not_equals(index_p2, -1);

	index_p3 = board_add_player(&b, &p3);
	assert_int_equals(b.nb_players, 2);
	assert_int_equals(index_p3, -1);

	free_board(&b);
}

void test_board_get_player_cells(void)
{
	printf("\ntest_board_get_player_cells\n");
	s_board b;
	s_player p1;
	struct s_cell **player_cells;
	uint8_t nb_cells;
	int nb_players_cells;

	nb_cells = 4;
	init_board(&b, nb_cells, 2);
	player_cells = calloc((size_t) b.nb_cells, sizeof(struct s_cell *));

	builder_create_small_board(&b, 2);
	init_player(&p1, "Player 1", 1, STRATEGY_NONE, 1);

	p1.id = 1;

	board_add_player(&b, &p1);
	nb_players_cells = board_get_player_cells(&b, &p1, player_cells);
	assert_int_equals(nb_players_cells, 1);
	assert_not_null(player_cells[0]);
	assert_null(player_cells[1]);

	free_board(&b);
}
