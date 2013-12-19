#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include "human.h"
#include "../../ui.h"

short _check_command(const char *typed, const char *command, short strict);
short _extract_cell_id(const char *command, long int *cell);
int _get_cell_from_command(const char *command, struct s_cell **player_cells, int nb_cells);

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

	ui_info("Choose a cell to leave");

	do {
		ui_prompt("Command: ", command, (size_t) command_size);

		if (_check_command(command, "cells", 1)) {
			ui_list_cells(player_cells, nb_cells, CELLS_LIST_MIN);
		}
		else if (_check_command(command, "neighbours ", 0)) {
			// c must be a player's cell
			int c = _get_cell_from_command(command, player_cells, nb_cells);

			if (c == -1)
				continue;

			ui_list_cells(player_cells[c]->neighbours, player_cells[c]->nb_neighbours, CELLS_LIST_FULL);
		}
		else if (_check_command(command, "cell ", 0)) {
			// c must be a player's cell
			int c = _get_cell_from_command(command, player_cells, nb_cells);

			if (c == -1)
				continue;

			choosen_cell = c;
		}
	} while (choosen_cell == -1);

	return choosen_cell;
}

struct s_cell *human_select_cell_to_go_to(struct s_cell *src_cell)
{
	int command_size;
	struct s_cell *choosen_cell;

	command_size = 30;
	char command[command_size];

	choosen_cell = NULL;

	ui_info("Choose a cell to go to");

	do {
		ui_prompt("Command: ", command, (size_t) command_size);

		if (_check_command(command, "neighbours", 1)) {
			ui_list_cells(src_cell->neighbours, src_cell->nb_neighbours, CELLS_LIST_FULL);
		}
		else if (_check_command(command, "cell ", 0)) {
			// c must be a player's cell
			int c = _get_cell_from_command(command, src_cell->neighbours, src_cell->nb_neighbours);

			if (c == -1)
				continue;

			choosen_cell = src_cell->neighbours[c];
		}
	} while (choosen_cell == NULL);

	return choosen_cell;
}

int human_select_nb_pawns(struct s_cell *src_cell)
{
	char nb_pawns_str[4], msg[64];
	char *endptr;
	long nb_pawns;
	int max_pawns_number;

	nb_pawns = -1;
	// there must be at least one pawn on the cell
	max_pawns_number = src_cell->nb_pawns - 1;

	sprintf(msg, "Choose a number of pawns to move between 1 and %d", max_pawns_number);
	ui_info(msg);

	do {
		ui_prompt("Number of pawns: ", nb_pawns_str, (size_t) 4);
		nb_pawns = strtol(nb_pawns_str, &endptr, 10);

		if ((errno == ERANGE && (nb_pawns == LONG_MAX || nb_pawns == LONG_MIN))
			|| (errno != 0 && nb_pawns == 0)
			// nondigits found after the digits
			|| (*endptr != '\0' && endptr != nb_pawns_str)
			|| nb_pawns < 1
			|| nb_pawns > max_pawns_number
		) {
			ui_error("Invalid number of pawns");
			nb_pawns = -1;
			continue;
		}
		else if (endptr == nb_pawns_str) {
			ui_error("No value found");
			nb_pawns = -1;
			continue;
		}

	} while (nb_pawns == -1);

	return (int) nb_pawns;
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

int _get_cell_from_command(const char *command, struct s_cell **player_cells, int nb_cells)
{
	long int cell;
	short result;

	result = _extract_cell_id(command, &cell);
	if (!result)
		return -1;

	// check if the selected cell belong to the player's cells
	int c;
	for (c = 0; c < nb_cells && player_cells[c]->id != (int) cell; c++);

	if (c == nb_cells) {
		char error[64];
		sprintf(error, "The cell %ld is not valid", cell);
		ui_error(error);
		return -1;
	}

	return c;
}
