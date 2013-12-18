#ifndef PLAYER_HUMAN
#define PLAYER_HUMAN

#include "../player.h"
#include "../cell.h"

int human_select_cell_to_leave(struct s_cell **player_cells, int nb_cells);
struct s_cell *human_select_cell_to_go_to(struct s_cell *src_cell);
int human_select_nb_pawns(struct s_cell *src_cell);

#endif
