#include <stdlib.h>
#include <stdint.h>
#include "entity/board.h"
#include "game.h"

int main()
{
	s_board b;
	uint8_t nb_players_max;
	uint16_t nb_pawns_per_player;
	s_player *players;

	game_select_map(&b, &nb_players_max, &nb_pawns_per_player);

	players = calloc((size_t) nb_players_max, sizeof(s_player));
	game_select_players(&b, players, nb_players_max, nb_pawns_per_player);
	game_start(&b);

	free_board(&b);
	free(players);
	return EXIT_SUCCESS;
}
