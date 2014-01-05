#ifndef S_PLAYER
#define S_PLAYER

struct s_player;

#include <stdint.h>
#include "cell.h"

#define STRATEGY_NONE 0
#define STRATEGY_SPREAD 1
#define STRATEGY_OFFENCE 2

#define PLAYER_ERROR_INIT_PLAYER_EMPTY_NAME -1
#define PLAYER_ERROR_INIT_PLAYER_STRATEGY -2
#define PLAYER_ERROR_INIT_PLAYER_NB_PAWNS -3
#define INIT_PLAYER_OK 1

#define PLAYER_ERROR_MOVE_CELLS_NOT_NEIGHBOURS -1

#define NO_FIGHT 0
#define FIGHT_WON 1
#define FIGHT_LOST 2
#define FIGHT_DRAW 3

typedef struct s_player {
	const char *name;
	int id;
	uint8_t nb_cells;
	uint16_t nb_pawns;
	int strategy;
	int is_human;
} s_player;

int init_player(
	s_player *p,
	const char *name,
	const short is_human,
	const int strategy,
	const uint16_t nb_pawns
);
int player_select_cell_to_leave(s_player *p, struct s_cell **player_cells, int nb_cells);
struct s_cell *player_select_cell_to_go_to(s_player *p, struct s_cell *src_cell);
uint16_t player_select_nb_pawns(s_player *p, struct s_cell *src_cell);
short player_move_to_cell(s_player *p, uint16_t nb_pawns, struct s_cell *src_cell, struct s_cell *dst_cell);

#endif
