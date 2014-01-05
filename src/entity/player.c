#include <stdlib.h>
#include <stdint.h>
#include "cell.h"
#include "player.h"
#include "player/ai.h"
#include "player/human.h"

short _fight(int nb_pawns, struct s_cell *cell);

/**
 * Function to initialise a player
 *
 * @param s_player *p The player
 * @param const char *name The player's name
 * @param const short is_human A flag to know if the player is human or an AI
 * @param const int strategy If the player is an AI, this defines the game
 * 		strategy he must adopt. Not implemented yet
 * @param const int nb_pawns The player's initial number of pawns
 *
 * @return int 1 if the player is correctly initialised,
 * 		ERROR_INIT_PLAYER_EMPTY_NAME if the provided name is empty,
 * 		ERROR_INIT_PLAYER_STRATEGY if the strategy is incorrect,
 * 		ERROR_INIT_PLAYER_NB_PAWNS if the number of pawns is < 1.
 */
int init_player(
	s_player *p,
	const int id,
	const char *name,
	const short is_human,
	const int strategy,
	const uint16_t nb_pawns
)
{
	if (name[0] == '\0')
		return PLAYER_ERROR_INIT_PLAYER_EMPTY_NAME;

	if (
		(is_human && strategy != STRATEGY_NONE)
		|| (!is_human && strategy != STRATEGY_SPREAD && strategy != STRATEGY_OFFENCE)
	)
		return PLAYER_ERROR_INIT_PLAYER_STRATEGY;

	if (nb_pawns < 1)
		return PLAYER_ERROR_INIT_PLAYER_NB_PAWNS;

	p->nb_pawns = nb_pawns;
	p->strategy = strategy;
	p->id = id;
	p->name = name;
	p->is_human = is_human;
	p->nb_cells = 0;

	return INIT_PLAYER_OK;
}

/**
 * Wrapper function to ask the player to choose a cell where some pawns will
 * move from. Depending on if the player is human or AI, a specific function
 * will be called.
 *
 * @param s_player *p The player
 * @param struct s_cell **player_cells The cells belonging to this player
 * @param int nb_cells The number of cells the player owns
 *
 * @return int the id of the cell the player will leave
 */
int player_select_cell_to_leave(s_player *p, struct s_cell **player_cells, int nb_cells)
{
	int cell_id;

	if (p->is_human) {
		cell_id = human_select_cell_to_leave(player_cells, nb_cells);
	}
	else {
		cell_id = ai_select_cell_to_leave(player_cells, nb_cells);
	}
	return cell_id;
}

/**
 * Wrapper function to ask the player to choose a cell where some pawns will
 * move to. Depending on if the player is human or AI, a specific function
 * will be called.
 *
 * @param s_player *p The player
 * @param struct s_cell *src_cell The cell the pawns come from. The destination
 * 		cell must be a neighbour of the source cell.
 *
 * @return int the id of the cell the player will try to go to.
 */
struct s_cell *player_select_cell_to_go_to(s_player *p, struct s_cell *src_cell)
{
	struct s_cell *dst_cell;

	if (p->is_human) {
		dst_cell = human_select_cell_to_go_to(src_cell);
	}
	else {
		dst_cell = ai_select_cell_to_go_to(src_cell);
	}
	return dst_cell;
}

/**
 * Wrapper function to ask the player to choose a number of pawns to move.
 * Depending on if the player is human or AI, a specific function will be called
 *
 * @param s_player *p The player
 * @param struct s_cell *src_cell The cell the player will leave
 *
 * @return uint16_t The number of pawns the player will move
 */
uint16_t player_select_nb_pawns(s_player *p, struct s_cell *src_cell)
{
	uint16_t nb_pawns;

	if (p->is_human) {
		nb_pawns = human_select_nb_pawns(src_cell);
	}
	else {
		nb_pawns = ai_select_nb_pawns(src_cell);
	}
	return nb_pawns;
}

/**
 * Move nb_pawns of the player p from the cell src_cell to the cell dst_cell
 *
 * Check if dst and src are neighbours
 * error if not
 * check dst owner
 * if owner == p or null
 * 		move pawns
 * else
 * 		fight
 * if not draw (no move)
 * 		remove pawns from src.
 *
 * return move result (nofight, draw, win, lost)
 */
short player_move_to_cell(s_player *p, uint16_t nb_pawns, struct s_cell *src_cell, struct s_cell *dst_cell)
{
	short result;

	if (!cell_are_neighbours(src_cell, dst_cell)) {
		return PLAYER_ERROR_MOVE_CELLS_NOT_NEIGHBOURS;
	}

	if (dst_cell->owner != NULL && dst_cell->owner->id != p->id) {
		// fight
		result = _fight(nb_pawns, dst_cell);
	}
	else {
		if (dst_cell->owner == NULL) {
			dst_cell->owner = p;
			p->nb_cells++;
		}
		dst_cell->nb_pawns = (uint16_t) (dst_cell->nb_pawns + nb_pawns);
		result = NO_FIGHT;
	}

	if (result != FIGHT_DRAW) {
		src_cell->nb_pawns = (uint16_t) (src_cell->nb_pawns - nb_pawns);

		if (result == FIGHT_LOST) {
			p->nb_pawns = (uint16_t) (p->nb_pawns - nb_pawns);
		}
		else if (result == FIGHT_WON) {
			// update opponent pawns and cells number
			dst_cell->owner->nb_pawns = (uint16_t) (dst_cell->owner->nb_pawns - dst_cell->nb_pawns);
			dst_cell->owner->nb_cells--;

			// update cell owner
			dst_cell->owner = p;
			dst_cell->nb_pawns = nb_pawns;
			p->nb_cells = (uint8_t) (p->nb_cells + 1);
		}
	}

	return result;
}

/**
 * The player tries to dominate the cell with nb_pawns.
 *
 * @param int nb_pawns The number of pawns the current player wants to move to
 * 		the cell
 * @param s_cell *cell The cell where the fight is happening
 *
 * @return sort FIGHT_WON if the current player won the fight, FIGHT_DRAW if
 * 		nobody won, FIGHT_LOST if the current player lost the fight.
 */
short _fight(int nb_pawns, s_cell *cell)
{
	short result;

	if (cell->nb_pawns > nb_pawns)
		result = FIGHT_LOST;
	else if (nb_pawns > cell->nb_pawns)
		result = FIGHT_WON;
	else
		result = FIGHT_DRAW;

	return result;
}
