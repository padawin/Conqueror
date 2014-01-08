#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "game.h"
#include "entity/board.h"
#include "entity/player.h"
#include "entity/cell.h"
#include "builder.h"
#include "utils.h"
#include "ui.h"

int _select_starting_player(int nb_players);
short _set_next_player_index(s_board *b, int *current_player_index, s_player *current_player, s_player *winner);

/**
 * Select a map and returns the max number of players of the map
 */
int game_select_map(s_board *b)
{
	// @TODO ask for size
	// @TODO build map from size
	// @TODO the number of pawns per player should be map dependant
	return builder_create_small_board(b);
}

/**
 * Init the players, between 2 and nb_max_players
 *
 * @return int the actual number of players
 */
void game_select_players(s_board *b, s_player *players, int nb_max_players)
{
	int p;
	const char *names[4] = {"Player1", "player2", "player3", "player4"};
	for (p = 0; p < nb_max_players; p++) {
		init_player(&players[p], 1, names[p], 1, STRATEGY_NONE, 8);
		board_add_player(b, &players[p]);
		// @TODO loop on each player, ask if the player is an AI or a human
		// @TODO	ask for the player name and the strategy if AI
	}
}

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
	short result;
	s_player *winner, *current_player;
	s_cell **player_cells;
	s_cell *cell_to_goto;
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

		// @TODO move in player with an event
		if (cell_to_goto->owner != NULL && current_player->id != cell_to_goto->owner->id)
			ui_info("You're engaging a fight");

		result = player_move_to_cell(
			current_player,
			nb_pawns_to_move,
			player_cells[cell_to_leave],
			cell_to_goto
		);

		if (result == FIGHT_LOST) {
			ui_info("You lost the fight");
		}
		else if (result == FIGHT_WON) {
			ui_info("You won the fight");
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
