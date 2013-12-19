#include <stdlib.h>
#include "game.h"
#include "entity/board.h"
#include "entity/player.h"
#include "entity/cell.h"
#include "utils.h"
#include "ui.h"

#define NO_FIGHT 0
#define FIGHT_WON 1
#define FIGHT_LOST 2
#define FIGHT_DRAW 3

int _select_starting_player(int nb_players);
short _fight(struct s_cell *cell, int nb_pawns);

s_player *game_start(s_board *b)
{
	int current_player_index, player_nb_cells, cell_to_leave, nb_pawns_to_move, p;
	s_player *winner, *current_player;
	struct s_cell **player_cells;
	struct s_cell *cell_to_goto;

	winner = NULL;
	player_cells = calloc((size_t) b->nb_cells, sizeof(struct s_cell *));

	// select starting player
	current_player_index = _select_starting_player(b->nb_players);

	do {
		current_player = b->players[current_player_index];

		player_nb_cells = board_get_player_cells(b, current_player, player_cells);

		// Here the player can list his cells, see the neighbours of any of his
		// cells, select a cell to leave
		// cell_to_leave = cell index in player_cells
		cell_to_leave = player_select_cell_to_leave(current_player, player_cells, player_nb_cells);

		// Select a neighbours cell of cell_to_leave to go there
		// cell_to_goto = cell struct of the cell to go to
		cell_to_goto = player_select_cell_to_go_to(current_player, player_cells[cell_to_leave]);

		// Select the number of pawns to move
		nb_pawns_to_move = player_select_nb_pawns(current_player, player_cells[cell_to_leave]);

		player_cells[cell_to_leave]->nb_pawns -= nb_pawns_to_move;
		if (cell_to_goto->owner == NULL || cell_to_goto->owner->id == current_player->id) {
			if (cell_to_goto->owner == NULL) {
				cell_to_goto->owner = current_player;
				current_player->nb_cells++;
			}
			cell_to_goto->nb_pawns += nb_pawns_to_move;
		}
		else {
			ui_info("You're engaging a fight");

			// fight
			short fight_result;
			fight_result = _fight(cell_to_goto, nb_pawns_to_move);

			if (fight_result == FIGHT_LOST) {
				ui_info("You lost the fight");
				current_player->nb_pawns -= nb_pawns_to_move;
			}
			else if (fight_result == FIGHT_WON) {
				ui_info("You won the fight");
				cell_to_goto->owner = current_player;
				cell_to_goto->nb_pawns = nb_pawns_to_move;
				current_player->nb_cells++;

				// Check if the current player is the winner of the game
				for (
					p = 0;
					p < b->nb_players
					&& (
						b->players[p]->nb_cells == 0
						|| b->players[p]->id == current_player->id
					);
					p++
				);

				if (p == nb_players) {
					winner = current_player;
				}
			}
		}

		if (winner == NULL) {
			if (current_player->nb_pawns == 0) {
				ui_info("You cannot play anymore, all your pawns are dead");
			}
			else if (current_player->nb_pawns == current_player->nb_cells) {
				ui_info("You cannot play anymore, all your cells contain one pawn");
			}

			// Loop to skip players who cannot play anymore
			// @TODO check if next player is the current one, which means no player won
			// In this case, the winner is the one possessing the most cells
			do {
				current_player_index = (current_player_index + 1) % b->nb_players;
			} while (
				b->players[current_player_index]->nb_pawns == 0
				|| b->players[current_player_index]->nb_pawns == b->players[current_player_index]->nb_cells
			);
		}
	} while (winner == NULL);

	return winner;
}

int _select_starting_player(int nb_players)
{
	return (int) utils_get_random_int(0, (unsigned int) nb_players);
}

/**
 * The player tries to dominate the cell with nb_pawns.
 *
 */
short _fight(struct s_cell *cell, int nb_pawns)
{
	if (cell->nb_pawns > nb_pawns) {
		return FIGHT_LOST;
	}
	else if (nb_pawns > cell->nb_pawns) {
		return FIGHT_WON;
	}
	else {
		return FIGHT_DRAW;
	}
}
