#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
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
short _fight(s_player *current_player, struct s_cell *cell, uint16_t nb_pawns);
short _set_next_player_index(s_board *b, int *current_player_index, s_player *current_player, s_player *winner);

/**
 * Game main loop
 *
 * @param s_board *b The game's board
 *
 * @return s_player* Pointer to the game's winner
 */
s_player *game_start(s_board *b)
{
	int current_player_index, player_nb_cells, cell_to_leave;
	uint16_t nb_pawns_to_move;
	short fight_result;
	s_player *winner, *current_player;
	struct s_cell **player_cells;
	struct s_cell *cell_to_goto;
	char next_player_msg[64];

	winner = NULL;
	player_cells = calloc((size_t) b->nb_cells, sizeof(struct s_cell *));

	// select starting player
	current_player_index = _select_starting_player(b->nb_players);

	do {
		current_player = b->players[current_player_index];

		sprintf(next_player_msg, "%s's turn to play", current_player->name);
		ui_info(next_player_msg);
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

		if (cell_to_goto->owner == NULL || cell_to_goto->owner->id == current_player->id) {
			if (cell_to_goto->owner == NULL) {
				cell_to_goto->owner = current_player;
				current_player->nb_cells++;
			}
// @XXX
			cell_to_goto->nb_pawns = (uint16_t) (cell_to_goto->nb_pawns + nb_pawns_to_move);
			fight_result = NO_FIGHT;
		}
		else {
			ui_info("You're engaging a fight");

			// fight
			fight_result = _fight(current_player, cell_to_goto, nb_pawns_to_move);
		}

		if (fight_result != FIGHT_DRAW) {
// @XXX
			player_cells[cell_to_leave]->nb_pawns = (uint16_t) (player_cells[cell_to_leave]->nb_pawns + nb_pawns_to_move);
		}

		if (current_player->nb_pawns == current_player->nb_cells) {
			ui_info("You cannot play anymore, all your cells contain one pawn");
		}

		// Define the next player. If no next player is set, the function
		// returns 0, this means a winner is found by draw (no player can
		// move anymore, the winner is the one having the largest number of
		// cells/remaining pawns)
		if (!_set_next_player_index(b, &current_player_index, current_player, winner)) {
			break;
		}
	} while (winner == NULL);

	return winner;
}

/**
 * Randomly select an integer between 0 (included) and the number of players
 * (excluded). This integer will be the index of the player who will play first.
 *
 * @param int nb_players
 *
 * @return int The index of the starting player
 */
int _select_starting_player(int nb_players)
{
	return (int) utils_get_random_int(0, (unsigned int) nb_players);
}

/**
 * This function selects the next player who must play.
 * The next player is the first who still has pawns and who has more pawns than
 * cells.
 * If all players are tested and the current player is reached again, that means
 * none can play so the current player is the game's winner.
 *
 * @param s_board *b The game's board
 * @param int *current_player_index The current player index in the players' list
 * @param s_player *current_player Pointer to the current player
 * @param s_player *winner Game's winner
 *
 * @return short 0 if there is no next player (which means a winner is found), 1
 * 		if a next player is found
 */
short _set_next_player_index(s_board *b, int *current_player_index, s_player *current_player, s_player *winner)
{
	int p;
	// Loop to skip players who cannot play anymore
	do {
		*current_player_index = (*current_player_index + 1) % b->nb_players;

		// There is no next player, the winner is the one owning the
		// largest number of cells
		if (b->players[*current_player_index]->id == current_player->id) {
			for (p = 0; p < b->nb_players; p++) {
				if (winner == NULL || b->players[p]->nb_cells > winner->nb_cells) {
					winner = b->players[p];
				}
			}
			return 0;
		}
	} while (
		b->players[*current_player_index]->nb_pawns == 0
		|| b->players[*current_player_index]->nb_pawns == b->players[*current_player_index]->nb_cells
	);

	return 1;
}

/**
 * The player tries to dominate the cell with nb_pawns.
 *
 * @param s_board *b The game's board
 * @param s_player *current_player The current player, who is starting a fight
 * @param struct s_cell *cell The cell where the fight is happening
 * @param int nb_pawns The number of pawns the current player wants to move to
 * 		the cell
 * @param s_player **winner The game winner
 *
 * @return short FIGHT_WON if current_player won the fight, FIGHT_DRAW if nobody
 * 		won, FIGHT_LOST if current_player lost the fight
 */
short _fight(s_player *current_player, struct s_cell *cell, uint16_t nb_pawns)
{
	short result;

	if (cell->nb_pawns > nb_pawns) {
		result = FIGHT_LOST;
	}
	else if (nb_pawns > cell->nb_pawns) {
		result = FIGHT_WON;
	}
	else {
		result = FIGHT_DRAW;
	}

	if (result == FIGHT_LOST) {
		ui_info("You lost the fight");
// @XXX
		current_player->nb_pawns = (uint16_t) (current_player->nb_pawns - nb_pawns);
	}
	else if (result == FIGHT_WON) {
		ui_info("You won the fight");
// @XXX
		cell->owner->nb_pawns = (uint16_t) (cell->owner->nb_pawns - cell->nb_pawns);
		cell->owner->nb_cells--;
		cell->owner = current_player;
		cell->nb_pawns = nb_pawns;
		current_player->nb_cells++;
	}

	return result;
}
