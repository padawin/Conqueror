#include <stdlib.h>
#include <string.h>
#include "human.h"
#include "../../ui.h"

short check_command(const char *typed, const char *command, short strict);

/**
 * Function to ask the player to choose a cell to play.
 * In this step, the player must be able to list his cells, list a cell's
 * neighbours and choose a cell to play.
 *
 * Commands:
 * cells: List the player's cells
 * neighbours #: List the neighbours cells of the cell having as ID #. The cell
 * 		# Must belong to the player
 * cell #: Select the cell # to play. The cell # must belong to the player.
 */
int human_select_cell_to_leave(s_player *p, struct s_cell **player_cells, int nb_cells)
{
	int command_size = 30;
	char command[command_size];

	ui_prompt_command(command, (size_t) command_size);

	if (check_command(command, "cells", 1)) {
		ui_list_cells(player_cells, nb_cells);
	}
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

/**
 * Checks if a typed command match the provided command.
 * Returns 1 if the typed command is correct, 0 else.
 */
short check_command(const char *typed, const char *command, short strict)
{
	char *result;
	int position;

	// Find command in type
	result = strstr(typed, command);
	if (result == NULL) {
		return 0;
	}

	position = (int) (result - typed);

	if (strict && strlen(typed) != strlen(command)) {
		return 0;
	}

	return position == 0;
}
