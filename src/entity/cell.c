#include <stdlib.h>
#include "cell.h"

/**
 * Function to initialise a cell.
 *
 * @param s_cell *c The cell to initialise
 * @param const int id The cell ID
 * @param const int nb_cells The board's number of cells. Used to devine the
 * 		cell's max number of neigbours.
 *
 * @return int 1 if the cell is correctly initialised,
 * 		ERROR_INIT_INVALID_CELLS_NUMBER if the number of cells is < 1
 */
int init_cell(s_cell *c, const int id, const uint8_t nb_cells)
{
	if (nb_cells < 1) {
		return ERROR_INIT_INVALID_CELLS_NUMBER;
	}

	c->id = id;
	c->owner = NULL;
	c->nb_pawns = 0;
	c->nb_neighbours = 0;
	c->nb_max_neighbours = (uint8_t) (nb_cells - 1);

	c->neighbours = calloc((size_t) c->nb_max_neighbours, sizeof(s_cell*));

	return 1;
}

/**
 * Function to free the memory used by a cell. Will free the cell's neighbours,
 * which have been allocated with a calloc.
 *
 * @param s_cell *c The cell to free
 *
 * @return void
 */
void free_cell(s_cell *c)
{
	free(c->neighbours);
}

/**
 * Set the cell owner
 *
 * @param s_cell *c
 * @param struct s_player *owner
 *
 * @return void
 */
void cell_set_owner(s_cell *c, struct s_player *owner)
{
	c->owner = owner;
}

/**
 * Set the cell's number of pawns
 *
 * @param s_cell *c
 * @param const int nb_pawns
 *
 * @return void
 */
void cell_set_nb_pawns(s_cell *c, const uint16_t nb_pawns)
{
	c->nb_pawns = nb_pawns;
}

/**
 * Add a neighbour to a cell.
 *
 * @param s_cell *c
 * @param struct s_cell *neighbour
 *
 * @return int 1 if the neighbour is added, ERROR_MAX_NEIGHBOURS_REACHED if the
 * 		cell cannot have more neighbours.
 */
int cell_add_neighbour(s_cell *c, struct s_cell *neighbour)
{
	if (c->nb_neighbours == c->nb_max_neighbours)
		return ERROR_MAX_NEIGHBOURS_REACHED;

	c->neighbours[c->nb_neighbours] = neighbour;
	c->nb_neighbours++;

	return 1;
}
