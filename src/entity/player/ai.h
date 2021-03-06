#ifndef PLAYER_AI
#define PLAYER_AI

#include <stdint.h>
#include "../player.h"
#include "../cell.h"

int ai_select_cell_to_leave(struct s_cell **player_cells, int nb_cells);
struct s_cell *ai_select_cell_to_go_to(struct s_cell *src_cell);
uint16_t ai_select_nb_pawns(struct s_cell *src_cell);

#endif
