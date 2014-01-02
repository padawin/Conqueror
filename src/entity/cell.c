#include <stdlib.h>
#include "cell.h"

int init_cell(s_cell *c, const int id, const uint8_t nb_cells)
{
	c->id = id;
	c->owner = NULL;
	c->nb_pawns = 0;
	c->nb_neighbours = 0;
	c->nb_max_neighbours = (uint8_t) (nb_cells - 1);
	// @XXX: Might cause some issues here
	c->neighbours = calloc((size_t) c->nb_max_neighbours, sizeof(s_cell*));

	return 1;
}

void free_cell(s_cell *c)
{
	free(c->neighbours);
}

void cell_set_owner(s_cell *c, struct s_player *owner)
{
	c->owner = owner;
}

void cell_set_nb_pawns(s_cell *c, const uint16_t nb_pawns)
{
	c->nb_pawns = nb_pawns;
}

int cell_add_neighbour(s_cell *c, struct s_cell *neighbour)
{
	if (c->nb_neighbours == c->nb_max_neighbours)
		return ERROR_MAX_NEIGHBOURS_REACHED;

	c->neighbours[c->nb_neighbours] = neighbour;
	c->nb_neighbours++;

	return 1;
}
