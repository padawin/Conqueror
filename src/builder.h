#ifndef S_BUILDER
#define S_BUILDER

#include <stdint.h>
#include "entity/board.h"

#define BUILDER_SMALL_BOARD 1
#define BUILDER_MEDIUM_BOARD 2
#define BUILDER_LARGE_BOARD 3

#define BUILDER_BOARD_CREATED 1
#define BUILDER_ERROR_INVALID_BOARD_SIZE -1

#define SMALL_BOARD_NB_CELLS 4

int builder_create_board(int size, s_board *b, uint8_t *nb_max_players, uint16_t *pawns_per_player);

#endif
