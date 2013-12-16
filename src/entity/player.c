#include "player.h"

int init_player(s_player *p, const char *name)
{
	p->name = name;

	return 1;
}
