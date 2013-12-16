#ifndef S_CELL
#define S_CELL

#include "player.h"

struct s_cell;

typedef struct {
	int id;
	struct s_player *owner;
	int nb_pawns;
	int nb_neighbours;
	int nb_max_neighbours;
	struct s_cell **neighbours;
} s_cell;

#endif
