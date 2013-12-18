#ifndef S_BOARD
#define S_BOARD

#include "cell.h"
#include "player.h"

typedef struct {
	int nb_cells;
	int nb_players;
	int nb_total_players;
	s_player **players;
	struct s_cell *cells;
} s_board;

int init_board(s_board *b, int nb_cells, int nb_players);
void free_board(s_board *b);
int board_add_player(s_board *b, s_player * p);
int board_get_player_cells(s_board *b, struct s_player *p, struct s_cell **player_cells);

#endif
