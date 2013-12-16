#ifndef S_PLAYER
#define S_PLAYER

struct s_player;

#include "cell.h"

typedef struct {
	const char *name;
	short is_human;
	int strategy;
	int nb_pawns;
	int nb_cells;
	struct s_cell **owned_cells;
} s_player;

int init_player(s_player *p, const char *name);

#endif
