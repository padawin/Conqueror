#ifndef S_CELL
#define S_CELL

struct s_cell;

#include <stdint.h>
#include "player.h"

#define ERROR_MAX_NEIGHBOURS_REACHED -1

typedef struct s_cell {
	struct s_player *owner;
	struct s_cell **neighbours;
	int id;
	uint16_t nb_pawns;
	uint8_t nb_neighbours;
	uint8_t nb_max_neighbours;
} s_cell;

int init_cell(s_cell *c, const int id, const uint8_t nb_cells);
void free_cell(s_cell *c);
void cell_set_owner(s_cell *c, struct s_player *owner);
void cell_set_nb_pawns(s_cell *c, const uint16_t nb_pawns);
int cell_add_neighbour(s_cell *c, struct s_cell *neighbour);

#endif
