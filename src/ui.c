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
void ui_list_cells(s_cell **cells, int nb_cells)
{
	int c;

	for (c = 0; c < nb_cells; c++) {
		printf("Cell %d: %d pawns\n", cells[c]->id, cells[c]->nb_pawns);
	}
}

/**
 * Function to ask the user to type a command
 */
void ui_prompt_command(char *command, size_t command_size)
{
	get_line("Command: ", command, command_size);
}
