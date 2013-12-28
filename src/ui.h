#ifndef UI
#define UI

#include "entity/cell.h"

#define CELLS_LIST_MIN 0
#define CELLS_LIST_FULL 1

void ui_list_cells(s_cell **cells, int nb_cells, short full_display);
void ui_prompt(const char *prompt, char *command, size_t command_size);
void ui_error(const char *msg);
void ui_info(const char *msg);

#endif
