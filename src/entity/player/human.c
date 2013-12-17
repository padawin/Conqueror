#include <stdio.h>
#include "human.h"
#include "../../utils.h"

int human_select_cell_to_leave(s_player *p, struct s_cell **player_cells, int nb_cells)
{
	char command[30];

	get_line("Command:", command, sizeof(command));

	printf("Typed command: %s", command);
	// list player cells
	// prompt cell to leave
	/*
	 * Command examples:
	 * cells
	 * neighbours #
	 * leave #
	 */
	return 1;
}
