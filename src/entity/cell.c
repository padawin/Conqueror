#include <stdlib.h>
#include "cell.h"

/**
 * Function to initialise a cell.
 *
 * @param s_cell *c The cell to initialise
 * @param const int id The cell ID
 * @param const int nb_cells The board's number of cells. Used to devine the
 * 		cell's max number of neighbours.
 *
 * @return int 1 if the cell is correctly initialised,
 * 		ERROR_INIT_CELL_INVALID_CELLS_NUMBER if the number of cells is < 1
 */
int init_cell(s_cell *c, const int id, const uint8_t nb_cells)
{
	if (nb_cells < 1) {
		return ERROR_INIT_CELL_INVALID_CELLS_NUMBER;
	}

	c->id = id;
	c->owner = NULL;
	c->nb_pawns = 0;
	c->nb_neighbours = 0;
	c->nb_max_neighbours = (uint8_t) (nb_cells - 1);

	c->neighbours = calloc((size_t) c->nb_max_neighbours, sizeof(s_cell*));

	return INIT_CELL_OK;
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
	c->neighbours = NULL;
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
	owner->nb_cells = (uint8_t) (owner->nb_cells + 1);
}

/**
 * Set the cell's number of pawns
 *
 * @param s_cell *c
 * @param const int nb_pawns
 *
 * @return void
 */
int cell_set_nb_pawns(s_cell *c, const uint16_t nb_pawns)
{
	if (c->owner == NULL) {
		return CELL_ERROR_SET_PAWNS_NO_OWNER;
	}

	if (nb_pawns > c->owner->nb_pawns) {
		return CELL_ERROR_SET_PAWNS_NOT_ENOUGH_PAWNS;
	}

	c->nb_pawns = nb_pawns;
	return CELL_SET_PAWNS_OK;
}

/**
 * Add a neighbour to a cell.
 *
 * @param s_cell *c
 * @param struct s_cell *neighbour
 *
 * @return int CELL_ADD_NEIGHBOUR_OK if the neighbour is added,
 * 		ERROR_MAX_NEIGHBOURS_REACHED if the cell or the neighbour cannot have
 * 		more neighbours or ERROR_ALREADY_NEIGHBOUR if neighbour is already a
 * 		neighbour of c.
 */
int cell_add_neighbour(s_cell *c, s_cell *neighbour)
{
	if (
		c->nb_neighbours == c->nb_max_neighbours
		|| neighbour->nb_neighbours == neighbour->nb_max_neighbours
	)
		return CELL_ERROR_MAX_NEIGHBOURS_REACHED;

	if (cell_are_neighbours(c, neighbour)) {
		return CELL_ERROR_ALREADY_NEIGHBOUR;
	}

	c->neighbours[c->nb_neighbours++] = neighbour;
	neighbour->neighbours[neighbour->nb_neighbours++] = c;

	return CELL_ADD_NEIGHBOUR_OK;
}

/**
 * Check if two cells are neighbours.
 *
 * @param s_cell *c1
 * @param s_cell *c2
 *
 * @return 1 if the cells are neighbours, 0 else
 */
short cell_are_neighbours(s_cell *c1, s_cell *c2)
{
	int n;
	for (n = 0; n < c1->nb_neighbours && c1->neighbours[n]->id != c2->id; n++);

	return n < c1->nb_neighbours;
}
