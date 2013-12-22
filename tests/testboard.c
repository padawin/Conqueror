#include "entity/board.h"
#include "entity/player.h"
#include "testboard.h"
#include "test.h"

void test_init_board(void)
{
	s_board b;

	init_board(&b, 4, 2);

	assert_int_equals(b.nb_cells, 4);
	assert_int_equals(b.nb_players, 0);
	assert_int_equals(b.nb_total_players, 2);

	free_board(&b);

}

void test_free_board(void)
{
	s_board b;

	init_board(&b, 4, 2);

	free_board(&b);

	assert_null(b.cells);
	assert_null(b.players);
}

void test_board_add_player(void)
{
	s_board b;
	int index_p1, index_p2, index_p3, nb_cells;
	s_player p1, p2, p3;

	nb_cells = 4;
	init_board(&b, nb_cells, 2);

	builder_create_small_board(&b, 2);
	init_player(&p1, "Player 1", 1, STRATEGY_NONE, 1, nb_cells);
	init_player(&p2, "Player 2", 1, STRATEGY_OFFENCE, 1, nb_cells);
	init_player(&p2, "Player 3", 1, STRATEGY_OFFENCE, 1, nb_cells);

	p1.id = 1;
	p2.id = 2;
	p2.id = 3;

	index_p1 = board_add_player(&b, &p1);
	assert_int_equals(b.nb_players, 1);
	assert_int_not_equals(index_p1, -1);

	index_p2 = board_add_player(&b, &p2);
	assert_int_equals(b.nb_players, 2);
	assert_int_not_equals(index_p2, -1);

	index_p3 = board_add_player(&b, &p3);
	assert_int_equals(b.nb_players, 2);
	assert_int_equals(index_p3, -1);

	free_player(&p1);
	free_player(&p2);
	free_player(&p3);
	free_board(&b);
}
