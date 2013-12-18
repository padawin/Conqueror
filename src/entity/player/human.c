#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include "human.h"
#include "../../ui.h"

short _check_command(const char *typed, const char *command, short strict);
short _extract_cell_id(const char *command, long int *cell);

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
int human_select_cell_to_leave(struct s_cell **player_cells, int nb_cells)
{
	int command_size, choosen_cell;

	command_size = 30;
	char command[command_size];

	choosen_cell = -1;

	do {
		ui_prompt("Command: ", command, (size_t) command_size);

		if (_check_command(command, "cells", 1)) {
			ui_list_cells(player_cells, nb_cells);
		}
		else if (_check_command(command, "neighbours ", 0)) {
			long int cell;
			short result;

			result = _extract_cell_id(command, &cell);
			if (!result)
				continue;

			// check if the selected cell belong to the player's cells
			int c;
			for (c = 0; c < nb_cells && player_cells[c]->id != (int) cell; c++);

			if (c == nb_cells) {
				char error[64];
				sprintf(error, "The cell %ld does not exist or does not belong to you", cell);
				ui_error(error);
				continue;
			}

			ui_list_cells(player_cells[c]->neighbours, player_cells[c]->nb_neighbours);
		}
	} while (choosen_cell == -1);

	return choosen_cell;
}

/**
 * Checks if a typed command match the provided command.
 * Returns 1 if the typed command is correct, 0 else.
 */
short _check_command(const char *typed, const char *command, short strict)
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

/**
 * From a typed command, extract a cell ID, which must be after the first space.
 */
short _extract_cell_id(const char *command, long int *cell)
{
	char *cell_str, *endptr;

	cell_str = strstr(command, " ");
	*cell = strtol(cell_str, &endptr, 10);

	if ((errno == ERANGE && (*cell == LONG_MAX || *cell == LONG_MIN))
		|| (errno != 0 && *cell == 0)
		// nondigits found after the digits
		|| (*endptr != '\0' && endptr != cell_str)
	) {
		ui_error("Invalid cell ID value");
		return 0;
	}
	else if (endptr == cell_str) {
		ui_error("No cell ID found");
		return 0;
	}

	return 1;
}
