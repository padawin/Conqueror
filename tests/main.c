#include "testbuilder.h"
#include "testboard.h"

void testbuilder(void);
void testboard(void);

int main()
{
	testbuilder();
	testboard();
	return 1;
}

void testbuilder(void)
{
	test_board_creation();
}

void testboard(void)
{
	test_init_board();
	test_free_board();
	test_board_add_player();
	test_board_get_player_cells();
}
