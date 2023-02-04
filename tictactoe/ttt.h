#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <windows.h>

char *replace_char (char *str, char f, char r);
char *board_to_str (char *str, int b, int x);
char *combine_xo(char *str, char *x, char *o);
char *get_board (char *str, char *xo);
bool win(int board);
int turn(int board, int move);
void print_board(int x_board, int o_board);
int find_move(int board, int x_board, int o_board, char side, int d, int *move, int *count);
bool game_over(int board, int x_board, int o_board, char side);
void clear(int n);