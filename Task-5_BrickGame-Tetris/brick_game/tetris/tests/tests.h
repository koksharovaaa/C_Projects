#ifndef S21_TETRIS_TESTS_H
#define S21_TETRIS_TESTS_H

#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "tetris_backend.h"

#define SUCCESS 1
#define FAILURE 0
#define NO_TEST -1

#define FIELDS_FILE "brick_game/tetris/tests/fields.txt"

// Test functions

Suite *field_tests(void);
Suite *mask_tests(void);
Suite *figure_tests(void);
Suite *fsm_tests(void);

// Helpers
void h_set_parameters(TetrisInfo_t *G);
void h_set_next(TetrisInfo_t *G, int index);
void h_fill_field(TetrisInfo_t *G, int value);

int h_figures_eq(figure_t a, figure_t b);
int h_parameters_eq(TetrisInfo_t *A, TetrisInfo_t *B);
int h_fields_eq(TetrisInfo_t *A, TetrisInfo_t *B);

int h_check_next(TetrisInfo_t *G);
int h_is_field_empty(TetrisInfo_t *G);
void h_get_field(TetrisInfo_t *G, FILE **file, const char *Gest);
int h_test_field(TetrisInfo_t *G, FILE **file);

#endif