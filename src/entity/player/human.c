#include <stdlib.h>
#include "human.h"
#include "../../ui.h"

int human_select_cell_to_leave(s_player *p, struct s_cell **player_cells, int nb_cells)
{
	int command_size = 30;
	char command[command_size];

	ui_list_cells(player_cells, nb_cells);

	ui_prompt_command(command, (size_t) command_size);

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
