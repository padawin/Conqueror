#include "testbuilder.h"
#include "testboard.h"

void testbuilder();
void testboard();

int main()
{
	testbuilder();
	testboard();
	return 1;
}

void testbuilder()
{
	test_board_creation();
}

void testboard()
{
	test_init_board();
}
