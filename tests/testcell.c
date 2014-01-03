#include <stdlib.h>
#include <stdio.h>
#include "entity/cell.h"
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
