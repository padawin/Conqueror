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

	builder_create_small_board(&b);

	for (c = 0; c < SMALL_BOARD_NB_CELLS; c++) {
		assert_int_equals(b.cells[c].nb_neighbours, 2);
		assert_int_equals(b.cells[c].neighbours[0]->id, b.cells[(SMALL_BOARD_NB_CELLS + c - 1) % SMALL_BOARD_NB_CELLS].id);
		assert_int_equals(b.cells[c].neighbours[1]->id, b.cells[(c + 1) % SMALL_BOARD_NB_CELLS].id);
	}

	free_board(&b);
}
