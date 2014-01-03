#include <stdlib.h>
#include <stdio.h>
#include "entity/cell.h"
#include "entity/player.h"
#include "testcell.h"
#include "test.h"

void test_init_cell(void)
{
	printf("\ntest_init_cell\n");
	s_cell c;
	int result;

	result = init_cell(&c, 1, 4);
	assert_null(c.owner);
	assert_int_equals(result, 1);
	assert_int_equals(c.id, 1);
	assert_int_equals(c.nb_pawns, 0);
	assert_int_equals(c.nb_neighbours, 0);
	assert_int_equals(c.nb_max_neighbours, 3);

	free_cell(&c);
}

void test_free_cell(void)
{
	printf("\ntest_free_cell\n");
	s_cell c;
	init_cell(&c, 1, 4);
	free_cell(&c);

	assert_null(c.neighbours);
}

void test_cell_set_owner(void)
{
	printf("\ncell_set_owner\n");
	s_cell c;
	s_player p;
	init_cell(&c, 1, 4);
	init_player(&p, "test", 1, 1,10);

	assert_null(c.owner);
	cell_set_owner(&c, &p);
	assert_str_equals(c.owner->name, "test");

	free_cell(&c);
}
