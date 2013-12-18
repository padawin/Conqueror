#ifndef S_PLAYER
#define S_PLAYER

struct s_player;

#include "cell.h"

#define STRATEGY_NONE 0
#define STRATEGY_SPREAD 1
#define STRATEGY_OFFENCE 2

// Invalid strategy provided
#define ERROR_INIT_EMPTY_NAME -1
#define ERROR_INIT_STRATEGY -2
#define ERROR_INIT_NB_PAWNS -3

typedef struct s_player {
	int id;
	const char *name;
	short is_human;
	int strategy;
	int nb_pawns;
	int nb_cells;
	struct s_cell **owned_cells;
} s_player;

int init_player(
	s_player *p,
	const char *name,
	const short is_human,
	const int strategy,
	const int nb_pawns,
	const int nb_total_cells
);
void free_player(s_player *p);
int player_select_cell_to_leave(s_player *p, struct s_cell **player_cells, int nb_cells);
struct s_cell *player_select_cell_to_go_to(s_player *p, struct s_cell *src_cell);
int player_select_nb_pawns(s_player *p, struct s_cell *src_cell);

#endif
