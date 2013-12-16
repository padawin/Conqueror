#ifndef S_CELL
#define S_CELL

#include "player.h"

struct s_cell;

typedef struct {
	int id;
	struct s_player *owner;
	int nb_pawns;
	struct s_cell* neighbours;
} s_cell;

#endif
