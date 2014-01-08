#ifndef S_BUILDER
#define S_BUILDER

#include <stdint.h>
#include "entity/board.h"

#define SMALL_BOARD_NB_CELLS 4

void builder_create_small_board(s_board *b, uint8_t *nb_max_players, uint16_t *pawns_per_player);

#endif
