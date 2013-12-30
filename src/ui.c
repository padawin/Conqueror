#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "utils.h"

/**
 * Bunch of functions to display informations to the user.
 *
 * For the moment, displays on STDOUT
 */

/**
 * Function to display a list of cells with their informations (number of pawns
 * for now)
 */
void ui_list_cells(s_cell **cells, int nb_cells, short full_display)
{
	int c;

	for (c = 0; c < nb_cells; c++) {
		if (full_display == CELLS_LIST_FULL)
			printf(
				"Cell %d: owned by %s with %d pawns\n",
				cells[c]->id,
				cells[c]->owner == NULL ? "nobody" : cells[c]->owner->name,
				cells[c]->nb_pawns
			);
		else
			printf("Cell %d: %d pawns\n", cells[c]->id, cells[c]->nb_pawns);
	}
}

/**
 * Function to ask the user to type a command
 */
void ui_prompt(const char *prompt, char *command, size_t command_size)
{
	utils_get_line(prompt, command, command_size);
}

/**
 * Displays an error message
 */
void ui_error(const char *msg)
{
	fprintf(stderr, "%s\n", msg);
}

/**
 * Display an information message
 */
void ui_info(const char *msg)
{
	printf("%s\n", msg);
}
