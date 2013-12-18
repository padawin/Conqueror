#ifndef UI
#define UI

#include "entity/cell.h"

void ui_list_cells(s_cell **cells, int nb_cells);
void ui_prompt_command(char *command, size_t command_size);

#endif
