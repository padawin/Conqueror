#include <stdlib.h>
#include "entity/board.h"
#include "game.h"

int main()
{
	s_board b;
	int nb_players_max;
	s_player *players;

	nb_players_max = game_select_map(&b);

	players = calloc((size_t) nb_players_max, sizeof(s_player));
	game_select_players(&b, players, nb_players_max);
	game_start(&b);

	free_board(&b);
	free(players);
	return EXIT_SUCCESS;
}
