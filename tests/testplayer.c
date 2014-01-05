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

}
