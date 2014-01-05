#include <stdlib.h>
#include <stdio.h>
#include "entity/cell.h"
#include "entity/player.h"
#include "testcell.h"
#include "test.h"

void test_init_cell(void)
{
	printf("\ntest_init_cell\n");
	s_cell c;
	int result;

	result = init_cell(&c, 1, 4);
	assert_null(c.owner);
	assert_int_equals(result, 1);
	assert_int_equals(c.id, 1);
	assert_int_equals(c.nb_pawns, 0);
	assert_int_equals(c.nb_neighbours, 0);
	assert_int_equals(c.nb_max_neighbours, 3);

	free_cell(&c);
}

void test_free_cell(void)
{
	printf("\ntest_free_cell\n");
	s_cell c;
	init_cell(&c, 1, 4);
	free_cell(&c);

	assert_null(c.neighbours);
}

void test_cell_set_owner(void)
{
	printf("\ntest_cell_set_owner\n");
	s_cell c;
	s_player p;
	init_cell(&c, 1, 4);
	init_player(&p, 1, "test", 1, STRATEGY_NONE, 10);

	assert_null(c.owner);
	cell_set_owner(&c, &p);
	assert_str_equals(c.owner->name, "test");
	assert_int_equals(c.owner->nb_cells, 1);

	free_cell(&c);
}

void test_cell_set_nb_pawns(void)
{
	printf("\ntest_cell_set_nb_pawns\n");
	s_cell c;
	s_player p;
	int result;

	init_cell(&c, 1, 4);
	init_player(&p, 1, "test", 1, STRATEGY_NONE, 10);

	result = cell_set_nb_pawns(&c, 13);
	assert_int_equals(result, CELL_ERROR_SET_PAWNS_NO_OWNER);
	assert_int_equals(c.nb_pawns, 0);
	cell_set_owner(&c, &p);

	result = cell_set_nb_pawns(&c, 13);
	assert_int_equals(result, CELL_ERROR_SET_PAWNS_NOT_ENOUGH_PAWNS);
	assert_int_equals(c.nb_pawns, 0);

	result = cell_set_nb_pawns(&c, 10);
	assert_int_equals(result, CELL_SET_PAWNS_OK);
	assert_int_equals(c.nb_pawns, 10);

	free_cell(&c);
}

void test_cell_add_neighbour(void)
{
	printf("\ntest_cell_add_neighbour\n");
	s_cell cells[4];
	int c, result;
	uint8_t nb_cells;

	nb_cells = 3;
	for (c = 0; c < 4; c++) {
		init_cell(&cells[c], c, nb_cells);
	}

	result = cell_add_neighbour(&cells[0], &cells[1]);
	assert_int_equals(result, CELL_ADD_NEIGHBOUR_OK);
	assert_int_equals(cells[0].nb_neighbours, 1);
	assert_int_equals(cells[1].nb_neighbours, 1);

	result = cell_add_neighbour(&cells[0], &cells[1]);
	assert_int_equals(result, CELL_ERROR_ALREADY_NEIGHBOUR);
	assert_int_equals(cells[0].nb_neighbours, 1);
	assert_int_equals(cells[1].nb_neighbours, 1);

	cell_add_neighbour(&cells[0], &cells[2]);

	result = cell_add_neighbour(&cells[0], &cells[3]);
	assert_int_equals(result, CELL_ERROR_MAX_NEIGHBOURS_REACHED);
	assert_int_equals(cells[0].nb_neighbours, nb_cells - 1);
	assert_int_equals(cells[3].nb_neighbours, 0);

	for (c = 0; c < 4; c++) {
		free_cell(&cells[c]);
	}
}

void test_cell_are_neighbours(void)
{
	printf("\ntest_cell_are_neighbours\n");
	s_cell cells[3];
	int c;
	uint8_t nb_cells;

	nb_cells = 3;
	for (c = 0; c < 4; c++) {
		init_cell(&cells[c], c, nb_cells);
	}

	cell_add_neighbour(&cells[0], &cells[1]);
	cell_add_neighbour(&cells[1], &cells[2]);

	assert_int_equals(cell_are_neighbours(&cells[0], &cells[1]), 1);
	assert_int_equals(cell_are_neighbours(&cells[1], &cells[2]), 1);
	assert_int_equals(cell_are_neighbours(&cells[0], &cells[2]), 0);

	for (c = 0; c < 3; c++) {
		free_cell(&cells[c]);
	}
}
