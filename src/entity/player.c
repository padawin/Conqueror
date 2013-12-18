#include <stdlib.h>
#include "player.h"
#include "player/ai.h"
#include "player/human.h"

int init_player(
	s_player *p,
	const char *name,
	const short is_human,
	const int strategy,
	const int nb_pawns,
	const int nb_total_cells
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

	// @XXX: Might cause some issues here
	p->owned_cells = calloc((size_t) nb_total_cells, sizeof(s_cell*));

	return 1;
}

void free_player(s_player *p)
{
	free(p->owned_cells);
}

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
