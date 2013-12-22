#include <stdlib.h>
#include "testbuilder.h"
#include "entity/board.h"
#include "builder.h"
#include "test.h"

void test_board_creation()
{
	s_board b;

	builder_create_small_board(&b, 2);
	//~assert_int_equals(result, 1);
	assert_int_equals(b.nb_cells, SMALL_BOARD_NB_CELLS);
	assert_int_equals(b.nb_players, 0);
	assert_int_equals(b.nb_total_players, 2);
}
