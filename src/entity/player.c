#include "player.h"

int init_player(
	s_player *p,
	const char *name,
	const short is_human,
	const int strategy,
	const int nb_pawns,
	const int nb_total_cells
)
{
	p->name = name;

	return 1;
}
