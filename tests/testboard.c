#include "entity/board.h"
#include "testboard.h"
#include "test.h"

void test_init_board()
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
