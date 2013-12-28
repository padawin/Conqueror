#ifndef S_CELL
#define S_CELL

struct s_cell;

#include "player.h"

#define ERROR_MAX_NEIGHBOURS_REACHED -1

typedef struct s_cell {
	int id;
	struct s_player *owner;
	int nb_pawns;
	int nb_neighbours;
	int nb_max_neighbours;
	struct s_cell **neighbours;
} s_cell;

int init_cell(s_cell *c, const int id, const int nb_cells);
void free_cell(s_cell *c);
void cell_set_owner(s_cell *c, struct s_player *owner);
void cell_set_nb_pawns(s_cell *c, const int nb_pawns);
int cell_add_neighbour(s_cell *c, struct s_cell *neighbour);

#endif
