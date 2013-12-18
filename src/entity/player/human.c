#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
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
	int command_size, choosen_cell;

	command_size = 30;
	char command[command_size];

	choosen_cell = -1;

	do {
		ui_prompt_command(command, (size_t) command_size);

		if (check_command(command, "cells", 1)) {
			ui_list_cells(player_cells, nb_cells);
		}
		else if (check_command(command, "neighbours ", 0)) {
			long int cell;
			char *cell_str, *endptr;

			cell_str = strstr(command, " ");
			cell = strtol(cell_str, &endptr, 10);

			if ((errno == ERANGE && (cell == LONG_MAX || cell == LONG_MIN))
				|| (errno != 0 && cell == 0)
				// nondigits found after the digits
				|| (*endptr != '\0' && endptr != cell_str)
			) {
				ui_error("Invalid cell ID value");
			}
			else if (endptr == cell_str)
				ui_error("No cell ID found");
			else
				printf("Cell: %d\n", (int) cell);
		}
		// list player cells
		// prompt cell to leave
		/*
		 * Command examples:
		 * cells
		 * neighbours #
		 * leave #
		 */
	} while (choosen_cell == -1);

	return choosen_cell;
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
