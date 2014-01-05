#include "testbuilder.h"
#include "testboard.h"
#include "testcell.h"
#include "testplayer.h"

void testbuilder(void);
void testboard(void);
void testcell(void);
void testplayer(void);

int main()
{
	testbuilder();
	testboard();
	testcell();
	testplayer();
	return 1;
}

void testbuilder(void)
{
	test_builder();
}

void testboard(void)
{
	test_init_board();
	test_free_board();
	test_board_add_player();
	test_board_get_player_cells();
}

void testcell(void)
{
	test_init_cell();
	test_free_cell();
	test_cell_set_owner();
	test_cell_set_nb_pawns();
	test_cell_add_neighbour();
	test_cell_are_neighbours();
}

void testplayer(void)
{
	test_init_player();
}
