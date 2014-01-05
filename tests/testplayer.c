#include <stdlib.h>
#include <stdio.h>
#include "entity/player.h"
#include "testplayer.h"
#include "test.h"

void test_init_player(void)
{
	printf("\ntest_init_player\n");
	s_player p1, p2, p3, p4, p5;
	int result;

	result = init_player(&p1, 1, "my name 1", 1, STRATEGY_NONE, 10);
	assert_int_equals(result, INIT_PLAYER_OK);
	assert_str_equals(p1.name, "my name 1");
	assert_int_equals(p1.id, 1);
	assert_int_equals(p1.nb_cells, 0);
	assert_int_equals(p1.nb_pawns, 10);
	assert_int_equals(p1.strategy, STRATEGY_NONE);
	assert_int_equals(p1.is_human, 1);

	result = init_player(&p2, 2, "my name 2", 1, STRATEGY_OFFENCE, 10);
	assert_int_equals(result, PLAYER_ERROR_INIT_PLAYER_STRATEGY);

	result = init_player(&p3, 3, "my name 3", 0, STRATEGY_NONE, 10);
	assert_int_equals(result, PLAYER_ERROR_INIT_PLAYER_STRATEGY);

	result = init_player(&p4, 4, "my name 4", 0, STRATEGY_SPREAD, 10);
	assert_int_equals(result, INIT_PLAYER_OK);
	assert_str_equals(p4.name, "my name 4");
	assert_int_equals(p4.id, 4);
	assert_int_equals(p4.nb_cells, 0);
	assert_int_equals(p4.nb_pawns, 10);
	assert_int_equals(p4.strategy, STRATEGY_SPREAD);
	assert_int_equals(p4.is_human, 0);
//~
	result = init_player(&p5, 5, "", 1, STRATEGY_NONE, 10);
	assert_int_equals(result, PLAYER_ERROR_INIT_PLAYER_EMPTY_NAME);
}

void test_player_move_to_cell(void)
{
	printf("\ntest_player_move_to_cell\n");
	s_cell c1, c2, c3;
	s_player p1, p2;
	short result;

	init_cell(&c1, 1, 3);
	init_cell(&c2, 2, 3);
	init_cell(&c3, 3, 3);
	init_player(&p1, 1, "p1", 1, STRATEGY_NONE, 10);
	init_player(&p2, 2, "p2", 1, STRATEGY_NONE, 10);

	cell_add_neighbour(&c1, &c2);
	cell_add_neighbour(&c2, &c3);

	cell_set_owner(&c1, &p1);
	cell_set_nb_pawns(&c1, 10);
	cell_set_owner(&c3, &p2);
	cell_set_nb_pawns(&c3, 10);

	// test move all pawns from src cell
	result = player_move_to_cell(&p1, 10, &c1, &c2);
	assert_int_equals(result, PLAYER_ERROR_MOVE_ALL_PAWNS);

	// test move too many pawns
	result = player_move_to_cell(&p1, 11, &c1, &c2);
	assert_int_equals(result, PLAYER_ERROR_MOVE_NOT_ENOUGH_PAWNS);

	// test move to a cell too far away
	result = player_move_to_cell(&p1, 1, &c1, &c3);
	assert_int_equals(result, PLAYER_ERROR_MOVE_CELLS_NOT_NEIGHBOURS);

	// move no fight
	assert_int_equals(p1.nb_cells, 1);
	result = player_move_to_cell(&p1, 5, &c1, &c2);
	assert_int_equals(result, NO_FIGHT);
	assert_int_equals(c1.nb_pawns, 5);
	assert_int_equals(c2.nb_pawns, 5);
	assert_int_equals(p1.nb_pawns, 10);
	assert_int_equals(p1.nb_cells, 2);
	assert_int_equals(c2.owner->id, p1.id);

	// move fight win
	result = player_move_to_cell(&p2, 6, &c3, &c2);
	assert_int_equals(result, FIGHT_WON);
	assert_int_equals(c3.nb_pawns, 4);
	assert_int_equals(c2.nb_pawns, 6);
	assert_int_equals(p2.nb_pawns, 10);
	assert_int_equals(p2.nb_cells, 2);
	assert_int_equals(p1.nb_pawns, 5);
	assert_int_equals(p1.nb_cells, 1);
	assert_int_equals(c2.owner->id, p2.id);

	// move fight lose
	result = player_move_to_cell(&p1, 4, &c1, &c2);
	assert_int_equals(result, FIGHT_LOST);
	assert_int_equals(c1.nb_pawns, 1);
	assert_int_equals(c2.nb_pawns, 6);
	assert_int_equals(p1.nb_pawns, 1);
	assert_int_equals(p1.nb_cells, 1);
	assert_int_equals(p2.nb_pawns, 10);
	assert_int_equals(p2.nb_cells, 2);
	assert_int_equals(c2.owner->id, p2.id);

	// move fight draw
	result = player_move_to_cell(&p2, 1, &c2, &c1);
	assert_int_equals(result, FIGHT_DRAW);
	assert_int_equals(c2.nb_pawns, 6);
	assert_int_equals(c1.nb_pawns, 1);
	assert_int_equals(p1.nb_pawns, 1);
	assert_int_equals(p1.nb_cells, 1);
	assert_int_equals(p2.nb_pawns, 10);
	assert_int_equals(p2.nb_cells, 2);
	assert_int_equals(c2.owner->id, p2.id);
	assert_int_equals(c1.owner->id, p1.id);

	free_cell(&c1);
	free_cell(&c2);
	free_cell(&c3);
}
