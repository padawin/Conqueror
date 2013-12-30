#include <stdlib.h>
#include <stdint.h>
#include "cell.h"
#include "player.h"
#include "player/ai.h"
#include "player/human.h"

/**
 * Function to initialize a player
 *
 * @param s_player *p THe player
 * @param const char *name The player's name
 * @param const short is_human A flag to know if the player is human or an AI
 * @param const int strategy If the player is an AI, this defines the game
 * 		strategy he must adopt. Not implemented yet
 * @param const int nb_pawns The player's initial number of pawns
 *
 * @return int 1 if the player is correctly initialized,
 * 		ERROR_INIT_EMPTY_NAME if the provided name is empty, ERROR_INIT_STRATEGY
 * 		if the strategy is incorrect, ERROR_INIT_NB_PAWNS if the number of pawns
 * 		is < 1
 *
 */
int init_player(
	s_player *p,
	const char *name,
	const short is_human,
	const int strategy,
	const uint16_t nb_pawns
)
{
	if (name == NULL)
		return ERROR_INIT_EMPTY_NAME;

	p->name = name;

	if (strategy != STRATEGY_NONE && strategy != STRATEGY_SPREAD && strategy != STRATEGY_OFFENCE)
		return ERROR_INIT_STRATEGY;

	p->strategy = strategy;

	if (nb_pawns < 1)
		return ERROR_INIT_NB_PAWNS;

	p->nb_pawns = nb_pawns;
	p->is_human = is_human;
	p->nb_cells = 0;

	return 1;
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
